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
#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/join_stmt.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/db/db.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
#include <cstddef>
#include <cstring>
#include <memory>
#include <string>
#include <utility>
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

static void wildcard_fields(Table *table, std::vector<shared_ptr<Expression>> &field_metas, string table_alias,
    std::vector<std::string> &field_alias)
{
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    auto field_expr = make_shared<FieldExpr>(table, table_meta.field(i));
    if (table_alias != "") {
      field_expr->set_table_alias(table_alias);
    }
    field_metas.push_back(field_expr);
    field_alias.emplace_back("");
  }
}

RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt, bool find_ctx)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *>                         tables;
  std::unordered_map<std::string, Table *>     table_map;
  std::unordered_map<std::string, std::string> table_alias;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {

    const auto &[table_name_str, table_name_alias] = select_sql.relations[i];
    // const char *table_name                  = select_sql.relations[i].c_str();
    const char *table_name = table_name_str.c_str();
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
    if (table_name_alias != "") {
      if (table_alias.find(table_name_alias) != table_alias.end()) {
        LOG_WARN("invalid argument. relation name alias can't be the same.");
        return RC::INVALID_ARGUMENT;
      }
      table_alias.insert(std::pair<std::string, std::string>(table_name_alias, table_name_str));
      FilterCtx::get_instance().table_names_.insert(std::pair<std::string, Table *>(table_name_alias, table));
    }
    FilterCtx::get_instance().table_names_.insert(std::pair<std::string, Table *>(table_name, table));
  }

  // collect tables in join statements
  // todo(ligch): join stmts haven't support table alias yet
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

  // create join statement
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
      auto join_stmt = make_shared<JoinStmt>(join_table, shared_ptr<FilterStmt>(join_filter_stmt));
      join_stmts.push_back(join_stmt);
    }
  }

  // collect query expressions
  std::vector<shared_ptr<Expression>> query_exprs;
  std::vector<std::string>            field_alias;

  for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
    const RelAttrSqlNode &relation_attr = select_sql.attributes[i];

    if (relation_attr.is_expr) {
      auto expr = relation_attr.expr;
      // create field expressions
      if (expr->type() == ExprType::AGGREGATE) {
        // create aggregate expressions
        auto   aggregate_expr = dynamic_cast<AggregateExpr *>(expr);
        Table *default_table  = tables.size() > 0 ? tables[0] : nullptr;
        RC     rc = AggregateExpr::complete_aggregate_expr(db, default_table, &table_map, &table_alias, aggregate_expr);
        if (rc != RC::SUCCESS) {
          LOG_WARN("complete aggregate expression failed");
          return rc;
        }
        field_alias.emplace_back(relation_attr.alias);
        query_exprs.emplace_back(aggregate_expr);
        continue;
      }

      if (expr->type() == ExprType::FUNCTION) {
        auto   func_expr     = dynamic_cast<FunctionExpr *>(expr);
        Table *default_table = tables.size() > 0 ? tables[0] : nullptr;
        RC     rc = FunctionExpr::complete_function_expr(db, default_table, &table_map, &table_alias, func_expr);
        if (rc != RC::SUCCESS) {
          LOG_WARN("complete aggregate expression failed");
          return rc;
        }
        field_alias.emplace_back(relation_attr.alias);
        query_exprs.emplace_back(func_expr);
        continue;
      }

      if (expr->type() == ExprType::ARITHMETIC) {
        auto   arithmetic_expr = dynamic_cast<ArithmeticExpr *>(expr);
        Table *default_table   = tables.size() > 0 ? tables[0] : nullptr;
        RC rc = ArithmeticExpr::complete_arithmetic_expr(db, default_table, &table_map, &table_alias, arithmetic_expr);
        if (rc != RC::SUCCESS) {
          LOG_WARN("complete arithmetic expression failed");
          return rc;
        }
        field_alias.emplace_back(relation_attr.alias);
        query_exprs.emplace_back(arithmetic_expr);
        // todo(ligch): collect aggregate expressions from arithmetic expr
        continue;
      }

      if (expr->type() == ExprType::FIELD) {
        auto field_expr = dynamic_cast<FieldExpr *>(expr);
        // auto rel_alias      = relation_attr.alias;
        auto alias          = field_expr->get_tmp_alias();
        auto relation_name  = field_expr->get_tmp_relation_name();
        auto attribute_name = field_expr->get_tmp_attribute_name();
        if (common::is_blank(relation_name.c_str()) && 0 == strcmp(attribute_name.c_str(), "*")) {
          for (Table *table : tables) {
            wildcard_fields(table, query_exprs, "", field_alias);  // todo: fix alias
          }
        } else if (!common::is_blank(relation_name.c_str())) {
          if (0 == strcmp(relation_name.c_str(), "*")) {
            if (0 != strcmp(attribute_name.c_str(), "*")) {
              LOG_WARN("invalid field name while table is *. attr=%s", relation_name.c_str());
              return RC::SCHEMA_FIELD_MISSING;
            }
            for (Table *table : tables) {
              wildcard_fields(table, query_exprs, "", field_alias);  // todo: fix alias
            }
          } else {
            auto iter = table_map.find(relation_name);
            if (iter == table_map.end()) {
              if (table_alias.find(relation_name) == table_alias.end()) {
                LOG_WARN("no such table in from list: %s", relation_name.c_str());
                return RC::SCHEMA_FIELD_MISSING;
              }
              auto table_real_name = table_alias[relation_name];
              if (table_map.find(table_real_name) == table_map.end()) {
                LOG_WARN("no such table in from list: %s", relation_name.c_str());
                return RC::SCHEMA_FIELD_MISSING;
              }
              iter = table_map.find(table_real_name);
            }

            Table *table = iter->second;
            if (0 == strcmp(attribute_name.c_str(), "*")) {
              wildcard_fields(table, query_exprs, relation_name.c_str(), field_alias);
            } else {
              const FieldMeta *field_meta = table->table_meta().field(attribute_name.c_str());
              if (nullptr == field_meta) {
                LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), attribute_name.c_str());
                return RC::SCHEMA_FIELD_MISSING;
              }
              auto field_expr = make_shared<FieldExpr>(table, field_meta);
              field_expr->set_table_alias(relation_name.c_str());
              field_alias.emplace_back(relation_attr.alias);
              query_exprs.emplace_back(make_shared<FieldExpr>(table, field_meta));
            }
          }
        } else {
          // select col1
          if (tables.size() != 1) {
            LOG_WARN("invalid. I do not know the attr's table. attr=%s", attribute_name.c_str());
            return RC::SCHEMA_FIELD_MISSING;
          }

          Table           *table      = tables[0];
          const FieldMeta *field_meta = table->table_meta().field(attribute_name.c_str());
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), attribute_name.c_str());
            return RC::SCHEMA_FIELD_MISSING;
          }
          auto field_expr = make_shared<FieldExpr>(table, field_meta);
          field_expr->set_table_alias(table->name());
          query_exprs.emplace_back(field_expr);
          field_alias.emplace_back(relation_attr.alias);
        }
        continue;
      }

      if (expr->type() == ExprType::VALUE) {
        LOG_WARN("shouldn't happen.");
        continue;
      }
      field_alias.emplace_back(relation_attr.alias);
    }
  }

  LOG_INFO("got %d tables in from stmt and %d fields/exprs in query stmt", tables.size(), query_exprs.size());
  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
    db->set_default_table(default_table);
  }

  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(db,
      default_table,
      &table_map,
      &table_alias,
      select_sql.conditions.data(),
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt,
      find_ctx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // create order by statements
  // 目前order by 只涉及rel_attr, 因此目前expression的改动未对其造成影响
  std::vector<shared_ptr<OrderByStmt>> order_by_stmts;
  for (int i = 0; i < select_sql.order_bys.size(); i++) {
    const OrderBySqlNode &order_by_node = select_sql.order_bys[i];
    OrderType             order_by_type = order_by_node.order_type;
    const char           *table_name    = order_by_node.attr.relation_name.c_str();
    const char           *field_name    = order_by_node.attr.attribute_name.c_str();
    Table                *table         = default_table;
    if ((0 == strcmp(field_name, "*")) || (0 == strcmp(table_name, "*"))) {
      LOG_WARN("invalid field name in xx by stmt while table or filed is *. attr=%s", field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    table = default_table;
    if (!common::is_blank(table_name)) {
      auto iter = table_map.find(table_name);
      if (iter == table_map.end()) {
        LOG_WARN("no such table in from list: %s", table_name);
        return RC::SCHEMA_FIELD_MISSING;
      }
      table = iter->second;
    } else {
      if (table_map.size() != 1) {
        LOG_WARN("table size should be 1 for xx by stmt.");
        return RC::SCHEMA_FIELD_MISSING;
      }
    }
    const FieldMeta *field_meta = table->table_meta().field(field_name);
    if (nullptr == field_meta) {
      LOG_WARN("no such field. field=%s.%s", table->name(), field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    order_by_stmts.emplace_back(make_shared<OrderByStmt>(order_by_type, table, field_meta));
  }

  // collect group by expressions
  std::vector<shared_ptr<Expression>> group_by_exprs_;
  for (const auto &group_by_attr : select_sql.group_bys) {
    const char *table_name = nullptr;
    const char *field_name = nullptr;
    if (group_by_attr.is_expr) {
      auto expr = group_by_attr.expr;
      if (expr->type() == ExprType::FIELD) {
        auto field_expr = dynamic_cast<FieldExpr *>(expr);
        table_name      = field_expr->get_tmp_relation_name().c_str();
        field_name      = field_expr->get_tmp_attribute_name().c_str();
      } else {
        LOG_WARN("shouldn't happen.");
        return RC::INVALID_ARGUMENT;
      }
    } else {
      LOG_WARN("shouldn't happen.");
      return RC::INVALID_ARGUMENT;
      // table_name = group_by_attr.relation_name.c_str();
      // field_name = group_by_attr.attribute_name.c_str();
    }

    if ((0 == strcmp(field_name, "*")) || (0 == strcmp(table_name, "*"))) {
      LOG_WARN("invalid field name in xx by stmt while table or filed is *. attr=%s", field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    Table *table = default_table;
    if (!common::is_blank(table_name)) {
      auto iter = table_map.find(table_name);
      if (iter == table_map.end()) {
        LOG_WARN("no such table in from list: %s", table_name);
        return RC::SCHEMA_FIELD_MISSING;
      }
      table = iter->second;
    } else {
      if (table_map.size() != 1) {
        LOG_WARN("table size should be 1 for xx by stmt.");
        return RC::SCHEMA_FIELD_MISSING;
      }
    }
    const FieldMeta *field_meta = table->table_meta().field(field_name);
    if (nullptr == field_meta) {
      LOG_WARN("no such field. field=%s.%s.", table->name(), field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }

    // if (group_by_attr.is_aggr) {
    //   group_by_exprs_.emplace_back(make_shared<AggregateExpr>(group_by_attr.aggr_type, table, field_meta));
    // } else {
    group_by_exprs_.emplace_back(make_shared<FieldExpr>(table, field_meta));
    // }
  }
  Table *table = default_table;
  // create having statement
  FilterStmt                         *having_stmt = nullptr;
  std::vector<shared_ptr<Expression>> having_exprs;
  if (!select_sql.havings.empty()) {
    for (const auto &cond : select_sql.havings) {
      if (cond.left_is_attr) {
        assert(cond.left_attr.is_expr);
        const auto &cond_left_expr = cond.left_attr.expr;
        if (cond_left_expr->type() == ExprType::AGGREGATE) {
          auto   aggregate_expr = dynamic_cast<AggregateExpr *>(cond_left_expr);
          Table *default_table  = tables.size() > 0 ? tables[0] : nullptr;
          RC rc = AggregateExpr::complete_aggregate_expr(db, default_table, &table_map, &table_alias, aggregate_expr);
          if (rc != RC::SUCCESS) {
            LOG_WARN("complete aggregate expression failed");
            return rc;
          }
          having_exprs.emplace_back(aggregate_expr);
        }
      }

      if (cond.right_is_attr) {
        assert(cond.right_attr.is_expr);
        const auto &cond_right_expr = cond.right_attr.expr;
        if (cond_right_expr->type() == ExprType::AGGREGATE) {
          auto   aggregate_expr = dynamic_cast<AggregateExpr *>(cond_right_expr);
          Table *default_table  = tables.size() > 0 ? tables[0] : nullptr;
          RC rc = AggregateExpr::complete_aggregate_expr(db, default_table, &table_map, &table_alias, aggregate_expr);
          if (rc != RC::SUCCESS) {
            LOG_WARN("complete aggregate expression failed");
            return rc;
          }
          having_exprs.emplace_back(aggregate_expr);
        }
      }
    }

    RC rc = FilterStmt::create(db,
        default_table,
        &table_map,
        &table_alias,
        select_sql.havings.data(),
        static_cast<int>(select_sql.havings.size()),
        having_stmt,
        find_ctx);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct filter stmt");
      return rc;
    }
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  select_stmt->query_exprs_.swap(query_exprs);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->join_stmts_.swap(join_stmts);
  select_stmt->order_by_stmts_.swap(order_by_stmts);
  select_stmt->group_by_exprs_.swap(group_by_exprs_);
  select_stmt->having_stmt_ = having_stmt;
  select_stmt->having_exprs_.swap(having_exprs);
  select_stmt->field_alias_.swap(field_alias);
  stmt = select_stmt;
  return RC::SUCCESS;
}
