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

#include <memory>
#include <stack>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include "sql/expr/tuple.h"
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
  enum class FilterObjType
  {
    FILTER_OBJ_ATTR,
    FILTER_OBJ_VALUE,
    FILTER_OBJ_EXPR,
    FILTER_OBJ_VALUES,
    FILTER_OBJ_SELECT,
    FILTER_OBJ_FATHRE_ATTR,
  };
  FilterObjType          type;
  bool is_attr() const { return type == FilterObjType::FILTER_OBJ_ATTR; }
  bool is_value() const { return type == FilterObjType::FILTER_OBJ_VALUE; }
  bool is_expr() const { return type == FilterObjType::FILTER_OBJ_EXPR; }
  bool is_values() const { return type == FilterObjType::FILTER_OBJ_VALUES; }
  bool is_select() const { return type == FilterObjType::FILTER_OBJ_SELECT; }
  Field                  field;
  Value                  value;
  shared_ptr<Expression> expression;  // maybe normal function or aggregate function  std::vector<Value> values_;
  std::vector<Value>     values_;
  shared_ptr<Stmt>       select_stmt_;
  void                   init_attr(const Field &field)
  {
    type        = FilterObjType::FILTER_OBJ_ATTR;
    this->field = field;
  }

  void init_value(const Value &value)
  {
    type        = FilterObjType::FILTER_OBJ_VALUE;
    this->value = value;
  }

  void init_expr(const shared_ptr<Expression> &&expr)
  {
    type             = FilterObjType::FILTER_OBJ_EXPR;
    this->expression = expr;
  }

  void init_values(std::vector<Value> &&values)
  {
    type    = FilterObjType::FILTER_OBJ_VALUES;
    values_ = std::move(values);
  }

  void init_values(const std::vector<Value> &values)
  {
    type    = FilterObjType::FILTER_OBJ_VALUES;
    values_ = values;
  }

  void init_select_stmt(const shared_ptr<Stmt> &&select_stmt)
  {
    type         = FilterObjType::FILTER_OBJ_SELECT;
    select_stmt_ = select_stmt;
  }

  void init_father_attr(const Field &field)
  {
    type        = FilterObjType::FILTER_OBJ_FATHRE_ATTR;
    this->field = field;
  }
};

class FilterUnit
{
public:
  FilterUnit() = default;
  ~FilterUnit() {}

  void set_comp(CompOp comp) { comp_ = comp; }
  void set_is_and(bool is_and) { is_and_=is_and; }

  CompOp comp() const { return comp_; }
  bool is_and() const { return is_and_; }

  void set_left(const FilterObj &obj) { left_ = obj; }
  void set_right(const FilterObj &obj) { right_ = obj; }

  const FilterObj &left() const { return left_; }
  const FilterObj &right() const { return right_; }

private:
  bool is_and_ = true; // 用来做不同FilterUnit之间的连接
  CompOp    comp_ = NO_OP;
  FilterObj left_;
  FilterObj right_;
};

class FilterCtx {
public:
  std::unordered_map<std::string, Table *> table_names_;
  std::unordered_map<std::string, Tuple *> tuple_maps_;
  bool contain_sub_select = false;
  static FilterCtx &get_instance() {
    static FilterCtx ctx;
    return ctx;
  }
  void reset() {
    table_names_.clear();
    tuple_maps_.clear();
    contain_sub_select = false;
  }
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
      std::unordered_map<std::string, std::string> *tables_alias, const ConditionSqlNode *conditions, int condition_num,
      FilterStmt *&stmt, bool find_ctx=false);

  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt, bool find_ctx=false);

  static RC create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const ConditionSqlNode &condition, FilterUnit *&filter_unit, bool find_ctx=false);

  static RC create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      std::unordered_map<std::string, std::string> *tables_alias, const ConditionSqlNode &condition,
      FilterUnit *&filter_unit, bool find_ctx=false);

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