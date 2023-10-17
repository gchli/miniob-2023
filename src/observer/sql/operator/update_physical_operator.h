#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/parser/value.h"

class Trx;
class DeleteStmt;

/**
 * @brief update
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, const std::string &attribute_name, const Value &value) : table_(table), attribute_name_(attribute_name), value_(value)
  {}

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::UPDATE;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override
  {
    return nullptr;
  }

private:
  Table *table_ = nullptr;
  std::string attribute_name_;
  Value value_;
  Trx *trx_ = nullptr;
};
