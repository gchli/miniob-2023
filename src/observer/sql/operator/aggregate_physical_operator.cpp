#include "common/log/log.h"
#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "storage/field/field.h"
#include <cstddef>
#include <cstring>
#include <memory>
#include <vector>
#include "sql/operator/aggregate_physical_operator.h"

Aggregator::Aggregator(AggregateExpr *expr)
{
  aggr_type_ = expr->aggregate_type();
  field_     = expr->get_field();
  attr_type_ = expr->get_field().attr_type();
  val_       = Value();
  val_.set_null();
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
  if (val.is_null()) {
    return;
  }
  switch (aggr_type_) {
    case MAX_T: {
      if (val_.is_null()) {
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
      if (val_.is_null()) {
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
      if (val.is_null()) {
        // val_ = val;
        break;
      }
      assert(rc == RC::SUCCESS);
      count_++;
      sum_ += val.get_float();
      val_ = val;

    } break;
    case SUM_T: {
      if (val.is_null()) {
        val_ = val;
        break;
      }
      assert(rc == RC::SUCCESS);
      sum_ += val.get_float();
      val_ = val;
    } break;
    case COUNT_T: {
      if (val.is_null()) {
        val_ = val;
        break;
      }
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
    if (val_.is_null()) {
      return val_;
    }
    return Value(FLOATS, (char *)&sum_, sizeof(float));
  }
  if (aggr_type_ == AVG_T) {
    if (val_.is_null()) {
      return val_;
    }
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
  std::vector<shared_ptr<AggregateExpr>> query_aggr_exprs;
  std::vector<shared_ptr<AggregateExpr>> having_aggr_exprs;
  std::vector<shared_ptr<Expression>>    expr_aggr_exprs;
  bool                                   has_arithmetic_expr = false;
  // std::vector<shared_ptr<FieldExpr>>     field_exprs;
  for (const auto &expr : aggr_exprs_) {
    if (expr->type() == ExprType::AGGREGATE) {
      query_aggr_exprs.push_back(dynamic_pointer_cast<AggregateExpr>(expr));
    } else if (expr->type() == ExprType::FIELD) {
      shared_ptr<AggregateExpr> converted_field_expr =
          make_shared<AggregateExpr>(FIELD_T, *dynamic_pointer_cast<FieldExpr>(expr), expr->alias());
      query_aggr_exprs.push_back(converted_field_expr);
    } else if (expr->type() == ExprType::ARITHMETIC) {
      has_arithmetic_expr         = true;
      const auto &arithmetic_expr = dynamic_pointer_cast<ArithmeticExpr>(expr);
      RC          rc = ArithmeticExpr::collect_aggregates_from_arithmetic_expr(arithmetic_expr.get(), expr_aggr_exprs);
    }
  }

  for (const auto &expr : having_exprs_) {
    if (expr->type() == ExprType::AGGREGATE) {
      having_aggr_exprs.push_back(dynamic_pointer_cast<AggregateExpr>(expr));
    } else if (expr->type() == ExprType::FIELD) {
      LOG_ERROR("shouldn't happen.");
    }
  }

  bool has_group_by = !group_by_exprs_.empty();
  if (!has_group_by) {
    for (const auto &expr : query_aggr_exprs) {
      if (expr->aggregate_type() != COUNT_T && expr->field().attr_type() == AttrType::UNDEFINED) {
        return RC::INTERNAL;
      }
      if (expr->aggregate_type() == FIELD_T)
        continue;
      aggregate_table_.add_expr(expr);
    }
    for (const auto &expr : expr_aggr_exprs) {
      const auto &aggr_expr = dynamic_pointer_cast<AggregateExpr>(expr);
      if (aggr_expr->aggregate_type() != COUNT_T && aggr_expr->field().attr_type() == AttrType::UNDEFINED) {
        return RC::INTERNAL;
      }
      aggregate_table_.add_expr(aggr_expr);
    }
    if (has_arithmetic_expr) {
      proj_tuple_ = make_shared<ProjectTuple>();
      int i       = 0;
      for (const auto &expr : aggr_exprs_) {
        TupleCellSpec *spec       = nullptr;
        std::string    expr_alias = field_alias_[i++];
        if (expr_alias != "") {
          spec = new TupleCellSpec(expr_alias.c_str());
        } else {
          spec = new TupleCellSpec(expr->name().c_str());
        }
        spec->set_expr(expr);
        proj_tuple_->add_cell_spec(spec);
      }
    }
    while ((rc = child->next()) == RC::SUCCESS) {
      Tuple *t = child->current_tuple();
      aggregate_table_.add_tuple(t);
    }

    for (const auto &expr : query_aggr_exprs) {
      Value val = aggregate_table_.get_result(expr);
      expr->set_value(val);
      auto aggr_expr_output = make_unique<AggregateExpr>(expr->aggregate_type(), expr->get_field_expr(), expr->alias());
      aggr_expr_output->set_value(val);
      aggr_exprs_output_.emplace_back(std::move(aggr_expr_output));
    }
    for (const auto &expr : expr_aggr_exprs) {
      const auto &aggr_expr = dynamic_pointer_cast<AggregateExpr>(expr);
      Value       val       = aggregate_table_.get_result(aggr_expr);
      aggr_expr->set_value(val);
      auto aggr_expr_output =
          make_unique<AggregateExpr>(aggr_expr->aggregate_type(), aggr_expr->get_field_expr(), expr->alias());
      aggr_expr_output->set_value(val);
      aggr_exprs_output_.emplace_back(std::move(aggr_expr_output));
    }
    shared_ptr<Tuple> expr_tuple = make_shared<ExpressionTuple>(aggr_exprs_output_);

    result_tuples_.emplace_back(std::move(expr_tuple));
    return RC::SUCCESS;
  }

  while ((rc = child->next()) == RC::SUCCESS) {
    Tuple       *cur_tuple = child->current_tuple()->copy();
    ProjectTuple proj_tuple;
    proj_tuple.set_tuple(cur_tuple);

    for (const auto &expr : group_by_exprs_) {
      // 在有子查询之前应该均为fieldexpr
      TupleCellSpec *spec = new TupleCellSpec(expr->table_name(), expr->field_name(), expr->name().c_str());
      proj_tuple.add_cell_spec(spec);
    }

    for (int i = 0; i < proj_tuple.cell_num(); ++i) {
      Value val;
      RC    rc = proj_tuple.cell_at(i, val);
      if (rc != RC::SUCCESS) {
        LOG_WARN("get value failed.");
        return rc;
      }
    }

    if (group_by_tables_.find(proj_tuple) == group_by_tables_.end()) {
      group_by_tables_[proj_tuple] = AggregationTable{};
      // AggregationTable new_aggr_table;
      for (const auto &expr : query_aggr_exprs) {
        if (expr->aggregate_type() == FIELD_T)
          continue;

        group_by_tables_[proj_tuple].add_expr(expr);
      }

      if (!having_exprs_.empty()) {
        for (const auto &expr : having_aggr_exprs) {
          if (expr->aggregate_type() == FIELD_T)
            continue;

          group_by_tables_[proj_tuple].add_expr(expr);
        }
      }
    }
    if (group_by_tables_.find(proj_tuple) == group_by_tables_.end()) {
      LOG_WARN("shouldn't happen.");
    }
    group_by_tables_[proj_tuple].add_tuple(cur_tuple);
  }

  // get result from aggregation table and put them into result_tuples_
  for (auto it = group_by_tables_.begin(); it != group_by_tables_.end(); it++) {
    auto &cur_proj_tuple = it->first;
    auto &cur_aggr_table = it->second;
    aggr_exprs_output_vec_.push_back(make_shared<vector<std::unique_ptr<Expression>>>());

    auto &aggr_exprs_output = aggr_exprs_output_vec_[aggr_exprs_output_vec_.size() - 1];
    auto  tmp_exprs_output  = make_shared<vector<std::unique_ptr<Expression>>>();
    for (const auto &expr : query_aggr_exprs) {
      Value val;
      if (expr->aggregate_type() == FIELD_T) {
        expr->get_value(cur_proj_tuple, val);
      } else {
        val = cur_aggr_table.get_result(expr);
      }
      auto aggr_expr_output = make_unique<AggregateExpr>(expr->aggregate_type(), expr->get_field_expr(), expr->alias());
      aggr_expr_output->set_value(val);
      aggr_exprs_output->push_back(std::move(aggr_expr_output));

      auto tmp_expr_output = make_unique<AggregateExpr>(expr->aggregate_type(), expr->get_field_expr(), expr->alias());
      tmp_expr_output->set_value(val);
      tmp_exprs_output->push_back(std::move(tmp_expr_output));
    }
    for (const auto &expr : having_aggr_exprs) {
      Value val             = cur_aggr_table.get_result(expr);
      auto  tmp_expr_output = make_unique<AggregateExpr>(expr->aggregate_type(), expr->get_field_expr(), expr->alias());
      tmp_expr_output->set_value(val);
      tmp_exprs_output->push_back(std::move(tmp_expr_output));
    }

    shared_ptr<Tuple> expr_tuple = make_shared<ExpressionTuple>(*aggr_exprs_output);

    if (having_stmt_) {
      shared_ptr<Tuple> tmp_expr_tuple = make_shared<ExpressionTuple>(*tmp_exprs_output);
      if (is_tuple_valid(*tmp_expr_tuple, having_stmt_)) {
        result_tuples_.emplace_back(std::move(expr_tuple));
      }
    } else {
      result_tuples_.emplace_back(std::move(expr_tuple));
    }
  }

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

bool AggregatePhysicalOperator::is_tuple_valid(Tuple &tuple, const shared_ptr<FilterStmt> &filter)
{
  bool filter_stmt_result = true;
  for (const auto &filter_unit : filter->filter_units()) {
    auto  left_filer_obj  = filter_unit->left();
    auto  right_filer_obj = filter_unit->right();
    Value left_value, right_value;
    if (left_filer_obj.is_expr()) {
      const auto &expr = left_filer_obj.expression;
      if (expr->type() == ExprType::AGGREGATE) {
        auto aggr_expr = dynamic_pointer_cast<AggregateExpr>(expr);
        RC   rc        = aggr_expr->get_value(tuple, left_value);
        // TupleCellSpec tuple_spec(aggr_expr->name(true).c_str());

        // tuple.find_cell(tuple_spec, left_value);
      } else {
        LOG_WARN("shouldn't have other expr type in having filter obj now");
      }
    } else if (left_filer_obj.is_attr()) {
      // if (left_filer_obj.)
      TupleCellSpec left_spec(left_filer_obj.field.table_name(), left_filer_obj.field.field_name());
      tuple.find_cell(left_spec, left_value);
    } else {
      left_value = left_filer_obj.value;
    }

    if (right_filer_obj.is_expr()) {
      const auto &expr = right_filer_obj.expression;
      if (expr->type() == ExprType::AGGREGATE) {
        auto aggr_expr = dynamic_pointer_cast<AggregateExpr>(expr);
        RC   rc        = aggr_expr->get_value(tuple, right_value);
        if (rc != RC::SUCCESS) {
          LOG_WARN("filter obj get value failed.");
          return false;
        }
      } else {
        LOG_WARN("shouldn't have other expr type in filter obj now");
      }
    } else if (right_filer_obj.is_attr()) {
      TupleCellSpec right_spec(right_filer_obj.field.table_name(), right_filer_obj.field.field_name());
      tuple.find_cell(right_spec, right_value);
    } else {
      right_value = right_filer_obj.value;
    }
    auto      comp_type     = filter_unit->comp();
    const int comp_result   = left_value.compare(right_value);
    bool      filter_result = false;
    if (left_value.is_null() || right_value.is_null()) {
      return false;
    }
    switch (comp_type) {
      case EQUAL_TO: {
        filter_result = (0 == comp_result);
      } break;
      case LESS_EQUAL: {
        filter_result = (comp_result <= 0);
      } break;
      case NOT_EQUAL: {
        filter_result = (comp_result != 0);
      } break;
      case LESS_THAN: {
        filter_result = (comp_result < 0);
      } break;
      case GREAT_EQUAL: {
        filter_result = (comp_result >= 0);
      } break;
      case GREAT_THAN: {
        filter_result = (comp_result > 0);
      } break;
      default: {
        LOG_WARN("invalid compare type: %d", comp_type);
      } break;
    }
    filter_stmt_result = filter_stmt_result && filter_result;
    if (!filter_stmt_result) {
      break;
    }
  }
  return filter_stmt_result;
}
