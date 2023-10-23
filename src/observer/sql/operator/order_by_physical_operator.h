

#pragma once

#include "sql/operator/physical_operator.h"

class OrderByPhysicalOperator : public PhysicalOperator
{
public:
  // OrderByPhysicalOperator() = default;
  OrderByPhysicalOperator(std::vector<shared_ptr<Expression>> &order_by_exprs, std::vector<OrderType> &order_by_type)
  {
    order_by_exprs_.swap(order_by_exprs);
    order_by_type_.swap(order_by_type);
  }
  virtual ~OrderByPhysicalOperator() = default;

  void add_expressions(std::vector<std::unique_ptr<Expression>> &&expressions) {}
  void add_projection(const Table *table, const FieldMeta *field);
  void add_order_by(shared_ptr<Expression> &order_by_expr, OrderType &order_by_type)
  {
    order_by_exprs_.push_back(order_by_expr);
    order_by_type_.push_back(order_by_type);
  }
  PhysicalOperatorType type() const override { return PhysicalOperatorType::PROJECT; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  int cell_num() const { return tuple_->cell_num(); }

  Tuple *current_tuple() override;
  void   set_order_by(std::vector<shared_ptr<Expression>> &order_by_exprs, std::vector<OrderType> &order_by_type)
  {
    order_by_exprs_.swap(order_by_exprs);
    order_by_type_.swap(order_by_type);
  }

private:
  // ProjectTuple                        tuple_;
  shared_ptr<Tuple>                   tuple_;
  std::vector<shared_ptr<Expression>> order_by_exprs_;
  std::vector<OrderType>              order_by_type_;
  std::vector<shared_ptr<Tuple>>      ordered_tuples_;
  int                                 cur_index{0};
};
