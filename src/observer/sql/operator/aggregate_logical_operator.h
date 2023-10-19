#pragma once

#include <memory>
#include <vector>

#include "sql/expr/expression.h"
#include "sql/expr/tuple_cell.h"
#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"
#include "storage/field/field.h"

class AggregateLogicalOperator : public LogicalOperator
{
public:
  AggregateLogicalOperator(const std::vector<shared_ptr<Expression>> &aggr_exprs);
  AggregateLogicalOperator(const std::vector<shared_ptr<Expression>> &&aggr_exprs);

  // AggregateOperator() AggregateOperator(std::vector<std::unique_ptr<Expression>> &&expressions, AggrType aggr_type,
  // const char *table_name, const char *field_name, const char *alias);
  virtual ~AggregateLogicalOperator() = default;

  LogicalOperatorType                             type() const override { return LogicalOperatorType::AGGREGATE; }
  std::vector<std::unique_ptr<Expression>>       &expressions() { return expressions_; }
  const std::vector<std::unique_ptr<Expression>> &expressions() const { return expressions_; }
  const std::vector<std::shared_ptr<Expression>> &aggr_exprs() const { return aggr_exprs_; }

private:
  std::vector<shared_ptr<Expression>> aggr_exprs_;
  // AggrType      aggr_type_;
  // TupleCellSpec cell_spec_;
};