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

#include "sql/expr/expression.h"
#include "common/date.h"
#include "common/lang/string.h"
#include "common/rc.h"
#include "common/lang/comparator.h"
#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/parser/parse_defs.h"
#include <cmath>
#include <cstddef>
#include <functional>
#include <memory>

using namespace std;

RC FieldExpr::get_value(const Tuple &tuple, Value &value) const
{
  return tuple.find_cell(TupleCellSpec(table_name(), field_name()), value);
}

RC ValueExpr::get_value(const Tuple &tuple, Value &value) const
{
  value = value_;
  return RC::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type) : child_(std::move(child)), cast_type_(cast_type)
{}

CastExpr::~CastExpr() {}

RC CastExpr::cast(const Value &value, Value &cast_value) const
{
  RC rc = RC::SUCCESS;
  if (this->value_type() == value.attr_type()) {
    cast_value = value;
    return rc;
  }

  switch (cast_type_) {
    case BOOLEANS: {
      bool val = value.get_boolean();
      cast_value.set_boolean(val);
    } break;
    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported convert from type %d to %d", child_->value_type(), cast_type_);
    }
  }
  return rc;
}

RC CastExpr::get_value(const Tuple &tuple, Value &cell) const
{
  RC rc = child_->get_value(tuple, cell);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(cell, cell);
}

RC CastExpr::try_get_value(Value &value) const
{
  RC rc = child_->try_get_value(value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, value);
}

////////////////////////////////////////////////////////////////////////////////

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right))
{}

ComparisonExpr::~ComparisonExpr() {}

RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
{

  RC rc = RC::SUCCESS;
  if (comp_ == STR_LIKE || comp_ == STR_NOT_LIKE) {
    if (left.attr_type() == CHARS && left.attr_type() == right.attr_type()) {
      bool cmp_result = left.compare_like(right);
      switch (comp_) {
        case STR_LIKE: result = cmp_result; break;
        case STR_NOT_LIKE: result = !cmp_result; break;
        default: return RC::INTERNAL;
      }
      return rc;
    }
    LOG_ERROR("type is not char for like compare");
    return RC::INTERNAL;
  }

  if (left.is_null() || right.is_null()) {
    switch (comp_) {
      case IS: {
        result = left.is_null() && right.is_null();
      } break;
      case IS_NOT: {
        result = !left.is_null() || !right.is_null();  // de morgan law
      } break;
      default:
        // compare with null is always false
        result = false;
    }
    return rc;
  }

  int cmp_result = left.compare(right);
  result         = false;
  switch (comp_) {
    case IS:  // maybe is is equal?
    case EQUAL_TO: {
      result = (0 == cmp_result);
    } break;
    case LESS_EQUAL: {
      result = (cmp_result <= 0);
    } break;
    case IS_NOT:
    case NOT_EQUAL: {
      result = (cmp_result != 0);
    } break;
    case LESS_THAN: {
      result = (cmp_result < 0);
    } break;
    case GREAT_EQUAL: {
      result = (cmp_result >= 0);
    } break;
    case GREAT_THAN: {
      result = (cmp_result > 0);
    } break;
    default: {
      LOG_WARN("unsupported comparison. %d", comp_);
      rc = RC::INTERNAL;
    } break;
  }

  return rc;
}

RC ComparisonExpr::try_get_value(Value &cell) const
{
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr   *left_value_expr  = static_cast<ValueExpr *>(left_.get());
    ValueExpr   *right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell        = left_value_expr->get_value();
    const Value &right_cell       = right_value_expr->get_value();

    bool value = false;
    RC   rc    = compare_value(left_cell, right_cell, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value) const
{
  Value left_value;
  Value right_value;

  if (comp_ == IN || comp_ == IN_NOT) {
    const auto &values = dynamic_cast<ValuesExpr *>(right_.get())->values();
    bool        in     = false;
    for (const auto right_value : values) {
      bool result = false;
      RC   rc     = left_->get_value(tuple, left_value);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
        return rc;
      }
      if (left_value.compare(right_value) == 0)
        in = true;
    }
    value.set_boolean(in ? (comp_ == IN) : (comp_ == IN_NOT));
    return RC::SUCCESS;
  }

  if (comp_ == EXIST || comp_ == EXIST_NOT) {
    const auto &values = dynamic_cast<ValuesExpr*>(right_.get())->values();
    bool exist = !values.empty();
    value.set_boolean(exist ? (comp_ == EXIST) : (comp_ == EXIST_NOT));
    return RC::SUCCESS;
  }

  if (left_->type() == ExprType::VALUES || right_->type() == ExprType::VALUES) {
  // if (dynamic_cast<ValuesExpr*>(left_.get()) != nullptr && dynamic_cast<ValuesExpr*>(right_.get()) != nullptr) {
    return RC::INVALID_ARGUMENT;
  }

  RC rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }

  bool bool_value = false;
  rc              = compare_value(left_value, right_value, bool_value);
  if (rc == RC::SUCCESS) {
    value.set_boolean(bool_value);
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
ConjunctionExpr::ConjunctionExpr(Type type, vector<unique_ptr<Expression>> &children)
    : conjunction_type_(type), children_(std::move(children))
{}

RC ConjunctionExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    value.set_boolean(true);
    return rc;
  }

  Value tmp_value;
  for (const unique_ptr<Expression> &expr : children_) {
    rc = expr->get_value(tuple, tmp_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
      return rc;
    }
    bool bool_value = tmp_value.get_boolean();
    if ((conjunction_type_ == Type::AND && !bool_value) || (conjunction_type_ == Type::OR && bool_value)) {
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
  value.set_boolean(default_value);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left, Expression *right)
    : arithmetic_type_(type), left_(left), right_(right)
{}
ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : arithmetic_type_(type), left_(std::move(left)), right_(std::move(right))
{}

AttrType ArithmeticExpr::value_type() const
{
  if (!right_) {
    return left_->value_type();
  }

  if (left_->value_type() == AttrType::INTS && right_->value_type() == AttrType::INTS &&
      arithmetic_type_ != Type::DIV) {
    return AttrType::INTS;
  }

  return AttrType::FLOATS;
}

RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();

  switch (arithmetic_type_) {
    case Type::ADD: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() + right_value.get_int());
      } else {
        value.set_float(left_value.get_float() + right_value.get_float());
      }
    } break;

    case Type::SUB: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() - right_value.get_int());
      } else {
        value.set_float(left_value.get_float() - right_value.get_float());
      }
    } break;

    case Type::MUL: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() * right_value.get_int());
      } else {
        value.set_float(left_value.get_float() * right_value.get_float());
      }
    } break;

    case Type::DIV: {
      if (target_type == AttrType::INTS) {
        if (right_value.get_int() == 0) {
          // NOTE:
          // 设置为整数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为整数最大值。
          value.set_int(numeric_limits<int>::max());
        } else {
          value.set_int(left_value.get_int() / right_value.get_int());
        }
      } else {
        if (right_value.get_float() > -EPSILON && right_value.get_float() < EPSILON) {
          // NOTE:
          // 设置为浮点数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为浮点数最大值。
          value.set_float(numeric_limits<float>::max());
        } else {
          value.set_float(left_value.get_float() / right_value.get_float());
        }
      }
    } break;

    case Type::NEGATIVE: {
      if (target_type == AttrType::INTS) {
        value.set_int(-left_value.get_int());
      } else {
        value.set_float(-left_value.get_float());
      }
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
    } break;
  }
  return rc;
}

RC ArithmeticExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_value(left_value, right_value, value);
}

RC ArithmeticExpr::try_get_value(Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

std::string AggregateExpr::name() const { return name(true); }

std::string AggregateExpr::name(bool with_table) const
{
  std::string ret = "";
  switch (aggregate_type_) {
    case MAX_T: ret += "MAX"; break;
    case MIN_T: ret += "MIN"; break;
    case SUM_T: ret += "SUM"; break;
    case COUNT_T: ret += "COUNT"; break;
    case AVG_T: ret += "AVG"; break;
    case FIELD_T: ret += ""; break;
    default: ret += "ERROR_AGGR"; break;
  }

  if (aggregate_type_ != FIELD_T) {
    ret += "(";
  }

  if (with_table) {
    ret += field_.table_name();
    ret += ".";
  }

  if (field_.value_type() == AttrType::UNDEFINED) {
    ret += "*";
  } else {
    ret += field_.field_name();
  }

  if (aggregate_type_ != FIELD_T) {
    ret += ")";
  }
  if (aggregate_type_ != FIELD_T) {
    std::transform(ret.begin(), ret.end(), ret.begin(), [](char const &c) { return std::toupper(c); });
  }
  return ret;
}

RC AggregateExpr::get_value(const Tuple &tuple, Value &value) const
{
  if (!val_.is_null()) {
    value = val_;
  }
  RC rc = RC::SUCCESS;
  if (aggregate_type_ == FIELD_T) {
    field_.get_value(tuple, value);
  } else {
    TupleCellSpec tuple_cell(this->name(true).c_str());
    rc = tuple.find_cell(tuple_cell, value);
  }
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of field expression. rc=%s", strrc(rc));
  }
  // value = val_;
  return rc;
}

RC AggregateExpr::try_get_value(Value &value) const
{
  value = val_;
  return RC::SUCCESS;
}

FunctionExpr::FunctionExpr(FuncType type, const std::shared_ptr<Expression> &first_obj_expr, std::string alias)
    : function_type_(type), first_obj_expr_(first_obj_expr), alias_(alias)
{
  val_.set_null();
}

FunctionExpr::FunctionExpr(FuncType type, const std::shared_ptr<Expression> &first_obj_expr,
    const std::shared_ptr<Expression> &second_obj_expr, std::string alias)
    : function_type_(type), first_obj_expr_(first_obj_expr), second_obj_expr_(second_obj_expr), alias_(alias)
{
  val_.set_null();
}

RC FunctionExpr::get_value(const Tuple &tuple, Value &value) const
{
  if (!val_.is_null()) {
    value = val_;
    return RC::SUCCESS;
  }

  if (function_type_ == LENGTH_T) {
    Value first_val;
    first_obj_expr_->get_value(tuple, first_val);
    if (first_val.attr_type() != CHARS) {
      LOG_WARN("length() can only be used on chars");
      return RC::INVALID_ARGUMENT;
    }
    size_t length = strlen(first_val.data());
    // val_.set_int(static_cast<int>(length));
    value.set_int(static_cast<int>(length));
    return RC::SUCCESS;
  }

  if (function_type_ == ROUND_T) {
    Value first_val, second_val;
    first_obj_expr_->get_value(tuple, first_val);

    if (first_val.attr_type() != FLOATS) {
      LOG_WARN("round() can only be used on floats");
      return RC::INVALID_ARGUMENT;
    }

    float f = first_val.get_float();
    int   r = 0;
    if (second_obj_expr_ != nullptr) {
      second_obj_expr_->get_value(tuple, second_val);
      r = second_val.get_int();
    }
    std::function<int(int)> pow10 = [&](int n) -> int {
      if (n == 0) {
        return 1;
      }
      if (n % 2 == 1) {
        return 10 * pow10(n - 1);
      }
      int half = pow10(n / 2);
      return half * half;
    };
    float pow = pow10(r);
    f         = std::round(f * pow) / pow;
    // val_.set_float(f);
    value.set_float(f);
    return RC::SUCCESS;
  }

  if (function_type_ == DATE_FORMAT_T) {
    Value first_val, second_val;
    if (first_obj_expr_ == nullptr || second_obj_expr_ == nullptr) {
      LOG_WARN("date_format() should have two arguments");
      return RC::INVALID_ARGUMENT;
    }
    first_obj_expr_->get_value(tuple, first_val);
    second_obj_expr_->get_value(tuple, second_val);
    // todo(ligch): 传入参数的合法性检查应该在创建expr之前进行？
    date_u date;
    if (first_val.attr_type() == CHARS) {
      RC rc = str_to_date(first_val.get_string(), date);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    } else if (first_val.attr_type() == DATES) {
      date = first_val.get_date();
    } else {
      LOG_WARN("date_format() can only be used on date");
      return RC::INVALID_ARGUMENT;
    }
    std::string str_format = second_val.get_string();
    std::string formatted_date;
    if (!is_date_valid(date.year, date.month, date.day)) {
      return RC::INVALID_ARGUMENT;
    }
    RC rc = format_to_date(date, str_format, formatted_date);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    value.set_string(formatted_date.c_str());
    return RC::SUCCESS;
  }

  return RC::INVALID_ARGUMENT;
}
std::string FunctionExpr::name() const { return name(true); }
std::string FunctionExpr::name(bool with_table) const
{
  if (alias_ != "") {
    return alias_;
  }
  std::string ret = "";
  switch (function_type_) {
    case LENGTH_T: ret += "LENGTH"; break;
    case DATE_FORMAT_T: ret += "DATE_FORMAT"; break;
    case ROUND_T: ret += "ROUND"; break;
    default: ret += "ERROR_FUNC"; break;
  }
  ret += "(";

  if (with_table) {
    if (first_obj_expr_->type() == ExprType::FIELD) {
      ret += string(first_obj_expr_->table_name()) + ".";
    }
  }

  if (first_obj_expr_->type() == ExprType::FIELD) {
    ret += string(first_obj_expr_->field_name());
  } else {
    ret += string(first_obj_expr_->name());
  }

  if (second_obj_expr_ != nullptr) {
    ret += ", " + second_obj_expr_->name();
  }
  ret += ")";
  // std::transform(ret.begin(), ret.end(), ret.begin(), [](char const &c) { return std::toupper(c); });
  return ret;
}
RC FunctionExpr::create_func_expr(Db *db, const RelAttrSqlNode &attr_node, Table *default_table,
    std::unordered_map<std::string, Table *> *tables, std::unordered_map<std::string, std::string> *tables_alias,
    shared_ptr<FunctionExpr> &func_expr)
{
  if (!attr_node.is_func) {
    func_expr = nullptr;
    return RC::INVALID_ARGUMENT;
  }

  FuncType    func_type       = attr_node.func_type;
  const auto &first_func_arg  = attr_node.first_func_arg;
  const auto &second_func_arg = attr_node.second_func_arg;
  const auto &alias           = attr_node.alias;
  if (second_func_arg.is_valid) {
    if (second_func_arg.is_attr) {
      // round(a, b), date_format(a, b), b can only be values.
      return RC::INVALID_ARGUMENT;
    }
    if (func_type == LENGTH_T) {
      return RC::INVALID_ARGUMENT;
    }
    if (func_type == DATE_FORMAT_T && second_func_arg.value.attr_type() != CHARS) {
      return RC::INVALID_ARGUMENT;
    }
    if (func_type == ROUND_T && second_func_arg.value.attr_type() != INTS) {
      return RC::INVALID_ARGUMENT;
    }
  }
  auto check_func_attr_type = [](FuncType func_type, AttrType attr_type) {
    if (func_type == LENGTH_T && attr_type != CHARS) {
      return RC::INVALID_ARGUMENT;
    }
    if (func_type == DATE_FORMAT_T && attr_type != DATES &&
        attr_type != CHARS) {  // todo: maybe chars can also be allowed
      return RC::INVALID_ARGUMENT;
    }
    if (func_type == ROUND_T && attr_type != INTS && attr_type != FLOATS) {
      return RC::INVALID_ARGUMENT;
    }
    return RC::SUCCESS;
  };
  shared_ptr<Expression> obj_expr{nullptr};
  if (first_func_arg.is_attr) {
    const char      *table_name = first_func_arg.relation_name.c_str();
    const char      *field_name = first_func_arg.attribute_name.c_str();
    Table           *table      = nullptr;
    const FieldMeta *field_meta = nullptr;
    // if ()

    if (!common::is_blank(table_name)) {
      auto iter = tables->find(table_name);
      if (iter == tables->end()) {
        if (tables_alias->find(string(table_name)) == tables_alias->end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        auto table_real_name = tables_alias->find(table_name)->second;
        if (tables->find(table_real_name) == tables->end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        iter = tables->find(table_real_name);
      }
      table      = iter->second;
      field_meta = table->table_meta().field(field_name);
    } else {
      if (tables->size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", field_name);
        return RC::SCHEMA_FIELD_MISSING;
      }
      table      = default_table;
      field_meta = table->table_meta().field(field_name);
    }

    field_meta = table->table_meta().field(field_name);
    if (field_meta == nullptr) {
      // todo(ligch): figure out whether the "*" can appear in function
      if ((0 == strcmp(field_name, "*"))) {
        field_meta = new FieldMeta("*");
      } else {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
        return RC::SCHEMA_FIELD_MISSING;
      }
    }
    RC rc = check_func_attr_type(func_type, field_meta->type());
    if (rc != RC::SUCCESS) {
      return rc;
    }

    obj_expr = make_shared<FieldExpr>(table, field_meta);
  } else {
    RC rc = check_func_attr_type(func_type, first_func_arg.value.attr_type());
    if (rc != RC::SUCCESS) {
      return rc;
    }
    obj_expr = make_shared<ValueExpr>(first_func_arg.value);
  }
  shared_ptr<ValueExpr> second_obj_expr{nullptr};
  if (second_func_arg.is_valid) {
    second_obj_expr = make_shared<ValueExpr>(second_func_arg.value);
    func_expr       = make_shared<FunctionExpr>(func_type, obj_expr, second_obj_expr, alias);
  } else {
    func_expr = make_shared<FunctionExpr>(func_type, obj_expr, alias);
  }

  return RC::SUCCESS;
}