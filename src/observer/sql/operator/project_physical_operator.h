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

#pragma once

#include "sql/expr/expression.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/parse_defs.h"
#include <memory>
#include <vector>

/**
 * @brief 选择/投影物理算子
 * @ingroup PhysicalOperator
 */
class ProjectPhysicalOperator : public PhysicalOperator
{
public:
  ProjectPhysicalOperator() {}

  virtual ~ProjectPhysicalOperator() = default;

  void add_expressions(std::vector<std::unique_ptr<Expression>> &&expressions) {}
  void add_projection(const Table *table, const FieldMeta *field, const std::string alias = "");
  void add_projection(
      const Table *table, const std::string table_alias, const FieldMeta *field, const std::string alias = "");

  void                 add_projection(const std::string &alias);
  void                 add_projection(const std::string &alias, shared_ptr<Expression> expr);
  void                 add_function_expr(const shared_ptr<FunctionExpr> &func_expr);
  void                 add_arithmetic_expr(const shared_ptr<ArithmeticExpr> &arithmetic_expr);
  PhysicalOperatorType type() const override { return PhysicalOperatorType::PROJECT; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  int cell_num() const { return tuple_.cell_num(); }

  Tuple *current_tuple() override;

private:
  ProjectTuple                       tuple_;
  vector<shared_ptr<FunctionExpr>>   function_exprs_;
  vector<shared_ptr<ArithmeticExpr>> arithmetic_exprs_;
  bool                               is_ended_{false};
};
