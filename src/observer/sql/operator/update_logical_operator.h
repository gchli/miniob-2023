#pragma once

#include "sql/operator/logical_operator.h"
#include "sql/stmt/update_stmt.h"
#include "storage/field/field_meta.h"
#include <cstddef>
#include <unordered_map>

/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator 
{
public:
  UpdateLogicalOperator(Table *table, std::vector<const FieldMeta *> &&field_metas, std::unordered_map<size_t, Value> &&value_map, std::unordered_map<size_t, size_t> &&select_oper);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::UPDATE;
  }
  Table *table() const
  {
    return table_;
  }
  std::vector<const FieldMeta *> &field_metas()
  {
    return field_metas_;
  }
  std::unordered_map<size_t, Value> &value_map()
  {
    return value_map_;
  }
  std::unordered_map<size_t, size_t> &select_oper()
  {
    return select_oper_;
  }

private:
  Table *table_ = nullptr;
  std::vector<const FieldMeta *> field_metas_;
  std::unordered_map<size_t, size_t> select_oper_;
  std::unordered_map<size_t, Value> value_map_;
};
