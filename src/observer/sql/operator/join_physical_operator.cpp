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
// Created by WangYunlai on 2022/12/30.
//

#include "sql/operator/join_physical_operator.h"
#include "common/rc.h"
#include "sql/expr/tuple.h"
#include "sql/parser/value.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/limits.h"
#include <cstddef>
#include <memory>
#include <vector>

NestedLoopJoinPhysicalOperator::NestedLoopJoinPhysicalOperator() {}

RC NestedLoopJoinPhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 2) {
    LOG_WARN("nlj operator should have 2 children");
    return RC::INTERNAL;
  }

  RC rc         = RC::SUCCESS;
  left_         = children_[0].get();
  right_        = children_[1].get();
  right_closed_ = true;

  rc = left_->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open left oper. rc=%s", strrc(rc));
    return rc;
  }

  rc = right_->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open right oper. rc=%s", strrc(rc));
    return rc;
  }

  get_all_tuples(left_, left_tuples_);
  get_all_tuples(right_, right_tuples_);

  trx_ = trx;

  return rc;
}

RC NestedLoopJoinPhysicalOperator::next()
{
  if (left_tuples_.empty() || right_tuples_.empty()) {
    return RC::RECORD_EOF;
  }
  while (get_next_joined_tuple()) {
    if (join_stmt_ == nullptr) {
      return RC::SUCCESS;
    }

    const auto &filter = join_stmt_->get_filter();
    if (filter == nullptr) {
      return RC::SUCCESS;
    }

    bool filter_result = is_tuple_valid(filter);
    if (filter_result) {
      return RC::SUCCESS;
    }
  }
  return RC::RECORD_EOF;
}

RC NestedLoopJoinPhysicalOperator::close()
{
  RC rc = left_->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close left oper. rc=%s", strrc(rc));
  }

  if (!right_closed_) {
    rc = right_->close();
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to close right oper. rc=%s", strrc(rc));
    } else {
      right_closed_ = true;
    }
  }
  return rc;
}

Tuple *NestedLoopJoinPhysicalOperator::current_tuple() { return &joined_tuple_; }

bool NestedLoopJoinPhysicalOperator::is_tuple_valid(const shared_ptr<FilterStmt> &filter)
{
  bool filter_stmt_result = true;
  for (const auto &filter_unit : filter->filter_units()) {
    auto  left_filer_obj  = filter_unit->left();
    auto  right_filer_obj = filter_unit->right();
    Value left_value, right_value;
    if (left_filer_obj.is_attr()) {
      TupleCellSpec left_spec(left_filer_obj.field.table_name(), left_filer_obj.field.field_name());
      joined_tuple_.find_cell(left_spec, left_value);
    } else {
      left_value = left_filer_obj.value;
    }
    if (right_filer_obj.is_attr()) {
      TupleCellSpec right_spec(right_filer_obj.field.table_name(), right_filer_obj.field.field_name());
      joined_tuple_.find_cell(right_spec, right_value);
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

bool NestedLoopJoinPhysicalOperator::get_next_joined_tuple()
{
  if (right_tuples_.empty() || left_tuples_.empty()) {
    return false;
  }
  if (right_index_ == right_tuples_.size() && left_index_ == left_tuples_.size() - 1) {
    return false;
  }
  if (right_index_ == right_tuples_.size()) {
    right_index_ = 0;
    left_index_++;
  }
  joined_tuple_.set_left(left_tuples_[left_index_]);
  joined_tuple_.set_right(right_tuples_[right_index_++]);
  return true;
}

RC NestedLoopJoinPhysicalOperator::get_all_tuples(PhysicalOperator *oper, vector<Tuple *> &tuples)
{
  RC rc = RC::SUCCESS;
  while (RC::SUCCESS == (rc = oper->next())) {
    tuples.push_back(oper->current_tuple()->copy());
  }
  return rc;
}
