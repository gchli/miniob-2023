#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator 
{
public:
  UpdateLogicalOperator(Table *table, const std::vector<std::string> &attribute_names, const std::vector<Value> &values);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::UPDATE;
  }
  Table *table() const
  {
    return table_;
  }
  std::vector<Value> values() const
  {
    return values_;
  }
  std::vector<std::string> attribute_names() const {
    return attribute_names_;
  }

private:
  Table *table_ = nullptr;
  std::vector<std::string> attribute_names_;
  std::vector<Value> values_;
};
