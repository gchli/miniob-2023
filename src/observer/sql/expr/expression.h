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
// Created by Wangyunlai on 2022/07/05.
//

#pragma once

#include <string.h>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "sql/expr/tuple_cell.h"
#include "sql/stmt/stmt.h"
#include "sql/parser/parse_defs.h"
#include "storage/db/db.h"
#include "storage/field/field.h"
#include "sql/parser/value.h"
#include "common/log/log.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"

class Tuple;
class LogicalOperator;
/**
 * @defgroup Expression
 * @brief 表达式
 */

/**
 * @brief 表达式类型
 * @ingroup Expression
 */
enum class ExprType
{
  NONE,
  STAR,         ///< 星号，表示所有字段
  FIELD,        ///< 字段。在实际执行时，根据行数据内容提取对应字段的值
  VALUE,        ///< 常量值
  CAST,         ///< 需要做类型转换的表达式
  COMPARISON,   ///< 需要做比较的表达式
  CONJUNCTION,  ///< 多个表达式使用同一种关系(AND或OR)来联结
  ARITHMETIC,   ///< 算术运算
  AGGREGATE,    ///< 聚合函数
  FUNCTION,     ///< 函数
  SELECT,       ///< 子查询
  VALUES        ///< 多个值
};

/**
 * @brief 表达式的抽象描述
 * @ingroup Expression
 * @details 在SQL的元素中，任何需要得出值的元素都可以使用表达式来描述
 * 比如获取某个字段的值、比较运算、类型转换
 * 当然还有一些当前没有实现的表达式，比如算术运算。
 *
 * 通常表达式的值，是在真实的算子运算过程中，拿到具体的tuple后
 * 才能计算出来真实的值。但是有些表达式可能就表示某一个固定的
 * 值，比如ValueExpr。
 */
class Expression
{
public:
  Expression()          = default;
  virtual ~Expression() = default;

  /**
   * @brief 根据具体的tuple，来计算当前表达式的值。tuple有可能是一个具体某个表的行数据
   */
  virtual RC get_value(const Tuple &tuple, Value &value) const = 0;

  /**
   * @brief 在没有实际运行的情况下，也就是无法获取tuple的情况下，尝试获取表达式的值
   * @details 有些表达式的值是固定的，比如ValueExpr，这种情况下可以直接获取值
   */
  virtual RC try_get_value(Value &value) const { return RC::UNIMPLENMENT; }

  /**
   * @brief 表达式的类型
   * 可以根据表达式类型来转换为具体的子类
   */
  virtual ExprType type() const = 0;

  /**
   * @brief 表达式值的类型
   * @details 一个表达式运算出结果后，只有一个值
   */
  virtual AttrType value_type() const = 0;

  /**
   * @brief 表达式的名字，比如是字段名称，或者用户在执行SQL语句时输入的内容
   */
  virtual std::string name() const { return name_; }
  virtual void        set_name(std::string name) { name_ = name; }

  virtual const char                 *table_name() const { return ""; }
  virtual const char                 *field_name() const { return ""; }
  virtual const Field                 get_field() const { return {}; }
  virtual std::unique_ptr<Expression> clone() const { return nullptr; }

private:
  std::string name_;
};

class ExprContext
{
public:
  std::unordered_map<std::string, shared_ptr<Tuple>> ctx_;
  static ExprContext                                &get_context()
  {
    static ExprContext ctx;
    return ctx;
  }
};

/**
 * @brief 字段表达式
 * @ingroup Expression
 */
class FieldExpr : public Expression
{
public:
  FieldExpr() = default;
  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field) {}
  FieldExpr(const Field &field) : field_(field) {}
  FieldExpr(const string &attr_name) : is_uncompleted_(true), tmp_attribute_name_(attr_name) {}
  FieldExpr(const string &relation_name, const string &attr_name)
      : is_uncompleted_(true), tmp_relation_name_(relation_name), tmp_attribute_name_(attr_name)
  {}
  FieldExpr(const RelAttrSqlNode &attr_node)
      : is_uncompleted_(true),
        tmp_relation_name_(attr_node.relation_name),
        tmp_attribute_name_(attr_node.attribute_name),
        field_alias_(attr_node.alias),
        table_alias_(attr_node.alias)
  {}
  virtual ~FieldExpr() = default;

  ExprType type() const override { return ExprType::FIELD; }
  AttrType value_type() const override { return field_.attr_type(); }

  Field &field() { return field_; }

  const Field &field() const { return field_; }
  const Field  get_field() const override { return field_; }
  void         set_field(const Table *table, const FieldMeta *field_meta)
  {
    is_uncompleted_ = false;
    field_          = Field(table, field_meta);
  }
  const char *table_name() const override { return field_.table_name(); }

  const char *field_name() const override { return field_.field_name(); }

  RC                          get_value(const Tuple &tuple, Value &value) const override;
  const std::string           get_field_alias() const { return field_alias_; }
  void                        set_field_alias(const std::string &alias) { field_alias_ = alias; }
  const std::string           get_table_alias() const { return table_alias_; }
  void                        set_table_alias(const std::string &alias) { table_alias_ = alias; }
  const std::string          &get_tmp_relation_name() const { return tmp_relation_name_; }
  const std::string          &get_tmp_attribute_name() const { return tmp_attribute_name_; }
  const std::string          &get_tmp_alias() const { return tmp_alias_; }
  std::unique_ptr<Expression> clone() const override { return std::make_unique<FieldExpr>(field_); }
  static RC complete_field_expr(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      std::unordered_map<std::string, std::string> *tables_alias, FieldExpr *expr);

private:
  Field       field_;
  std::string field_alias_{""};
  std::string table_alias_{""};
  // when create arithmetic expressions, the parser can't get the table's pointer.
  bool        is_uncompleted_{false};
  std::string tmp_attribute_name_{""};
  std::string tmp_relation_name_{""};
  std::string tmp_alias_{""};
};

/**
 * @brief 常量值表达式
 * @ingroup Expression
 */
class ValueExpr : public Expression
{
public:
  ValueExpr()                                  = default;
  ValueExpr(const ValueExpr &other)            = default;
  ValueExpr &operator=(const ValueExpr &other) = default;
  explicit ValueExpr(const Value &value) : value_(value) {}

  virtual ~ValueExpr() = default;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override
  {
    value = value_;
    return RC::SUCCESS;
  }

  ExprType type() const override { return ExprType::VALUE; }

  AttrType value_type() const override { return value_.attr_type(); }

  void get_value(Value &value) const { value = value_; }

  const Value &get_value() const { return value_; }

  std::unique_ptr<Expression> clone() const override { return std::make_unique<ValueExpr>(value_); }
  std::string                 name() const override { return value_.to_string(); }

private:
  Value value_;
};

class ValuesExpr : public Expression
{
public:
  ValuesExpr() = default;
  explicit ValuesExpr(const std::vector<Value> &values) : values_(values) {}

  virtual ~ValuesExpr() = default;

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::SUCCESS; };
  RC try_get_value(Value &value) const override { return RC::INVALID_ARGUMENT; }

  ExprType type() const override { return ExprType::VALUES; }

  AttrType value_type() const override { return values_[0].attr_type(); }

  void get_value(Value &value) const { value = value_; }

  const Value &get_value() const { return value_; }

  const std::vector<Value> values() const { return values_; }

  std::unique_ptr<Expression> clone() const override { return std::make_unique<ValuesExpr>(values_); }

private:
  std::vector<Value> values_;
  Value              value_{};
};

class SelectExpr : public Expression
{
public:
  SelectExpr() = delete;
  explicit SelectExpr(const shared_ptr<Stmt> &select_stmt) : select_stmt_(select_stmt){};

  virtual ~SelectExpr() = default;

  ExprType type() const override { return ExprType::SELECT; }

  AttrType value_type() const override { return UNDEFINED; }

  RC get_value(const Tuple &tuple, Value &value) const override { return RC::INVALID_ARGUMENT; };

  shared_ptr<Stmt> select_stmt() const { return select_stmt_; }

  std::unique_ptr<Expression> clone() const override { return std::make_unique<SelectExpr>(select_stmt_); }

  // RC get_value(const Tuple &)
private:
  shared_ptr<Stmt> select_stmt_;
  // unique_ptr<LogicalOperator> select_logical_oper_;
};

/**
 * @brief 类型转换表达式
 * @ingroup Expression
 */
class CastExpr : public Expression
{
public:
  CastExpr(std::unique_ptr<Expression> child, AttrType cast_type);
  virtual ~CastExpr();

  ExprType type() const override { return ExprType::CAST; }
  RC       get_value(const Tuple &tuple, Value &value) const override;

  RC try_get_value(Value &value) const override;

  AttrType value_type() const override { return cast_type_; }

  std::unique_ptr<Expression> &child() { return child_; }

private:
  RC cast(const Value &value, Value &cast_value) const;

private:
  std::unique_ptr<Expression> child_;      ///< 从这个表达式转换
  AttrType                    cast_type_;  ///< 想要转换成这个类型
};

/**
 * @brief 比较表达式
 * @ingroup Expression
 */
class ComparisonExpr : public Expression
{
public:
  ComparisonExpr(CompOp comp, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ComparisonExpr();

  ExprType type() const override { return ExprType::COMPARISON; }

  RC get_value(const Tuple &tuple, Value &value) const override;

  AttrType value_type() const override { return BOOLEANS; }

  CompOp comp() const { return comp_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

  /**
   * 尝试在没有tuple的情况下获取当前表达式的值
   * 在优化的时候，可能会使用到
   */
  RC try_get_value(Value &value) const override;

  /**
   * compare the two tuple cells
   * @param value the result of comparison
   */
  RC compare_value(const Value &left, const Value &right, bool &value) const;

private:
  CompOp                      comp_;
  std::unique_ptr<Expression> left_;
  std::unique_ptr<Expression> right_;
};

/**
 * @brief 联结表达式
 * @ingroup Expression
 * 多个表达式使用同一种关系(AND或OR)来联结
 * 当前miniob仅有AND操作
 */
class ConjunctionExpr : public Expression
{
public:
  enum class Type
  {
    AND,
    OR,
  };

public:
  ConjunctionExpr(Type type, std::vector<std::unique_ptr<Expression>> &children);
  virtual ~ConjunctionExpr() = default;

  ExprType type() const override { return ExprType::CONJUNCTION; }

  AttrType value_type() const override { return BOOLEANS; }

  RC get_value(const Tuple &tuple, Value &value) const override;

  Type conjunction_type() const { return conjunction_type_; }

  std::vector<std::unique_ptr<Expression>> &children() { return children_; }

private:
  Type                                     conjunction_type_;
  std::vector<std::unique_ptr<Expression>> children_;
};

/**
 * @brief 算术表达式
 * @ingroup Expression
 */
class ArithmeticExpr : public Expression
{
public:
  enum class Type
  {
    ADD,
    SUB,
    MUL,
    DIV,
    NEGATIVE,
  };

public:
  ArithmeticExpr(Type type, Expression *left, Expression *right);
  ArithmeticExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  virtual ~ArithmeticExpr() = default;

  ExprType type() const override { return ExprType::ARITHMETIC; }

  AttrType value_type() const override;

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override;

  Type arithmetic_type() const { return arithmetic_type_; }

  std::unique_ptr<Expression> &left() { return left_; }
  std::unique_ptr<Expression> &right() { return right_; }

  static RC complete_arithmetic_expr(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      std::unordered_map<std::string, std::string> *tables_alias, ArithmeticExpr *expr);
  static RC collect_fields_from_arithmetic_expr(
      ArithmeticExpr *expr, std::vector<Field> &fields, const char *table_name);
  static RC collect_aggregates_from_arithmetic_expr(ArithmeticExpr *expr, std::vector<shared_ptr<Expression>> &aggrs);
  static RC collect_aggregate_from_arithmetic_expr(
      ArithmeticExpr *expr, std::vector<Field> &fields, const char *table_name);

private:
  RC calc_value(const Value &left_value, const Value &right_value, Value &value) const;

private:
  Type                        arithmetic_type_;
  std::unique_ptr<Expression> left_{nullptr};
  std::unique_ptr<Expression> right_{nullptr};
};

class AggregateExpr : public Expression
{
public:
public:
  AggregateExpr() = default;
  AggregateExpr(AggrType type, FieldExpr field) : aggregate_type_(type), field_(field)
  {  // todo set alias and name;
    val_.set_null();
  }
  AggregateExpr(AggrType type, shared_ptr<Expression> expr) : aggregate_type_(type), expr_(expr)
  {  // todo set alias and name;
    val_.set_null();
  }
  AggregateExpr(AggrType type, const Table *table, const FieldMeta *field_meta)
      : aggregate_type_(type), field_(table, field_meta)
  {}
  AggregateExpr(const RelAttrSqlNode &attr_node)
      : is_uncompleted_(true),
        aggregate_type_(attr_node.aggr_type),
        tmp_relation_name_(attr_node.relation_name),
        tmp_attribute_name_(attr_node.attribute_name),
        tmp_alias_(attr_node.alias),
        alias_(attr_node.alias)
  {}
  AggregateExpr(const AggregateExpr &other) = default;
  virtual ~AggregateExpr()                  = default;  // todo(ligch)

  ExprType    type() const override { return ExprType::AGGREGATE; }
  std::string name() const override;
  std::string name(bool with_table) const;
  AttrType    value_type() const override
  {
    if (aggregate_type_ == AVG_T) {
      return FLOATS;
    } else if (aggregate_type_ == COUNT_T) {
      return INTS;
    }
    return field_.value_type();

    // return AttrType::INTS;
  }

  RC   get_value(const Tuple &tuple, Value &value) const override;
  void set_value(const Value &value) { val_ = value; }
  RC   try_get_value(Value &value) const override;

  AggrType         aggregate_type() const { return aggregate_type_; }
  const FieldExpr &get_field_expr() const { return field_; }
  const Field      get_field() const override { return field_.field(); }
  void             set_field(const Field &field) { field_ = FieldExpr(field); }
  void        set_field_expr(const Table *table, const FieldMeta *field_meta) { field_ = FieldExpr(table, field_meta); }
  std::string get_alis() const { return alias_; }
  void        set_alis(const char *alis) { this->alias_ = alis; }
  const Field       &field() { return field_.field(); }
  const char        *table_name() const override { return field_.table_name(); }
  const char        *field_name() const override { return field_.field_name(); }
  const std::string &get_tmp_relation_name() const { return tmp_relation_name_; }
  const std::string &get_tmp_attribute_name() const { return tmp_attribute_name_; }
  const std::string &get_tmp_alias() const { return tmp_alias_; }
  static RC complete_aggregate_expr(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      std::unordered_map<std::string, std::string> *tables_alias, AggregateExpr *expr);
  const shared_ptr<Expression> &get_expr() const { return expr_; }
  void                          set_expr(shared_ptr<Expression> &expr) { expr_ = expr; }

private:
  AggrType               aggregate_type_;
  FieldExpr              field_;
  std::string            alias_;
  shared_ptr<Expression> expr_{nullptr};
  bool                   is_uncompleted_{false};
  std::string            tmp_attribute_name_{""};
  std::string            tmp_relation_name_{""};
  std::string            tmp_alias_{""};
  Value                  val_;
};

class FunctionExpr : public Expression
{

public:
  // FunctionExpr(FuncType type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  FunctionExpr(FuncType type, const std::shared_ptr<Expression> &first_obj_expr, std::string alias = "");
  FunctionExpr(FuncType type, const std::shared_ptr<Expression> &first_obj_expr,
      const std::shared_ptr<Expression> &second_obj_expr, std::string alias = "");
  virtual ~FunctionExpr() = default;  // todo(ligch)

  FunctionExpr(const RelAttrSqlNode &attr_node)
      : is_uncompleted_(true), function_type_(attr_node.func_type), tmp_alias_(attr_node.alias), alias_(attr_node.alias)
  {}

  static RC create_func_expr(Db *db, const RelAttrSqlNode &attr_node, Table *default_table,
      std::unordered_map<std::string, Table *> *tables, std::unordered_map<std::string, std::string> *tables_alias,
      shared_ptr<FunctionExpr> &func_expr);

  static RC complete_function_expr(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      std::unordered_map<std::string, std::string> *tables_alias, FunctionExpr *expr);

  ExprType    type() const override { return ExprType::FUNCTION; }
  std::string name() const override;
  std::string name(bool with_table) const;
  AttrType    value_type() const override
  {
    if (function_type_ == LENGTH_T) {
      return INTS;
    } else if (function_type_ == ROUND_T) {
      return FLOATS;
    } else if (function_type_ == DATE_FORMAT_T) {
      return CHARS;
    }
    return val_.attr_type();
  }

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC try_get_value(Value &value) const override
  {
    RC rc = RC::SUCCESS;
    if (!val_.is_null()) {
      value = val_;
      return rc;
    }
    return RC::EMPTY;
  }
  void                    set_first_expr(shared_ptr<Expression> &expr) { first_obj_expr_ = expr; }
  shared_ptr<Expression> &get_first_expr() { return first_obj_expr_; }
  ExprType                get_first_expr_type()
  {
    if (first_obj_expr_ == nullptr) {
      return ExprType::NONE;
    }
    return first_obj_expr_->type();
  }

  void                    set_second_expr(shared_ptr<Expression> &expr) { second_obj_expr_ = expr; }
  shared_ptr<Expression> &get_second_expr() { return second_obj_expr_; }
  ExprType                get_second_expr_type()
  {
    if (second_obj_expr_ == nullptr) {
      return ExprType::NONE;
    }
    return second_obj_expr_->type();
  }
  std::string &get_alias() { return alias_; }
  FuncType     function_type() const { return function_type_; }
  bool         obj_is_val() const { return first_obj_expr_ != nullptr && first_obj_expr_->type() == ExprType::VALUE; }
  void         set_name(std::string name) override { alias_ = name; }

  const char *table_name() const override
  {
    if (first_obj_expr_ != nullptr && first_obj_expr_->type() == ExprType::FIELD) {
      return first_obj_expr_->table_name();
    }
    return "";
  }
  const char *field_name() const override
  {
    if (first_obj_expr_ != nullptr && first_obj_expr_->type() == ExprType::FIELD) {
      return first_obj_expr_->table_name();
    }
    return "";
  }
  const Field get_field() const override
  {
    if (first_obj_expr_ != nullptr && first_obj_expr_->type() == ExprType::FIELD) {
      return first_obj_expr_->get_field();
    }
    return {};
  }

  const FuncArgSqlNode &get_tmp_first_func_arg() const { return tmp_first_func_arg_; }
  const FuncArgSqlNode &get_tmp_second_func_arg() const { return tmp_second_func_arg_; }
  const std::string    &get_tmp_alias() const { return tmp_alias_; }

private:
  FuncType function_type_{UNDEFINED_T};

  shared_ptr<Expression> first_obj_expr_{nullptr};
  shared_ptr<Expression> second_obj_expr_{nullptr};
  std::string            alias_{""};

  bool is_uncompleted_{false};

  std::string    tmp_alias_{""};
  FuncArgSqlNode tmp_first_func_arg_;
  FuncArgSqlNode tmp_second_func_arg_;
  mutable Value  val_;
};