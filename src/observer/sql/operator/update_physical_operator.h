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
  UpdatePhysicalOperator(Table *table, std::vector<const FieldMeta *> &&field_metas, std::unordered_map<size_t, Value> &&value_map, std::unordered_map<size_t, size_t> &&select_oper)
  : table_(table), field_metas_(std::move(field_metas)), select_oper_(std::move(select_oper)), value_map_(std::move(value_map))
  {
  };

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

  std::string param() const override;

private:
  Table      *table_ = nullptr;
  std::vector<const FieldMeta *> field_metas_;
  std::unordered_map<size_t, size_t> select_oper_;
  std::unordered_map<size_t, Value> value_map_;
  Trx        *trx_ = nullptr;
  bool wrong_select_ = false;
};
