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
// Created by Wangyunlai on 2022/12/15
//

#include "sql/operator/order_by_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/expr/expression.h"
#include <memory>

// ProjectLogicalOperator::ProjectLogicalOperator(const std::vector<Field> &fields) : fields_(fields) {}

OrderByLogicalOperator::OrderByLogicalOperator(const vector<shared_ptr<OrderByStmt>> &order_by_stmt)
{

  for (const auto &stmt : order_by_stmt) {
    order_by_exprs_.push_back(stmt->get_attr_expr());
    order_by_type_.push_back(stmt->get_order_type());
  }
}