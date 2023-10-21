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
// Created by Wangyunlai on 2022/12/07
//

#pragma once

#include "sql/expr/tuple.h"
#include "sql/operator/logical_operator.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/join_stmt.h"
#include <memory>

/**
 * @brief 连接算子
 * @ingroup LogicalOperator
 * @details 连接算子，用于连接两个表。对应的物理算子或者实现，可能有NestedLoopJoin，HashJoin等等。
 */
class JoinLogicalOperator : public LogicalOperator
{
public:
  JoinLogicalOperator() : join_stmt_(nullptr) {}
  JoinLogicalOperator(shared_ptr<JoinStmt> join_stmt) : join_stmt_(join_stmt) {}
  virtual ~JoinLogicalOperator() = default;

  LogicalOperatorType  type() const override { return LogicalOperatorType::JOIN; }
  shared_ptr<JoinStmt> get_join_stmt() const { return join_stmt_; }

private:
  // Table                 *join_table_;
  // shared_ptr<FilterStmt> filter_stmt_;
  shared_ptr<JoinStmt> join_stmt_;
};
