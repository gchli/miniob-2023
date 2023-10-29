#pragma once

#include "sql/expr/expression.h"
#include "sql/operator/logical_operator.h"
#include <memory>
#include <queue>

class ApplyLogicalOperator : public LogicalOperator 
{
public:
    ApplyLogicalOperator(std::vector<std::unique_ptr<Expression>> &&expressions, bool is_and) : comp_expressions_(std::move(expressions)), is_and_(is_and)
    {
        // expressions_.emplace_back(std::move(expression));
    }
    virtual ~ApplyLogicalOperator() = default;
    
    LogicalOperatorType type() const override { return LogicalOperatorType::APPLY; }

    std::vector<std::unique_ptr<Expression>>& comp_expression() { return comp_expressions_; }

    bool is_and() const { return is_and_; }

private:
    // TODO(liyh): ugly 但是现在的关系都是AND所以也无所谓了，这里边其实是CompExpr，方便拿到左边和右边的表达式
std::vector<std::unique_ptr<Expression>> comp_expressions_;
bool is_and_;
};