#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/operator/aggregate_physical_operator.h"
#include "sql/parser/value.h"
#include "storage/field/field.h"
#include <cstring>
#include <memory>
#include <vector>

Aggregator::Aggregator(AggregateExpr *expr)
{
  aggr_type_ = expr->aggregate_type();
  field_     = expr->get_field();
  attr_type_ = expr->get_field().attr_type();
  val_       = Value();
  val_.set_type(NULLS);
}

Aggregator::Aggregator(shared_ptr<AggregateExpr> expr) : Aggregator(expr.get()) {}

void Aggregator::add_tuple(Tuple *tuple)
{
  bool is_star = (field_.attr_type() == AttrType::UNDEFINED);
  if (is_star) {
    assert(aggr_type_ == COUNT_T);
    count_++;
    return;
  }
  Value val;
  RC    rc = tuple->find_cell(TupleCellSpec(field_.table_name(), field_.field_name()), val);

  switch (aggr_type_) {
    case MAX_T: {
      if (val_.attr_type() == NULLS) {
        val_ = val;
        break;
      }
      int compare_res = val.compare(val_);
      assert(rc == RC::SUCCESS);
      if (compare_res > 0) {
        val_ = val;
      }
    } break;
    case MIN_T: {
      // todo(ligch): maybe bugs here
      if (val.attr_type() == NULLS) {
        val_ = val;
        break;
      }
      int compare_res = val.compare(val_);
      assert(rc == RC::SUCCESS);
      if (compare_res < 0) {
        val_ = val;
      }
    } break;
    case AVG_T: {
      assert(rc == RC::SUCCESS);
      count_++;
      sum_ += val.get_float();
      val_ = val;

    } break;
    case SUM_T: {
      assert(rc == RC::SUCCESS);
      sum_ += val.get_float();
      val_ = val;
    } break;
    case COUNT_T: {
      assert(rc == RC::SUCCESS);
      count_++;
      val_ = val;
    } break;
    default: LOG_ERROR("unknown aggregation type\n"); break;
  }
}

Value Aggregator::get_result()
{
  if (aggr_type_ == MAX_T || aggr_type_ == MIN_T) {
    return val_;
  }
  if (aggr_type_ == COUNT_T) {
    return Value(INTS, (char *)&count_, sizeof(int));
  }
  if (aggr_type_ == SUM_T) {
    return Value(FLOATS, (char *)&sum_, sizeof(float));
  }
  if (aggr_type_ == AVG_T) {
    avg_ = sum_ / count_;
    return Value(FLOATS, (char *)&avg_, sizeof(float));
  }
  assert(false);
  return Value{};
}

void AggregationTable::add_expr(shared_ptr<AggregateExpr> expr)
{
  auto iter = ht_.find(expr);
  if (iter != ht_.end()) {
    return;
  }
  ht_.insert({expr, Aggregator(expr)});
}

void AggregationTable::add_tuple(Tuple *t)
{
  for (auto it = ht_.begin(); it != ht_.end(); it++) {
    it->second.add_tuple(t);
  }
}

Value AggregationTable::get_result(shared_ptr<AggregateExpr> expr)
{
  assert(ht_.count(expr));
  return ht_.at(expr).get_result();
}

RC AggregatePhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_WARN("aggregate operator should have 1 child.");
    return RC::INTERNAL;
  }
  const auto &child = children_[0];
  RC          rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("open child failed.");
    return rc;
  }
  // todo(ligch): 目前应该只有aggr_exprs, 之后需要扩展
  std::vector<shared_ptr<AggregateExpr>> aggr_exprs;
  for (const auto &expr : aggr_exprs_) {
    if (expr->type() == ExprType::AGGREGATE) {
      aggr_exprs.push_back(dynamic_pointer_cast<AggregateExpr>(expr));
    }
  }

  for (const auto &expr : aggr_exprs) {
    if (expr->aggregate_type() != COUNT_T && expr->field().attr_type() == AttrType::UNDEFINED) {
      return RC::INTERNAL;
    }
    aggregate_table_.add_expr(expr);
  }

  while ((rc = child->next()) == RC::SUCCESS) {
    Tuple *t = child->current_tuple();
    aggregate_table_.add_tuple(t);
  }

  for (const auto &expr : aggr_exprs) {
    Value val = aggregate_table_.get_result(expr);
    expr->set_value(val);
    aggr_exprs_output_.emplace_back(make_unique<ValueExpr>(val));
  }
  ExpressionTuple expr_tuple{aggr_exprs_output_};
  // result_tuples_.reserve(1);
  result_tuples_.emplace_back(expr_tuple);
  return RC::SUCCESS;
}

RC AggregatePhysicalOperator::next()
{
  if (cur_index_ == result_tuples_.size()) {
    return RC::RECORD_EOF;
  }
  return RC::SUCCESS;
}
RC AggregatePhysicalOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}
