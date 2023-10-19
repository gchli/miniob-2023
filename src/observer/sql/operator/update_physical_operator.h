#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/parser/value.h"
#include "storage/table/table.h"
class Trx;
class DeleteStmt;

/**
 * @brief update
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, const std::vector<std::string> &attribute_names, const std::vector<Value> &values)
      : table_(table), attribute_names_(attribute_names), values_(values)
  {}

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

  std::string param() const override;

private:
  Table      *table_ = nullptr;
  std::vector<std::string> attribute_names_;
  std::vector<Value>       values_;
  Trx        *trx_ = nullptr;
};
