#include "sql/operator/update_logical_operator.h"
#include "sql/parser/value.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, const std::vector<std::string> &attribute_names, const std::vector<Value> &values)
    : table_(table), attribute_names_(attribute_names), values_(values)
{}