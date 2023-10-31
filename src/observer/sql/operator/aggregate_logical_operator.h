#pragma once

#include <memory>
#include <vector>

#include "sql/expr/expression.h"
#include "sql/expr/tuple_cell.h"
#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/field/field.h"

class AggregateLogicalOperator : public LogicalOperator
{
public:
  AggregateLogicalOperator(
      const std::vector<shared_ptr<Expression>> &aggr_exprs, const std::vector<std::string> &field_alias);
  AggregateLogicalOperator(
      const std::vector<shared_ptr<Expression>> &&aggr_exprs, const std::vector<std::string> &&field_alias);

  // AggregateOperator() AggregateOperator(std::vector<std::unique_ptr<Expression>> &&expressions, AggrType aggr_type,
  // const char *table_name, const char *field_name, const char *alias);
  virtual ~AggregateLogicalOperator() = default;

  LogicalOperatorType                             type() const override { return LogicalOperatorType::AGGREGATE; }
  std::vector<std::unique_ptr<Expression>>       &expressions() { return expressions_; }
  const std::vector<std::unique_ptr<Expression>> &expressions() const { return expressions_; }
  const std::vector<std::shared_ptr<Expression>> &aggr_exprs() const { return aggr_exprs_; }
  void                                            set_order_by(const vector<shared_ptr<OrderByStmt>> &order_by_stmt)
  {
    for (const auto &stmt : order_by_stmt) {
      order_by_exprs_.push_back(stmt->get_attr_expr());
      order_by_type_.push_back(stmt->get_order_type());
    }
  }
  void set_group_bys(std::vector<shared_ptr<Expression>> &group_by_exprs) { group_by_exprs_.swap(group_by_exprs); }
  std::vector<shared_ptr<Expression>> &get_group_by() { return group_by_exprs_; }
  const std::vector<OrderType>        &order_by_type() const { return order_by_type_; }
  void                   set_having(FilterStmt *havings) { having_stmt_ = shared_ptr<FilterStmt>(havings); }
  shared_ptr<FilterStmt> get_having() const { return having_stmt_; }
  void set_having_exprs(std::vector<shared_ptr<Expression>> &having_exprs) { having_exprs_.swap(having_exprs); }
  std::vector<shared_ptr<Expression>> &get_having_exprs() { return having_exprs_; }
  const std::vector<std::string>      &field_alias() const { return field_alias_; }

private:
  std::vector<shared_ptr<Expression>> aggr_exprs_;
  std::vector<shared_ptr<Expression>> order_by_exprs_;
  std::vector<OrderType>              order_by_type_;
  std::vector<shared_ptr<Expression>> group_by_exprs_;
  shared_ptr<FilterStmt>              having_stmt_{nullptr};
  std::vector<shared_ptr<Expression>> having_exprs_;
  std::vector<std::string>            field_alias_;
};