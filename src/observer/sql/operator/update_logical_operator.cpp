#include "sql/operator/update_logical_operator.h"
#include "sql/parser/value.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, const std::string &attribute_name, const Value &value)
    : table_(table), attribute_name_(attribute_name), value_(value)
{}