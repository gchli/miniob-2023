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
// Created by Wangyunlai on 2021/5/14.
//

#pragma once

#include <cstring>
#include <functional>
#include <memory>
#include <vector>
#include <string>

#include "common/hash.h"
#include "common/log/log.h"
#include "sql/expr/tuple_cell.h"
#include "sql/parser/parse.h"
#include "sql/parser/value.h"
#include "sql/expr/expression.h"
#include "storage/common/limits.h"
#include "storage/record/record.h"

class Table;

/**
 * @defgroup Tuple
 * @brief Tuple 元组，表示一行数据，当前返回客户端时使用
 * @details
 * tuple是一种可以嵌套的数据结构。
 * 比如select t1.a+t2.b from t1, t2;
 * 需要使用下面的结构表示：
 * @code {.cpp}
 *  Project(t1.a+t2.b)
 *        |
 *      Joined
 *      /     \
 *   Row(t1) Row(t2)
 * @endcode
 *
 */

/**
 * @brief 元组的结构，包含哪些字段(这里成为Cell)，每个字段的说明
 * @ingroup Tuple
 */
class TupleSchema
{
public:
  void                 append_cell(const TupleCellSpec &cell) { cells_.push_back(cell); }
  void                 append_cell(const char *table, const char *field) { append_cell(TupleCellSpec(table, field)); }
  void                 append_cell(const char *alias) { append_cell(TupleCellSpec(alias)); }
  int                  cell_num() const { return static_cast<int>(cells_.size()); }
  const TupleCellSpec &cell_at(int i) const { return cells_[i]; }

private:
  std::vector<TupleCellSpec> cells_;
};

/**
 * @brief 元组的抽象描述
 * @ingroup Tuple
 */
class Tuple
{
public:
  Tuple()          = default;
  virtual ~Tuple() = default;

  /**
   * @brief 获取元组中的Cell的个数
   * @details 个数应该与tuple_schema一致
   */
  virtual int cell_num() const = 0;

  /**
   * @brief 获取指定位置的Cell
   *
   * @param index 位置
   * @param[out] cell  返回的Cell
   */
  virtual RC cell_at(int index, Value &cell) const = 0;

  /**
   * @brief 根据cell的描述，获取cell的值
   *
   * @param spec cell的描述
   * @param[out] cell 返回的cell
   */
  virtual RC find_cell(const TupleCellSpec &spec, Value &cell) const = 0;

  virtual std::string to_string() const
  {
    std::string str;
    const int   cell_num = this->cell_num();
    for (int i = 0; i < cell_num - 1; i++) {
      Value cell;
      cell_at(i, cell);
      str += cell.to_string();
      str += ", ";
    }

    if (cell_num > 0) {
      Value cell;
      cell_at(cell_num - 1, cell);
      str += cell.to_string();
    }
    return str;
  }
  virtual Tuple      *copy() const { return nullptr; }
  virtual std::string alias() const { return ""; }
};

/**
 * @brief 一行数据的元组
 * @ingroup Tuple
 * @details 直接就是获取表中的一条记录
 */
class RowTuple : public Tuple
{
public:
  RowTuple() = default;
  virtual ~RowTuple()
  {
    for (FieldExpr *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_record(Record *record) { this->record_ = record; }

  void set_schema(const Table *table, const std::vector<FieldMeta> *fields)
  {
    table_ = table;
    this->speces_.reserve(fields->size());
    for (const FieldMeta &field : *fields) {
      speces_.push_back(new FieldExpr(table, &field));
    }
  }

  int cell_num() const override { return speces_.size(); }

  RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    FieldExpr       *field_expr = speces_[index];
    const FieldMeta *field_meta = field_expr->field().meta();
    cell.set_type(field_meta->type());
    if (is_mem_null(this->record_->data() + field_meta->offset(), field_meta->type(), field_meta->len())) {
      cell.set_null();
      return RC::SUCCESS;
    }
    cell.set_data(this->record_->data() + field_meta->offset(), field_meta->len());
    return RC::SUCCESS;
  }

  RC find_cell(const TupleCellSpec &spec, Value &cell) const override
  {
    const char *table_name = spec.table_name();
    const char *field_name = spec.field_name();
    if (0 != strcmp(table_name, table_->name())) {
      return RC::NOTFOUND;
    }

    for (size_t i = 0; i < speces_.size(); ++i) {
      const FieldExpr *field_expr = speces_[i];
      const Field     &field      = field_expr->field();
      if (0 == strcmp(field_name, field.field_name())) {
        return cell_at(i, cell);
      }
    }
    return RC::NOTFOUND;
  }
  Tuple *copy() const override
  {
    RowTuple *new_tuple  = new RowTuple();
    Record   *new_record = new Record(*record_);
    new_tuple->set_record(new_record);
    new_tuple->set_schema(table_, table_->table_meta().field_metas());
    return new_tuple;
  }
#if 0
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }
#endif

  Record &record() { return *record_; }

  const Record &record() const { return *record_; }

  const Table *table() const { return table_; }

private:
  Record                  *record_ = nullptr;
  const Table             *table_  = nullptr;
  std::vector<FieldExpr *> speces_;
};

/**
 * @brief 从一行数据中，选择部分字段组成的元组，也就是投影操作
 * @ingroup Tuple
 * @details 一般在select语句中使用。
 * 投影也可以是很复杂的操作，比如某些字段需要做类型转换、重命名、表达式运算、函数计算等。
 * 当前的实现是比较简单的，只是选择部分字段，不做任何其他操作。
 */
class ProjectTupleHash;
class ProjectTuple : public Tuple
{
public:
  ProjectTuple() = default;
  virtual ~ProjectTuple()
  {
    for (TupleCellSpec *spec : speces_) {
      // delete spec;
    }
    speces_.clear();
  }
  bool operator==(const ProjectTuple &other) const
  {
    Value value;
    this->cell_at(0, value);
    hash_t this_ret = HashUtil::HashOneCell(value);
    for (int i = 1; i < this->cell_num(); i++) {
      this->cell_at(i, value);
      this_ret = HashUtil::CombineHashes(this_ret, HashUtil::HashOneCell(value));
    }
    other.cell_at(0, value);
    hash_t other_ret = HashUtil::HashOneCell(value);
    for (int i = 1; i < other.cell_num(); i++) {
      other.cell_at(i, value);
      other_ret = HashUtil::CombineHashes(other_ret, HashUtil::HashOneCell(value));
    }
    return this_ret == other_ret;
  }

  void set_tuple(Tuple *tuple) { this->tuple_ = tuple; }

  void add_cell_spec(TupleCellSpec *spec) { speces_.push_back(spec); }
  int  cell_num() const override { return speces_.size(); }

  RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::INTERNAL;
    }
    if (tuple_ == nullptr) {
      return RC::INTERNAL;
    }

    const TupleCellSpec *spec = speces_[index];
    if (spec->expr() != nullptr) {
      return spec->expr()->get_value(*tuple_, cell);
    }
    return tuple_->find_cell(*spec, cell);
  }

  RC find_cell(const TupleCellSpec &spec, Value &cell) const override
  {
    if (spec.expr() != nullptr) {
      return spec.expr()->get_value(*tuple_, cell);
    }
    for (auto spec_ : speces_) {
      if (strcmp(spec.alias(), spec_->alias()) == 0) {
        if (spec_->expr() != nullptr) {
          return spec_->expr()->get_value(*tuple_, cell);
        }
        return tuple_->find_cell(*spec_, cell);
      }
      std::string alias = std::string(spec.table_name()) + "." + spec_->alias();
      if (strcmp(alias.c_str(), spec.alias()) == 0) {
        return tuple_->find_cell(*spec_, cell);
      }
    }
    return tuple_->find_cell(spec, cell);
  }
  Tuple *copy() const override
  {
    ProjectTuple *new_tuple = new ProjectTuple();
    new_tuple->tuple_       = tuple_->copy();
    for (const TupleCellSpec *spec : speces_) {
      auto tcs = new TupleCellSpec(spec->table_name(), spec->field_name(), spec->alias());
      if (spec->expr() != nullptr) {
        tcs->set_expr(spec->expr());
      }
      new_tuple->add_cell_spec(tcs);
    }
    return new_tuple;
  }
#if 0
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::NOTFOUND;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }
#endif
private:
  std::vector<TupleCellSpec *> speces_;
  Tuple                       *tuple_ = nullptr;
};

class ExpressionTuple : public Tuple
{
public:
  ExpressionTuple(std::vector<std::unique_ptr<Expression>> &expressions) : expressions_(expressions) {}
  ExpressionTuple(const ExpressionTuple &other) : expressions_(other.expressions_) {}
  ExpressionTuple(const ExpressionTuple &&other) : expressions_(other.expressions_) {}
  virtual ~ExpressionTuple() {}

  int cell_num() const override { return expressions_.size(); }

  RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(expressions_.size())) {
      return RC::INTERNAL;
    }

    // const Expression *expr = expressions_[index].get();
    const auto &expr = expressions_[index];
    return expr->try_get_value(cell);
  }

  RC find_cell(const TupleCellSpec &spec, Value &cell) const override
  {
    // string alias = spec.field_name() + string(".") + spec.table_name();

    for (const std::unique_ptr<Expression> &expr : expressions_) {
      auto expr_name = expr->alias() == "" ? expr->name() : expr->alias();
      if (expr->type() == ExprType::AGGREGATE) {
        auto aggr_expr = dynamic_cast<AggregateExpr *>(expr.get());
        expr_name      = expr->alias() == "" ? aggr_expr->name(true) : aggr_expr->alias();
      }
      if (0 == strcmp(spec.alias(), expr_name.c_str())) {
        return expr->try_get_value(cell);
      }
    }
    return RC::NOTFOUND;
  }
  Tuple *copy() const override
  {
    ExpressionTuple *new_tuple = new ExpressionTuple(expressions_);
    return new_tuple;
  }

private:
  // const std::vector<std::unique_ptr<Expression>> &expressions_;
  std::vector<std::unique_ptr<Expression>> &expressions_;
};

/**
 * @brief 一些常量值组成的Tuple
 * @ingroup Tuple
 */
class ValueListTuple : public Tuple
{
public:
  ValueListTuple()          = default;
  virtual ~ValueListTuple() = default;

  void set_cells(const std::vector<Value> &cells) { cells_ = cells; }

  virtual int cell_num() const override { return static_cast<int>(cells_.size()); }

  virtual RC cell_at(int index, Value &cell) const override
  {
    if (index < 0 || index >= cell_num()) {
      return RC::NOTFOUND;
    }

    cell = cells_[index];
    return RC::SUCCESS;
  }
  void   add_cell(const Value &cell) { cells_.push_back(cell); }
  Tuple *copy() const override
  {
    ValueListTuple *new_tuple = new ValueListTuple();
    new_tuple->set_cells(cells_);
    return new_tuple;
  }
  virtual RC find_cell(const TupleCellSpec &spec, Value &cell) const override { return RC::INTERNAL; }

private:
  std::vector<Value> cells_;
};

/**
 * @brief 将两个tuple合并为一个tuple
 * @ingroup Tuple
 * @details 在join算子中使用
 */
class JoinedTuple : public Tuple
{
public:
  JoinedTuple() = default;
  JoinedTuple(const JoinedTuple &other) : left_(other.left_), right_(other.right_){};
  JoinedTuple(Tuple *left, Tuple *right) : left_(left), right_(right){};
  JoinedTuple &operator=(const JoinedTuple &other)
  {
    this->left_ = other.get_left(), this->right_ = other.get_right();
    return *this;
  };
  virtual ~JoinedTuple() = default;

  void   set_left(Tuple *left) { left_ = left; }
  void   set_right(Tuple *right) { right_ = right; }
  Tuple *get_left() const { return left_; };
  Tuple *get_right() const { return right_; };
  int    cell_num() const override { return left_->cell_num() + right_->cell_num(); }
  Tuple *copy() const override
  {
    JoinedTuple *new_tuple = new JoinedTuple();
    new_tuple->set_left(left_->copy());
    new_tuple->set_right(right_->copy());
    return new_tuple;
  }

  RC cell_at(int index, Value &value) const override
  {
    const int left_cell_num = left_->cell_num();
    if (index > 0 && index < left_cell_num) {
      return left_->cell_at(index, value);
    }

    if (index >= left_cell_num && index < left_cell_num + right_->cell_num()) {
      return right_->cell_at(index - left_cell_num, value);
    }

    return RC::NOTFOUND;
  }

  RC find_cell(const TupleCellSpec &spec, Value &value) const override
  {
    RC rc = left_->find_cell(spec, value);
    if (rc == RC::SUCCESS || rc != RC::NOTFOUND) {
      return rc;
    }

    return right_->find_cell(spec, value);
  }

private:
  Tuple *left_  = nullptr;
  Tuple *right_ = nullptr;
};

class ProjectTupleHash
{
public:
  hash_t operator()(const ProjectTuple &tuple) const
  {
    Value value;
    tuple.cell_at(0, value);
    hash_t ret = HashUtil::HashOneCell(value);
    for (size_t i = 1; i < tuple.cell_num(); i++) {
      tuple.cell_at(i, value);
      ret = HashUtil::CombineHashes(ret, HashUtil::HashOneCell(value));
    }
    return ret;
  }
};