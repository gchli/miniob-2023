#pragma once

#include <vector>
#include <unordered_map>
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/stmt.h"
#include "sql/expr/expression.h"

class Db;
class Table;
class FieldMeta;

class OrderByStmt
{
public:
  OrderByStmt() = default;
  OrderByStmt(OrderType order_type, Table *table, const FieldMeta *field_meta)
      : order_type_(order_type), attr_expr_(make_shared<FieldExpr>(table, field_meta))
  {}
  ~OrderByStmt() {}

  OrderType              get_order_type() const { return order_type_; }
  shared_ptr<Expression> get_attr_expr() const { return attr_expr_; }

private:
  OrderType              order_type_;
  shared_ptr<Expression> attr_expr_;
};
