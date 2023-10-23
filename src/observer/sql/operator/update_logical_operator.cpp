#include "sql/operator/update_logical_operator.h"
#include "sql/parser/value.h"
#include "sql/stmt/update_stmt.h"
#include <vector>

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, std::vector<const FieldMeta *> &&field_metas, std::unordered_map<size_t, Value> &&value_map, std::unordered_map<size_t, size_t> &&select_oper)
    : table_(table), field_metas_(std::move(field_metas)), select_oper_(std::move(select_oper)), value_map_(std::move(value_map))
{}