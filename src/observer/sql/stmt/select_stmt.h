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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <vector>
#include <memory>

#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/stmt/join_stmt.h"
#include "sql/stmt/order_by_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt
{
public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }

public:
  static RC create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt, bool find_ctx = false);

public:
  const std::vector<Table *> &tables() const { return tables_; }
  // const std::vector<Field>                  &query_fields() const { return query_fields_; }
  const std::vector<shared_ptr<Expression>>  &query_exprs() const { return query_exprs_; }
  std::vector<shared_ptr<Expression>>  &query_exprs() { return query_exprs_; }
  const std::vector<shared_ptr<JoinStmt>>    &join_stmts() const { return join_stmts_; }
  const std::vector<shared_ptr<OrderByStmt>> &order_by_stmts() const { return order_by_stmts_; }
  FilterStmt                                 *filter_stmt() const { return filter_stmt_; }
  FilterStmt                                 *having_stmt() const { return having_stmt_; }
  std::vector<shared_ptr<Expression>>        &group_by_exprs() { return group_by_exprs_; }
  std::vector<shared_ptr<Expression>>        &having_exprs() { return having_exprs_; }
  const std::vector<std::string>             &field_alias() const { return field_alias_; }
  std::vector<std::string>             &field_alias() { return field_alias_; }

private:
  static RC check_table_and_filed_no_star(std::unordered_map<std::string, Table *> &table_map, const char *table_name,
      const char *field_name, Table *default_table);
  std::vector<shared_ptr<Expression>> query_exprs_;  // try to convert from query_fields to query_exprs
  // std::vector<Field>                  query_fields_;
  std::vector<Table *>                 tables_;
  FilterStmt                          *filter_stmt_ = nullptr;
  std::vector<shared_ptr<JoinStmt>>    join_stmts_;
  std::vector<shared_ptr<OrderByStmt>> order_by_stmts_;
  std::vector<shared_ptr<Expression>>  group_by_exprs_;

  FilterStmt                         *having_stmt_ = nullptr;
  std::vector<shared_ptr<Expression>> having_exprs_;
  std::vector<shared_ptr<Expression>> other_func_aggr_field_exprs_;
  std::vector<std::string>            field_alias_;
};
