/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "common/date.h"
#include "common/rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/expr/expression.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <memory>
#include <vector>

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc                      = create_filter_unit(db, default_table, tables, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

bool FilterStmt::check_comparable(FilterUnit &filter_unit)
{
  AttrType left_type;
  AttrType right_type;

  bool is_left_values = filter_unit.left().is_values;
  bool is_right_values = filter_unit.right().is_values;
  if (is_left_values && filter_unit.left().values_.size() > 0) {
    return false;
  }
  
  CompOp comp = filter_unit.comp();
  if (comp == IN || comp == IN_NOT) {
    if (is_left_values && is_right_values) return false;
    return true;
  } else if (comp == EXIST || comp == EXIST_NOT) {
    return false;
  } else {
    if (is_left_values && filter_unit.left().values_.size() != 1) return false;
    if (is_right_values && filter_unit.right().values_.size() != 1) return false;
  }

  bool is_left_attr  = filter_unit.left().is_attr;
  bool is_right_attr = filter_unit.right().is_attr;

  auto get_filer_obj_type = [](const FilterObj &obj, bool is_attr) {
    return is_attr ? obj.field.attr_type() : obj.value.attr_type();
  };
  left_type = is_left_values ? filter_unit.left().values_[0].attr_type() : get_filer_obj_type(filter_unit.left(), is_left_attr);
  right_type = is_right_values ? filter_unit.right().values_[0].attr_type() : get_filer_obj_type(filter_unit.right(), is_right_attr);

  // 均为attr类型，可能同时为DATES类型
  if (left_type == DATES && right_type == DATES) {
    return true;
  }
  if (left_type == CHARS && right_type == DATES) {
    date_u date;
    auto   ret = str_to_date(filter_unit.left().value.get_string(), date);
    if (ret != RC::SUCCESS) {
      return false;
    }
    FilterObj new_left_obj;
    Value     new_value(date);
    new_left_obj.init_value(new_value);
    filter_unit.set_left(new_left_obj);
  }
  if (left_type == DATES && right_type == CHARS) {
    date_u date;
    auto   ret = str_to_date(filter_unit.right().value.get_string(), date);
    if (ret != RC::SUCCESS) {
      return false;
    }
    FilterObj new_right_obj;
    Value     new_value(date);
    new_right_obj.init_value(new_value);
    filter_unit.set_right(new_right_obj);
  }
  // todo(ligch): 可能有其他类型也无法比较，目前只针对date进行判断。
  return true;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  filter_unit = new FilterUnit;

  if (condition.unary_op) {
    if (condition.comp == EXIST || condition.comp == EXIST_NOT) {
      goto right;
    }
    return RC::INVALID_ARGUMENT;
  }

  if (condition.left_is_select) {
    Stmt *select_stmt;
    rc = SelectStmt::create(db, *condition.left_select, select_stmt);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("create left sub select failed. %d:%s", rc, strrc(rc));
      return rc;
    }
    vector<Value> values;
    rc = SubselctToResult(select_stmt, values, !(condition.comp == EXIST || condition.comp == EXIST_NOT));
    if (rc != RC::SUCCESS) {
      LOG_ERROR("create right sub select failed. %d:%s", rc, strrc(rc));
      return rc;
    }
    if (values.size() == 1) {
      FilterObj filter_obj;
      filter_obj.init_value(values[0]);
      filter_unit->set_left(filter_obj);
    } else {
      FilterObj filter_obj;
      filter_obj.init_values(std::move(values));
      filter_unit->set_left(filter_obj);
    }
  } else if (condition.left_is_attr) {
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    rc                     = get_table_and_field(db, default_table, tables, condition.left_attr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_left(filter_obj);
  } else {
    FilterObj filter_obj;
    if (condition.left_value.attr_type() == DATES && !is_date_valid(condition.left_value.get_string())) {
      return RC::INVALID_ARGUMENT;
    }
    filter_obj.init_value(condition.left_value);
    filter_unit->set_left(filter_obj);
  }

right:
  if (condition.right_is_select) {
    vector<Value> values;
    if (condition.values.empty()) {
      Stmt *select_stmt;
      rc = SelectStmt::create(db, *condition.right_select, select_stmt);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("create left sub select failed. %d:%s", rc, strrc(rc));
        return rc;
      }
      
      rc = SubselctToResult(select_stmt, values, !(condition.comp == EXIST || condition.comp == EXIST_NOT));
      if (rc != RC::SUCCESS) {
        LOG_ERROR("create right sub select failed. %d:%s", rc, strrc(rc));
        return rc;
      }
    } else {
      values = condition.values;
    }
    if (condition.unary_op) {
      if (!values.empty()) {
        *filter_unit = create_equal_filter_unit();
        return rc;
      } else {
        *filter_unit = create_not_equal_filter_unit();
        return rc;
      }
    } else {
      if (values.size() == 1) {
        FilterObj filter_obj;
        filter_obj.init_value(values[0]);
        filter_unit->set_right(filter_obj);
      } else {
        FilterObj filter_obj;
        filter_obj.init_values(std::move(values));
        filter_unit->set_right(filter_obj);
      }
    }
  } else if (condition.right_is_attr) {
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    rc                     = get_table_and_field(db, default_table, tables, condition.right_attr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_right(filter_obj);
  } else {
    FilterObj filter_obj;
    filter_obj.init_value(condition.right_value);
    filter_unit->set_right(filter_obj);
  }

  filter_unit->set_comp(comp);

  // 检查两个类型是否能够比较
  if (!check_comparable(*filter_unit)) {
    LOG_ERROR("cant't compare left type with right type.");
    return RC::INVALID_ARGUMENT;
  }
  return rc;
}

RC SubselctToResult(Stmt *select_stmt, std::vector<Value> &values, bool single_cell_need) {
  unique_ptr<LogicalOperator> logical_oper;
  LogicalPlanGenerator logical_plan_generator;
  RC rc = RC::SUCCESS;
  rc = logical_plan_generator.create(select_stmt, logical_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create logical plan. rc=%s", strrc(rc));
    return rc;
  }
  PhysicalPlanGenerator physical_plan_generator;
  unique_ptr<PhysicalOperator> physical_oper;
  rc = physical_plan_generator.create(*logical_oper, physical_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create physical plan. rc=%s", strrc(rc));
    return rc;
  }
  rc = physical_oper->open(nullptr);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open physical plan. rc=%s", strrc(rc));
    return rc;
  }
  while (physical_oper->next() == RC::SUCCESS) {
    Tuple *tuple = physical_oper->current_tuple();
    Value value;
    if (single_cell_need && tuple->cell_num() != 1) {
      return RC::INVALID_ARGUMENT;
    }
    tuple->cell_at(0, value);
    values.push_back(value);
  }
  return RC::SUCCESS;
}