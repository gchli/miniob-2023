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
// Created by Wangyunlai on 2022/12/14.
//

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "sql/operator/aggregate_logical_operator.h"
#include "sql/operator/apply_logical_operator.h"
#include "sql/operator/apply_physical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/aggregate_physical_operator.h"
#include "sql/operator/order_by_physical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/operator/update_physical_operator.h"
#include "sql/optimizer/physical_plan_generator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/table_scan_physical_operator.h"
#include "sql/operator/index_scan_physical_operator.h"
#include "sql/operator/order_by_physical_operator.h"
#include "sql/operator/order_by_logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/predicate_physical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/insert_physical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/delete_physical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/explain_physical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/join_physical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/calc_physical_operator.h"
#include "sql/expr/expression.h"
#include "common/log/log.h"
#include "sql/stmt/select_stmt.h"
#include "storage/field/field.h"

using namespace std;

RC PhysicalPlanGenerator::create(LogicalOperator &logical_operator, unique_ptr<PhysicalOperator> &oper)
{
  RC rc = RC::SUCCESS;

  switch (logical_operator.type()) {
    case LogicalOperatorType::CALC: {
      return create_plan(static_cast<CalcLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::TABLE_GET: {
      return create_plan(static_cast<TableGetLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::PREDICATE: {
      return create_plan(static_cast<PredicateLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::PROJECTION: {
      return create_plan(static_cast<ProjectLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::AGGREGATE: {
      return create_plan(static_cast<AggregateLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::ORDER_BY: {
      return create_plan(static_cast<OrderByLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::INSERT: {
      return create_plan(static_cast<InsertLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::DELETE: {
      return create_plan(static_cast<DeleteLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::UPDATE: {
      return create_plan(static_cast<UpdateLogicalOperator &>(logical_operator), oper);
    }

    case LogicalOperatorType::EXPLAIN: {
      return create_plan(static_cast<ExplainLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::JOIN: {
      return create_plan(static_cast<JoinLogicalOperator &>(logical_operator), oper);
    } break;

    case LogicalOperatorType::APPLY: {
      return create_plan(static_cast<ApplyLogicalOperator &>(logical_operator), oper);
    } break;

    default: {
      return RC::INVALID_ARGUMENT;
    }
  }
  return rc;
}

RC PhysicalPlanGenerator::create_plan(TableGetLogicalOperator &table_get_oper, unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<Expression>> &predicates = table_get_oper.predicates();
  // 看看是否有可以用于索引查找的表达式
  Table *table = table_get_oper.table();

  Index     *index      = nullptr;
  ValueExpr *value_expr = nullptr;
  for (auto &expr : predicates) {
    if (expr->type() == ExprType::COMPARISON) {
      auto comparison_expr = static_cast<ComparisonExpr *>(expr.get());
      // 简单处理，就找等值查询
      if (comparison_expr->comp() != EQUAL_TO) {
        continue;
      }

      unique_ptr<Expression> &left_expr  = comparison_expr->left();
      unique_ptr<Expression> &right_expr = comparison_expr->right();
      // 左右比较的一边最少是一个值
      if (left_expr->type() != ExprType::VALUE && right_expr->type() != ExprType::VALUE) {
        continue;
      }

      FieldExpr *field_expr = nullptr;
      if (left_expr->type() == ExprType::FIELD) {
        ASSERT(right_expr->type() == ExprType::VALUE, "right expr should be a value expr while left is field expr");
        field_expr = static_cast<FieldExpr *>(left_expr.get());
        value_expr = static_cast<ValueExpr *>(right_expr.get());
      } else if (right_expr->type() == ExprType::FIELD) {
        ASSERT(left_expr->type() == ExprType::VALUE, "left expr should be a value expr while right is a field expr");
        field_expr = static_cast<FieldExpr *>(right_expr.get());
        value_expr = static_cast<ValueExpr *>(left_expr.get());
      }

      if (field_expr == nullptr) {
        continue;
      }

      const Field &field = field_expr->field();
      index              = table->find_index_by_field(field.field_name());
      if (nullptr != index) {
        break;
      }
    }
  }

  if (index != nullptr) {
    // Fuck wrong
    ASSERT(value_expr != nullptr, "got an index but value expr is null ?");

    const Value               &value           = value_expr->get_value();
    IndexScanPhysicalOperator *index_scan_oper = new IndexScanPhysicalOperator(
        table, index, table_get_oper.readonly(), &value, true /*left_inclusive*/, &value, true /*right_inclusive*/);

    index_scan_oper->set_predicates(std::move(predicates));
    oper = unique_ptr<PhysicalOperator>(index_scan_oper);
    LOG_TRACE("use index scan");
  } else {
    auto table_scan_oper = new TableScanPhysicalOperator(table, table_get_oper.readonly());
    if (table_get_oper.table_alias() != "") {
      table_scan_oper->set_table_alias(table_get_oper.table_alias());
    }
    table_scan_oper->set_predicates(std::move(predicates));
    oper = unique_ptr<PhysicalOperator>(table_scan_oper);
    LOG_TRACE("use table scan");
  }

  return RC::SUCCESS;
}

RC PhysicalPlanGenerator::create_plan(PredicateLogicalOperator &pred_oper, unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<LogicalOperator>> &children_opers = pred_oper.children();
  ASSERT(children_opers.size() == 1, "predicate logical operator's sub oper number should be 1");

  LogicalOperator &child_oper = *children_opers.front();

  unique_ptr<PhysicalOperator> child_phy_oper;
  RC                           rc = create(child_oper, child_phy_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create child operator of predicate operator. rc=%s", strrc(rc));
    return rc;
  }

  vector<unique_ptr<Expression>> &expressions = pred_oper.expressions();
  ASSERT(expressions.size() == 1, "predicate logical operator's children should be 1");

  unique_ptr<Expression> expression = std::move(expressions.front());
  oper = unique_ptr<PhysicalOperator>(new PredicatePhysicalOperator(std::move(expression)));
  oper->add_child(std::move(child_phy_oper));
  return rc;
}

RC PhysicalPlanGenerator::create_plan(ProjectLogicalOperator &project_oper, unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = project_oper.children();

  unique_ptr<PhysicalOperator> child_phy_oper;

  RC rc = RC::SUCCESS;
  if (!child_opers.empty()) {
    LogicalOperator *child_oper = child_opers.front().get();
    rc                          = create(*child_oper, child_phy_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create project logical operator's child physical operator. rc=%s", strrc(rc));
      return rc;
    }
  }

  ProjectPhysicalOperator              *project_operator = new ProjectPhysicalOperator;
  const vector<shared_ptr<Expression>> &project_expr     = project_oper.proj_exprs();
  const vector<string>                 &field_alias      = project_oper.field_alias();
  for (int i = 0; i < project_expr.size(); ++i) {
    const auto &expr = project_expr[i];
    if (expr->type() == ExprType::FUNCTION) {
      auto expr_name = expr->alias() == "" ? expr->name() : expr->alias();
      project_operator->add_projection(expr_name, dynamic_pointer_cast<FunctionExpr>(expr));
      project_operator->add_function_expr(dynamic_pointer_cast<FunctionExpr>(expr));
    } else if (expr->type() == ExprType::FIELD) {
      auto converted_field_expr = dynamic_pointer_cast<FieldExpr>(expr);
      auto table_alias          = converted_field_expr->get_table_alias();
      if (table_alias != "") {
        project_operator->add_projection(
            expr->get_field().table(), table_alias, expr->get_field().meta(), field_alias[i]);
      } else {
        project_operator->add_projection(expr->get_field().table(), expr->get_field().meta(), field_alias[i]);
      }
    } else if (expr->type() == ExprType::ARITHMETIC) {
      auto expr_name = field_alias[i] == "" ? expr->name() : field_alias[i];
      project_operator->add_projection(expr_name, dynamic_pointer_cast<ArithmeticExpr>(expr));
      project_operator->add_arithmetic_expr(dynamic_pointer_cast<ArithmeticExpr>(expr));
    }
  }
  if (child_phy_oper) {
    project_operator->add_child(std::move(child_phy_oper));
  }
  oper = unique_ptr<PhysicalOperator>(project_operator);

  LOG_TRACE("create a project physical operator");
  return rc;
}

RC PhysicalPlanGenerator::create_plan(OrderByLogicalOperator &order_by_oper, unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = order_by_oper.children();

  unique_ptr<PhysicalOperator> child_phy_oper;

  RC rc = RC::SUCCESS;
  if (!child_opers.empty()) {
    LogicalOperator *child_oper = child_opers.front().get();
    rc                          = create(*child_oper, child_phy_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create order by logical operator's child physical operator. rc=%s", strrc(rc));
      return rc;
    }
  }

  OrderByPhysicalOperator *order_by_operator =
      new OrderByPhysicalOperator(order_by_oper.order_by_exprs(), order_by_oper.order_by_type());
  // order_by_operator->set_order_by(order_by_oper.order_by_exprs(), order_by_oper.order_by_type());

  if (child_phy_oper) {
    order_by_operator->add_child(std::move(child_phy_oper));
  }

  oper = unique_ptr<PhysicalOperator>(order_by_operator);

  LOG_TRACE("create a order by physical operator");
  return rc;
}

RC PhysicalPlanGenerator::create_plan(AggregateLogicalOperator &aggr_oper, unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = aggr_oper.children();

  unique_ptr<PhysicalOperator> child_phy_oper;

  RC rc = RC::SUCCESS;
  if (!child_opers.empty()) {
    LogicalOperator *child_oper = child_opers.front().get();
    rc                          = create(*child_oper, child_phy_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create project logical operator's child physical operator. rc=%s", strrc(rc));
      return rc;
    }
  }
  AggregatePhysicalOperator *aggr_operator = new AggregatePhysicalOperator(aggr_oper.aggr_exprs());

  if (child_phy_oper) {
    aggr_operator->add_child(std::move(child_phy_oper));
  }

  aggr_operator->set_group_by_exprs(aggr_oper.get_group_by());
  aggr_operator->set_having_stmt(aggr_oper.get_having());
  aggr_operator->set_having_exprs(aggr_oper.get_having_exprs());
  aggr_operator->set_field_alias(aggr_oper.get_field_alias());
  oper = unique_ptr<PhysicalOperator>(aggr_operator);

  LOG_TRACE("create a project physical operator");
  return rc;
}

RC PhysicalPlanGenerator::create_plan(InsertLogicalOperator &insert_oper, unique_ptr<PhysicalOperator> &oper)
{
  Table                  *table           = insert_oper.table();
  vector<vector<Value>>  &insert_values   = insert_oper.insert_values();
  InsertPhysicalOperator *insert_phy_oper = new InsertPhysicalOperator(table, std::move(insert_values));
  oper.reset(insert_phy_oper);
  return RC::SUCCESS;
}

RC PhysicalPlanGenerator::create_plan(DeleteLogicalOperator &delete_oper, unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = delete_oper.children();

  unique_ptr<PhysicalOperator> child_physical_oper;

  RC rc = RC::SUCCESS;
  if (!child_opers.empty()) {
    LogicalOperator *child_oper = child_opers.front().get();
    rc                          = create(*child_oper, child_physical_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create physical operator. rc=%s", strrc(rc));
      return rc;
    }
  }

  oper = unique_ptr<PhysicalOperator>(new DeletePhysicalOperator(delete_oper.table()));

  if (child_physical_oper) {
    oper->add_child(std::move(child_physical_oper));
  }
  return rc;
}

RC PhysicalPlanGenerator::create_plan(UpdateLogicalOperator &update_oper, unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = update_oper.children();

  std::vector<unique_ptr<PhysicalOperator>> child_physical_opers;

  RC rc = RC::SUCCESS;
  if (!child_opers.empty()) {
    unique_ptr<PhysicalOperator> child_physical_oper;
    LogicalOperator             *child_oper = child_opers.front().get();
    rc                                      = create(*child_oper, child_physical_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create physical operator. rc=%s", strrc(rc));
      return rc;
    }
    child_physical_opers.emplace_back(std::move(child_physical_oper));
  }

  for (auto child_expr = child_opers.begin() + 1; child_expr != child_opers.end(); ++child_expr) {
    LogicalOperator             *child_oper = child_expr->get();
    unique_ptr<PhysicalOperator> child_physical_oper;
    rc = create(*child_oper, child_physical_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create physical operator. rc=%s", strrc(rc));
      return rc;
    }
    child_physical_opers.emplace_back(std::move(child_physical_oper));
  }

  oper = unique_ptr<PhysicalOperator>(new UpdatePhysicalOperator(update_oper.table(),
      std::move(update_oper.field_metas()),
      std::move(update_oper.value_map()),
      std::move(update_oper.select_oper())));

  if (!child_physical_opers.empty()) {
    for (auto &&child_physical_oper : child_physical_opers) {
      oper->add_child(std::move(child_physical_oper));
    }
  }

  return rc;
}

RC PhysicalPlanGenerator::create_plan(ExplainLogicalOperator &explain_oper, unique_ptr<PhysicalOperator> &oper)
{
  vector<unique_ptr<LogicalOperator>> &child_opers = explain_oper.children();

  RC                           rc = RC::SUCCESS;
  unique_ptr<PhysicalOperator> explain_physical_oper(new ExplainPhysicalOperator);
  for (unique_ptr<LogicalOperator> &child_oper : child_opers) {
    unique_ptr<PhysicalOperator> child_physical_oper;
    rc = create(*child_oper, child_physical_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create child physical operator. rc=%s", strrc(rc));
      return rc;
    }

    explain_physical_oper->add_child(std::move(child_physical_oper));
  }

  oper = std::move(explain_physical_oper);
  return rc;
}

RC PhysicalPlanGenerator::create_plan(JoinLogicalOperator &join_oper, unique_ptr<PhysicalOperator> &oper)
{
  RC rc = RC::SUCCESS;

  vector<unique_ptr<LogicalOperator>> &child_opers = join_oper.children();
  if (child_opers.size() != 2) {
    LOG_WARN("join operator should have 2 children, but have %d", child_opers.size());
    return RC::INTERNAL;
  }

  // unique_ptr<PhysicalOperator> join_physical_oper(new NestedLoopJoinPhysicalOperator);
  unique_ptr<PhysicalOperator> join_physical_oper(new NestedLoopJoinPhysicalOperator(join_oper.get_join_stmt()));

  for (auto &child_oper : child_opers) {
    unique_ptr<PhysicalOperator> child_physical_oper;
    rc = create(*child_oper, child_physical_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create physical child oper. rc=%s", strrc(rc));
      return rc;
    }

    join_physical_oper->add_child(std::move(child_physical_oper));
  }
  oper = std::move(join_physical_oper);
  return rc;
}

RC PhysicalPlanGenerator::create_plan(CalcLogicalOperator &logical_oper, std::unique_ptr<PhysicalOperator> &oper)
{
  RC                    rc        = RC::SUCCESS;
  CalcPhysicalOperator *calc_oper = new CalcPhysicalOperator(std::move(logical_oper.expressions()));
  oper.reset(calc_oper);
  return rc;
}

RC PhysicalPlanGenerator::create_plan(ApplyLogicalOperator &logical_oper, std::unique_ptr<PhysicalOperator> &oper)
{
  RC                     rc = RC::SUCCESS;
  ApplyPhysicalOperator *apply_oper =
      new ApplyPhysicalOperator(std::move(logical_oper.comp_expression()), logical_oper.is_and());
  oper.reset(apply_oper);
  for (auto &child_oper : logical_oper.children()) {
    unique_ptr<PhysicalOperator> child_physical_oper;
    rc = create(*child_oper, child_physical_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create physical child oper. rc=%s", strrc(rc));
      return rc;
    }

    oper->add_child(std::move(child_physical_oper));
  }
  return rc;
}