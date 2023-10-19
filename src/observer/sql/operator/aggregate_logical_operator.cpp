#include "sql/operator/aggregate_logical_operator.h"
AggregateLogicalOperator::AggregateLogicalOperator(const std::vector<shared_ptr<Expression>> &aggr_exprs)
    : aggr_exprs_(aggr_exprs){};
AggregateLogicalOperator::AggregateLogicalOperator(const std::vector<shared_ptr<Expression>> &&aggr_exprs)
    : aggr_exprs_(std::move(aggr_exprs)){};