#pragma once

#include "sql/expr/expression.h"
#include "sql/operator/physical_operator.h"
#include <memory>
#include <vector>

class ApplyPhysicalOperator : public PhysicalOperator
{
public:
  ApplyPhysicalOperator(std::vector<std::unique_ptr<Expression>> &&comp_expressions, bool is_and) : comp_expressions_(std::move(comp_expressions)), is_and_(is_and) {};
  virtual ~ApplyPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::APPLY; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

private:
  std::vector<std::unique_ptr<Expression>> comp_expressions_;
  bool is_and_;
  Trx *trx_;
  Tuple *tuple_;
};