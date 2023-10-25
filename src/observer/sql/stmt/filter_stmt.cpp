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
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
#include <memory>

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
  bool is_left_attr  = filter_unit.left().is_attr;
  bool is_right_attr = filter_unit.right().is_attr;
  bool is_left_expr  = filter_unit.left().is_expr;
  bool is_right_expr = filter_unit.right().is_expr;

  auto get_filer_obj_expr_type = [](const FilterObj &obj) {
    const auto &expr = obj.expression;
    if (expr->type() == ExprType::AGGREGATE) {
      const auto &aggr_expr = dynamic_pointer_cast<AggregateExpr>(expr);

      if (aggr_expr->aggregate_type() == AVG_T) {
        return FLOATS;
      } else if (aggr_expr->aggregate_type() == COUNT_T) {
        return INTS;
      } else {
        return aggr_expr->field().attr_type();
      }
    }
    return obj.field.attr_type();
  };

  auto get_filer_obj_type = [&](const FilterObj &obj, bool is_attr, bool is_expr) {
    if (is_expr) {
      return get_filer_obj_expr_type(obj);
    }
    return is_attr ? obj.field.attr_type() : obj.value.attr_type();
  };

  AttrType left_type  = get_filer_obj_type(filter_unit.left(), is_left_attr, is_left_expr);
  AttrType right_type = get_filer_obj_type(filter_unit.right(), is_right_attr, is_right_expr);

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
  if (condition.left_is_attr) {
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;

    rc = get_table_and_field(db, default_table, tables, condition.left_attr, table, field);
    if (rc != RC::SUCCESS) {
      if (condition.left_attr.is_aggr && condition.left_attr.aggr_type == COUNT_T) {
        table = default_table;
        field = new FieldMeta("*");
        rc    = RC::SUCCESS;
      }
      if (table == nullptr || field == nullptr) {
        LOG_WARN("cannot find attr");
        return rc;
      }
    }
    FilterObj filter_obj;
    if (condition.left_attr.is_aggr) {
      AggrType aggr_type = condition.left_attr.aggr_type;
      filter_obj.init_expr(make_shared<AggregateExpr>(aggr_type, table, field));
    } else {
      filter_obj.init_attr(Field(table, field));
    }

    filter_unit->set_left(filter_obj);
  } else {
    FilterObj filter_obj;
    if (condition.left_value.attr_type() == DATES && !is_date_valid(condition.left_value.get_string())) {
      return RC::INVALID_ARGUMENT;
    }
    filter_obj.init_value(condition.left_value);
    filter_unit->set_left(filter_obj);
  }

  if (condition.right_is_attr) {
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    rc                     = get_table_and_field(db, default_table, tables, condition.right_attr, table, field);
    if (rc != RC::SUCCESS) {
      if (condition.left_attr.is_aggr && condition.left_attr.aggr_type == COUNT_T) {
        table = default_table;
        field = new FieldMeta("*");
        rc    = RC::SUCCESS;
      }
      if (table == nullptr || field == nullptr) {
        LOG_WARN("cannot find attr");
        return rc;
      }
    }
    FilterObj filter_obj;
    if (condition.left_attr.is_aggr) {
      AggrType aggr_type = condition.left_attr.aggr_type;
      filter_obj.init_expr(make_shared<AggregateExpr>(aggr_type, table, field));
    } else {
      filter_obj.init_attr(Field(table, field));
    }
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
