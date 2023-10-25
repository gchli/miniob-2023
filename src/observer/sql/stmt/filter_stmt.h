/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include <vector>
#include <unordered_map>
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/stmt/stmt.h"
// #include "sql/stmt/select_stmt.h"
#include "sql/expr/expression.h"

class Db;
class Table;
class FieldMeta;
class SelectStmt;

struct FilterObj
{
  bool                   is_attr{false};
  bool                   is_value{false};
  bool                   is_expr{false};
  bool                   is_values{false};
  Field                  field;
  Value                  value;
  shared_ptr<Expression> expression;  // maybe normal function or aggregate function  std::vector<Value> values_;
  std::vector<Value>     values_;
  void                   init_attr(const Field &field)
  {
    is_attr     = true;
    this->field = field;
  }

  void init_value(const Value &value)
  {
    is_value    = true;
    this->value = value;
  }

  void init_expr(const shared_ptr<Expression> &&expr)
  {
    is_expr          = true;
    this->expression = expr;
  }

  void init_values(std::vector<Value> &&values)
  {
    is_values = true;
    values_   = std::move(values);
  }
};

class FilterUnit
{
public:
  FilterUnit() = default;
  ~FilterUnit() {}

  void set_comp(CompOp comp) { comp_ = comp; }

  CompOp comp() const { return comp_; }

  void set_left(const FilterObj &obj) { left_ = obj; }
  void set_right(const FilterObj &obj) { right_ = obj; }

  const FilterObj &left() const { return left_; }
  const FilterObj &right() const { return right_; }

private:
  CompOp    comp_ = NO_OP;
  FilterObj left_;
  FilterObj right_;
};

/**
 * @brief Filter/谓词/过滤语句
 * @ingroup Statement
 */
class FilterStmt
{
public:
  FilterStmt() = default;
  virtual ~FilterStmt();

public:
  const std::vector<FilterUnit *> &filter_units() const { return filter_units_; }

public:
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt);

  static RC create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const ConditionSqlNode &condition, FilterUnit *&filter_unit);

private:
  static bool               check_comparable(FilterUnit &filter_unit);
  std::vector<FilterUnit *> filter_units_;  // 默认当前都是AND关系
};

RC SubselctToResult(Stmt *select_stmt, std::vector<Value> &values, bool single_cell_need);

inline FilterUnit create_equal_filter_unit()
{
  FilterUnit filter_unit;
  FilterObj  left_obj;
  left_obj.init_value(Value{1});
  filter_unit.set_left(left_obj);
  FilterObj right_obj;
  filter_unit.set_right(right_obj);
  filter_unit.set_comp(EQUAL_TO);
  return filter_unit;
}

inline FilterUnit create_not_equal_filter_unit()
{
  FilterUnit filter_unit;
  FilterObj  left_obj;
  left_obj.init_value(Value{1});
  filter_unit.set_left(left_obj);
  FilterObj right_obj;
  filter_unit.set_right(right_obj);
  filter_unit.set_comp(EQUAL_TO);
  return filter_unit;
}