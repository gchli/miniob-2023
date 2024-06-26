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
// Created by WangYunlai on 2022/07/01.
//

#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include <memory>

RC ProjectPhysicalOperator::open(Trx *trx)
{
  is_ended_ = false;
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC                rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  return RC::SUCCESS;
}

RC ProjectPhysicalOperator::next()
{
  if (children_.empty() && (!function_exprs_.empty() || !arithmetic_exprs_.empty())) {
    if (!is_ended_) {
      is_ended_ = true;
      return RC::SUCCESS;
    }
    return RC::RECORD_EOF;
  }

  if (children_.empty()) {

    return RC::RECORD_EOF;
  }

  return children_[0]->next();
}

RC ProjectPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}

Tuple *ProjectPhysicalOperator::current_tuple()
{
  if (children_.empty() && (!function_exprs_.empty() || !arithmetic_exprs_.empty())) {
    tuple_.set_tuple(new RowTuple());
  } else {
    tuple_.set_tuple(children_[0]->current_tuple());
  }
  return &tuple_;
}

void ProjectPhysicalOperator::add_projection(
    const Table *table, const std::string table_alias, const FieldMeta *field_meta, std::string alias)
{
  TupleCellSpec *spec;
  if (alias == "") {
    if (table_alias != "") {
      spec = new TupleCellSpec(table_alias.c_str(), field_meta->name());
    } else {
      spec = new TupleCellSpec(table->name(), field_meta->name(), field_meta->name());
    }
  } else {
    spec = new TupleCellSpec(table->name(), field_meta->name(), alias.c_str());
  }
  tuple_.add_cell_spec(spec);
}

void ProjectPhysicalOperator::add_projection(const Table *table, const FieldMeta *field_meta, std::string alias)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  TupleCellSpec *spec;
  if (alias == "") {
    spec = new TupleCellSpec(table->name(), field_meta->name(), field_meta->name());
  } else {
    spec = new TupleCellSpec(table->name(), field_meta->name(), alias.c_str());
  }
  tuple_.add_cell_spec(spec);
}

void ProjectPhysicalOperator::add_projection(const std::string &alias)
{
  TupleCellSpec *spec = new TupleCellSpec(alias.c_str());
  tuple_.add_cell_spec(spec);
}

void ProjectPhysicalOperator::add_projection(const std::string &alias, shared_ptr<Expression> expr)
{
  TupleCellSpec *spec = new TupleCellSpec(alias.c_str());
  spec->set_expr(expr);
  tuple_.add_cell_spec(spec);
}

void ProjectPhysicalOperator::add_function_expr(const shared_ptr<FunctionExpr> &func_expr)
{
  function_exprs_.push_back(func_expr);
}

void ProjectPhysicalOperator::add_arithmetic_expr(const shared_ptr<ArithmeticExpr> &arithmetic_expr)
{
  arithmetic_exprs_.push_back(arithmetic_expr);
}