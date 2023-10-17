#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator 
{
public:
  UpdateLogicalOperator(Table *table, const std::string &attribute_name, const Value &value);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::UPDATE;
  }
  Table *table() const
  {
    return table_;
  }
  Value value() const
  {
    return value_;
  }
  std::string attribute_name() const {
    return attribute_name_;
  }

private:
  Table *table_ = nullptr;
  std::string attribute_name_;
  Value value_;
};
