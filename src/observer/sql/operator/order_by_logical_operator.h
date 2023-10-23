#pragma once

#include <vector>
#include <memory>

#include "sql/operator/logical_operator.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/field/field.h"

class OrderByLogicalOperator : public LogicalOperator
{
public:
  OrderByLogicalOperator() = default;
  OrderByLogicalOperator(const vector<shared_ptr<OrderByStmt>> &order_by_stmts);
  virtual ~OrderByLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::ORDER_BY; }

  std::vector<std::unique_ptr<Expression>>       &expressions() { return expressions_; }
  const std::vector<std::unique_ptr<Expression>> &expressions() const { return expressions_; }

  std::vector<shared_ptr<Expression>> &order_by_exprs() { return order_by_exprs_; }
  std::vector<OrderType>              &order_by_type() { return order_by_type_; }

private:
  // std::vector<shared_ptr<Expression>> proj_exprs_;
  std::vector<shared_ptr<Expression>> order_by_exprs_;
  std::vector<OrderType>              order_by_type_;
};
