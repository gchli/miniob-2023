#pragma once

#include "sql/expr/expression.h"
#include "sql/operator/aggregate_logical_operator.h"
#include "sql/operator/physical_operator.h"
#include "sql/expr/tuple.h"
#include <cassert>
#include <memory>
#include <tuple>
#include <vector>
#include "common/hash.h"
#include "sql/parser/value.h"
#include "sql/stmt/filter_stmt.h"
class ProjectTuple;

class TupleHash
{
public:
  hash_t operator()(const ProjectTuple &tuple) const
  {
    Value value;
    tuple.cell_at(0, value);
    hash_t ret = hash_one_cell(value);
    for (size_t i = 1; i < tuple.cell_num(); i++) {
      tuple.cell_at(i, value);
      ret = HashUtil::CombineHashes(ret, hash_one_cell(value));
    }
    return ret;
  }

  hash_t hash_one_cell(const Value &val) const
  {
    AttrType type      = val.attr_type();
    size_t   type_hash = HashUtil::Hash(&type);
    size_t   val_hash  = HashUtil::HashBytes(val.data(), val.length());
    return HashUtil::CombineHashes(type_hash, val_hash);
  }
};

class Aggregator
{
public:
  Aggregator(AggregateExpr *expr);
  Aggregator(shared_ptr<AggregateExpr> expr);
  void  add_tuple(Tuple *tuple);
  Value get_result();

private:
  Field    field_;
  AggrType aggr_type_;
  AttrType attr_type_;
  Value    val_;
  float    sum_{0};
  float    avg_;
  int      count_{0};
};

class AggregationTable
{
public:
  AggregationTable() = default;
  void  add_expr(shared_ptr<AggregateExpr> expr);
  void  add_tuple(Tuple *t);
  Value get_result(shared_ptr<AggregateExpr> expr);

private:
  std::unordered_map<shared_ptr<AggregateExpr>, Aggregator> ht_;
};

class AggregatePhysicalOperator : public PhysicalOperator
{
public:
  AggregatePhysicalOperator(const std::vector<std::shared_ptr<Expression>> &aggr_exprs) : aggr_exprs_(aggr_exprs)
  {
    val_.set_null();
  }

  virtual ~AggregatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::AGGREGATE; }

  std::string name() const override { return "AGGREGATE"; }
  std::string param() const override { return ""; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  int cell_num() const { return aggr_exprs_.size(); }
  // void add_expr_to_tupel(const Table *table, const FieldMeta *field_meta)
  Tuple *current_tuple() override
  {
    assert(cur_index_ < result_tuples_.size());
    return result_tuples_[cur_index_++].get();
  }

  const std::vector<std::shared_ptr<Expression>> &aggr_exprs() const { return aggr_exprs_; }
  void set_group_by_exprs(std::vector<shared_ptr<Expression>> group_by_exprs) { group_by_exprs_.swap(group_by_exprs); };
  const std::vector<std::shared_ptr<Expression>> &group_by_exprs() const { return group_by_exprs_; }
  void                         set_having_stmt(shared_ptr<FilterStmt> having_stmt) { having_stmt_ = having_stmt; }
  const shared_ptr<FilterStmt> get_having_stmt() const { return having_stmt_; }
  void set_having_exprs(std::vector<shared_ptr<Expression>> having_expr) { having_exprs_.swap(having_expr); }
  const std::vector<std::shared_ptr<Expression>> &get_having_exprs() const { return having_exprs_; }

private:
  bool is_tuple_valid(Tuple &tuple, const shared_ptr<FilterStmt> &filter);

  std::vector<std::shared_ptr<Expression>>                             aggr_exprs_;
  AggregationTable                                                     aggregate_table_;
  std::unordered_map<ProjectTuple, AggregationTable, ProjectTupleHash> group_by_tables_;

  std::vector<std::unique_ptr<Expression>>                          aggr_exprs_output_;
  std::vector<shared_ptr<std::vector<std::unique_ptr<Expression>>>> aggr_exprs_output_vec_;
  int                                                               cur_index_{0};
  vector<shared_ptr<Tuple>>                                         result_tuples_;
  Value                                                             val_;
  std::vector<shared_ptr<Expression>>                               group_by_exprs_;
  shared_ptr<FilterStmt>                                            having_stmt_{nullptr};
  std::vector<shared_ptr<Expression>>                               having_exprs_;
};