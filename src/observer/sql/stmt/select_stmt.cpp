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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/join_stmt.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/db/db.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
#include <cstddef>
#include <memory>
#include <vector>

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

static void wildcard_fields(Table *table, std::vector<shared_ptr<Expression>> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(make_shared<FieldExpr>(table, table_meta.field(i)));
  }
}

RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *>                     tables;
  std::unordered_map<std::string, Table *> table_map;

  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }
  // collect tables in join statements

  // create join statement

  for (size_t i = 0; i < select_sql.joins.size(); i++) {
    const InnerJoinSqlNode &join_node       = select_sql.joins[i];
    const char             *join_table_name = join_node.relation_name.c_str();
    Table                  *join_table      = db->find_table(join_table_name);
    if (join_table == nullptr) {
      LOG_WARN("Can't find the relation name %s from join node.", join_node.relation_name.c_str());
      return RC::INVALID_ARGUMENT;
    }
    tables.push_back(join_table);
    table_map.insert(std::pair<std::string, Table *>(join_table_name, join_table));
  }

  std::vector<shared_ptr<JoinStmt>> join_stmts;
  bool                              has_join = select_sql.joins.size() > 0;

  if (has_join) {
    for (const auto &join_node : select_sql.joins) {
      const char *table_name = join_node.relation_name.c_str();
      if (nullptr == table_name) {
        LOG_WARN("invalid argument. relation name is null.");
        return RC::INVALID_ARGUMENT;
      }
      Table *join_table = db->find_table(table_name);
      if (nullptr == join_table) {
        LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }
      FilterStmt *join_filter_stmt = nullptr;
      RC          rc               = FilterStmt::create(db,
          nullptr,
          &table_map,
          join_node.join_conditions.data(),
          join_node.join_conditions.size(),
          join_filter_stmt);
      if (rc != RC::SUCCESS) {
        LOG_WARN("fail to create filter for join.");
        return rc;
      }
      table_map.insert(std::pair<std::string, Table *>(table_name, join_table));
      auto join_stmt = make_shared<JoinStmt>(join_table, shared_ptr<FilterStmt>(join_filter_stmt));
      join_stmts.push_back(join_stmt);
      // join_stmts.emplace_back(join_table, shared_ptr<FilterStmt>(join_filter_stmt));
    }
  }

  // collect query expressions
  std::vector<shared_ptr<Expression>> query_exprs;
  for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
    const RelAttrSqlNode &relation_attr = select_sql.attributes[i];

    if (relation_attr.is_aggr) {
      AggrType    aggr_type  = relation_attr.aggr_type;
      const char *table_name = relation_attr.relation_name.c_str();
      const char *field_name = relation_attr.attribute_name.c_str();
      if (!common::is_blank(relation_attr.relation_name.c_str())) {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        auto             table      = iter->second;
        const FieldMeta *field_meta = table->table_meta().field(field_name);
        if (nullptr == field_meta) {
          if ((0 == strcmp(field_name, "*"))) {
            field_meta = new FieldMeta();
          } else {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
            return RC::SCHEMA_FIELD_MISSING;
          }
        }
        query_exprs.emplace_back(make_shared<AggregateExpr>(aggr_type, table, field_meta));
      } else {
        if (tables.size() != 1) {
          LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table           *table      = tables[0];
        const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
        if (nullptr == field_meta) {
          if ((0 == strcmp(field_name, "*"))) {
            field_meta = new FieldMeta();
          } else {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
            return RC::SCHEMA_FIELD_MISSING;
          }
        }
        query_exprs.emplace_back(make_shared<AggregateExpr>(aggr_type, table, field_meta));
      }
      continue;
    }

    if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
      for (Table *table : tables) {
        wildcard_fields(table, query_exprs);
      }

    } else if (!common::is_blank(relation_attr.relation_name.c_str())) {
      const char *table_name = relation_attr.relation_name.c_str();
      const char *field_name = relation_attr.attribute_name.c_str();

      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        for (Table *table : tables) {
          wildcard_fields(table, query_exprs);
        }
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          wildcard_fields(table, query_exprs);
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }
          query_exprs.emplace_back(make_shared<FieldExpr>(table, field_meta));
        }
      }
    } else {
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table           *table      = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }
      query_exprs.emplace_back(make_shared<FieldExpr>(table, field_meta));
    }
  }

  LOG_INFO("got %d tables in from stmt and %d fields/exprs in query stmt", tables.size(), query_exprs.size());
  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions.data(),
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }
  // create order by statements
  std::vector<shared_ptr<OrderByStmt>> order_by_stmts;
  for (int i = 0; i < select_sql.order_bys.size(); i++) {
    const OrderBySqlNode &order_by_node = select_sql.order_bys[i];
    OrderType             order_by_type = order_by_node.order_type;
    const char           *table_name    = order_by_node.attr.relation_name.c_str();
    const char           *field_name    = order_by_node.attr.attribute_name.c_str();
    Table                *table         = default_table;

    if ((0 == strcmp(field_name, "*")) || (0 == strcmp(table_name, "*"))) {
      LOG_WARN("invalid field name in order by stmt while table or filed is *. attr=%s", field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }

    if (!common::is_blank(table_name)) {
      auto iter = table_map.find(table_name);
      if (iter == table_map.end()) {
        LOG_WARN("no such table in from list: %s", table_name);
        return RC::SCHEMA_FIELD_MISSING;
      }
      table = iter->second;
    } else {
      if (tables.size() != 1) {
        LOG_WARN("table size should be 1 for order by stmt.");
        return RC::SCHEMA_FIELD_MISSING;
      }
    }
    const FieldMeta *field_meta = table->table_meta().field(field_name);
    if (nullptr == field_meta) {
      LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    order_by_stmts.emplace_back(make_shared<OrderByStmt>(order_by_type, table, field_meta));
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  select_stmt->query_exprs_.swap(query_exprs);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->join_stmts_.swap(join_stmts);
  select_stmt->order_by_stmts_.swap(order_by_stmts);
  stmt = select_stmt;
  return RC::SUCCESS;
}
