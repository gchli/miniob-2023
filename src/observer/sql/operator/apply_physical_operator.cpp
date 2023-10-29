#include "sql/operator/apply_physical_operator.h"
#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/physical_operator.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/db/db.h"
#include "storage/trx/trx.h"
#include <memory>

RC ApplyPhysicalOperator::open(Trx *trx) {
    auto &left_child = children_[0];
    RC rc = left_child->open(trx);
    if (rc != RC::SUCCESS) {
        return rc;
    }
    trx_ = trx;
    return RC::SUCCESS;
}

RC ApplySubselect(shared_ptr<Stmt> stmt, std::vector<Value> &values) {
    RC rc = RC::SUCCESS;
    auto select_stmt = dynamic_cast<SelectStmt*>(stmt.get());
    if (select_stmt == nullptr) {
        LOG_ERROR("sub select stmt is not select");
        return RC::INVALID_ARGUMENT;
    }
    unique_ptr<LogicalOperator> logical_oper;
    unique_ptr<PhysicalOperator> physical_oper;
    LogicalPlanGenerator logical_plan_generator;
    PhysicalPlanGenerator physical_plan_generator;
    rc = logical_plan_generator.create(stmt.get(), logical_oper);
    if (rc != RC::SUCCESS) {
        return rc;
    }
    physical_plan_generator.create(*logical_oper.get(), physical_oper);
    if (rc != RC::SUCCESS) {
        return rc;
    }
    rc = physical_oper->open(nullptr);
    if (rc != RC::SUCCESS) {
        return rc;
    }
    while ((rc = physical_oper->next()) == RC::SUCCESS) {
        auto tuple = physical_oper->current_tuple();
        Value value;
        tuple->cell_at(0, value);
        values.push_back(value);
    }

    if (rc == RC::RECORD_EOF) {
        return RC::SUCCESS;
    }
    return rc;
}

RC ApplyPhysicalOperator::next() {
    /**
     1. left child next
     2. put left tuple to CTX
     3. for expr:
        3.1 build stmt(other create), logical, physical
        3.2 expr get value
     4. return tuple if right return true
     5. loop left until right return true
    */
    auto &table_oper = children_[0];
    RC rc = RC::SUCCESS;
    auto &ctx = FilterCtx::get_instance();
    while ((rc = table_oper->next()) == RC::SUCCESS) {
        Tuple *tuple = table_oper->current_tuple();
        auto row_tuple = dynamic_cast<RowTuple*>(tuple);
        ctx.tuple_maps_[row_tuple->table()->name()] = row_tuple;

        bool is_true = true;
        bool is_all_true = true;
        for (auto &expr : comp_expressions_) {
            auto comp_expr = dynamic_cast<ComparisonExpr*>(expr.get());
            unique_ptr<Expression> left_expr = comp_expr->left()->clone();
            unique_ptr<Expression> right_expr = comp_expr->right()->clone();
            auto op = comp_expr->comp();
            if (left_expr->type() == ExprType::SELECT) {
                // std::cout << "left is select";
                auto select_expr = dynamic_cast<SelectExpr*>(left_expr.get());
                auto select_stmt = select_expr->select_stmt();
                vector<Value> values;
                rc = ApplySubselect(select_stmt, values);
                if (rc != RC::SUCCESS) {
                    return rc;
                }
                left_expr = make_unique<ValueExpr>(values[0]);
            }
            if (right_expr->type() == ExprType::SELECT) {
                // std::cout << "right is select";
                auto select_expr = dynamic_cast<SelectExpr*>(right_expr.get());
                auto select_stmt = select_expr->select_stmt();
                vector<Value> values;
                rc = ApplySubselect(select_stmt, values);
                if (rc != RC::SUCCESS) {
                    return rc;
                }
                if (values.size() == 1 && !is_values_op(op)) {
                    right_expr = make_unique<ValueExpr>(values[0]);
                } else {
                    right_expr = make_unique<ValuesExpr>(values);
                }
                // right_expr = make_unique<ValueExpr>(value);
            }
            auto new_comp = ComparisonExpr(op, std::move(left_expr), std::move(right_expr));
            Value value;
            new_comp.get_value(*tuple, value);
            if (!value.get_boolean()) {
                is_all_true = false;
            } else {
                is_true = true;
            }
        }

        if (is_true && !is_and_) {
            tuple_ = tuple;
            return RC::SUCCESS;
        }
        if (is_all_true && is_and_) {
            tuple_ = tuple;
            return RC::SUCCESS;
        }
    }
    return RC::RECORD_EOF;
}

RC ApplyPhysicalOperator::close() {
    return RC::SUCCESS;
}

Tuple *ApplyPhysicalOperator::current_tuple() {
    return tuple_;
}