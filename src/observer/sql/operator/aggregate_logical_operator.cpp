#include "sql/operator/aggregate_logical_operator.h"
AggregateLogicalOperator::AggregateLogicalOperator(const std::vector<shared_ptr<Expression>> &aggr_exprs, const std::vector<std::string> &field_alias)
    : aggr_exprs_(aggr_exprs), field_alias_(field_alias){};
AggregateLogicalOperator::AggregateLogicalOperator(const std::vector<shared_ptr<Expression>> &&aggr_exprs, const std::vector<std::string> &&field_alias)
    : aggr_exprs_(std::move(aggr_exprs)), field_alias_(std::move(field_alias)){};