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
#include "sql/parser/value.h"
#include <cstddef>

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
  round_done_   = true;

  rc   = left_->open(trx);
  trx_ = trx;

  while (rc == RC::SUCCESS) {

    bool left_need_step = (left_tuple_ == nullptr);

    if (round_done_) {
      left_need_step = true;
    }

    if (left_need_step) {
      rc = left_next();
      if (rc != RC::SUCCESS) {
        break;
      }
      rc = right_next();
      if (rc != RC::SUCCESS) {
        if (rc == RC::RECORD_EOF) {
          left_need_step = true;
        } else {
          break;
        }
      }
    } else {
      rc = right_next();
      if (rc != RC::SUCCESS) {
        if (rc == RC::RECORD_EOF) {
          left_need_step = true;
        } else {
          break;
        }
        if (left_need_step) {
          rc = left_next();
          if (rc != RC::SUCCESS) {
            break;
          }
        }
        rc = right_next();
      }
    }
    // if (round_done_) {
    //   left_need_step = true;
    // } else {
    //   rc = right_next();
    //   if (rc != RC::SUCCESS) {
    //     if (rc == RC::RECORD_EOF) {
    //       left_need_step = true;
    //     } else {
    //       break;
    //     }
    //   } else {
    //     if (join_stmt_ == nullptr) {
    //       joined_tuples_.push_back(JoinedTuple(joined_tuple_.get_left(), joined_tuple_.get_right()));
    //       continue;
    //     }
    //   }
    // }

    // if (left_need_step) {
    //   rc = left_next();
    //   if (rc != RC::SUCCESS) {
    //     break;
    //   }
    // }

    // rc = right_next();

    if (join_stmt_ == nullptr) {
      if (joined_tuple_.get_left() != nullptr && joined_tuple_.get_right() != nullptr) {
        joined_tuples_.push_back(JoinedTuple(joined_tuple_.get_left(), joined_tuple_.get_right()));
      }
      continue;
    }

    bool        filter_stmt_result = true;
    const auto &filter             = join_stmt_->get_filter();
    if (filter != nullptr) {
      for (const auto &filter_unit : filter->filter_units()) {
        auto  left_filer_obj  = filter_unit->left();
        auto  right_filer_obj = filter_unit->right();
        Value left_value, right_value;
        if (left_filer_obj.is_attr) {
          TupleCellSpec left_spec(left_filer_obj.field.table_name(), left_filer_obj.field.field_name());
          joined_tuple_.find_cell(left_spec, left_value);
        } else {
          left_value = left_filer_obj.value;
        }
        if (right_filer_obj.is_attr) {
          TupleCellSpec right_spec(right_filer_obj.field.table_name(), right_filer_obj.field.field_name());
          joined_tuple_.find_cell(right_spec, right_value);
        } else {
          right_value = right_filer_obj.value;
        }
        auto      comp_type     = filter_unit->comp();
        const int comp_result   = left_value.compare(right_value);
        bool      filter_result = false;
        switch (comp_result) {
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
      if (filter_stmt_result) {
        if (joined_tuple_.get_left() != nullptr && joined_tuple_.get_right() != nullptr) {
          joined_tuples_.push_back(JoinedTuple(joined_tuple_.get_left(), joined_tuple_.get_right()));
        }
        continue;
      }
    }
  }

  return rc == RC::RECORD_EOF ? RC::SUCCESS : rc;
}

RC NestedLoopJoinPhysicalOperator::next()
{
  // if (left_tuple_ == nullptr || right_tuple_ == nullptr) {
  //   return RC::RECORD_EOF;
  // }
  if (joined_tuples_.empty()) {
    return RC::RECORD_EOF;
  }
  if (cur_index_ == joined_tuples_.size()) {
    return RC::RECORD_EOF;
  }
  return RC::SUCCESS;
  // bool left_need_step = (left_tuple_ == nullptr);
  // RC   rc             = RC::SUCCESS;
  // if (round_done_) {
  //   left_need_step = true;
  // } else {
  //   rc = right_next();
  //   if (rc != RC::SUCCESS) {
  //     if (rc == RC::RECORD_EOF) {
  //       left_need_step = true;
  //     } else {
  //       return rc;
  //     }
  //   } else {
  //     return rc;  // got one tuple from right
  //   }
  // }

  // if (left_need_step) {
  //   rc = left_next();
  //   if (rc != RC::SUCCESS) {
  //     return rc;
  //   }
  // }

  // rc = right_next();
  // return rc;
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

Tuple *NestedLoopJoinPhysicalOperator::current_tuple()
{
  // return &joined_tuple_;
  // empty table join
  assert(!joined_tuples_.empty());
  assert(cur_index_ < joined_tuples_.size());
  return &joined_tuples_[cur_index_++];
}

RC NestedLoopJoinPhysicalOperator::left_next()
{
  RC rc = RC::SUCCESS;
  rc    = left_->next();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  left_tuple_ = left_->current_tuple()->copy();
  joined_tuple_.set_left(left_tuple_);
  // joined_tuple_.set_left(left_->current_tuple());
  return rc;
}

RC NestedLoopJoinPhysicalOperator::right_next()
{
  RC rc = RC::SUCCESS;
  if (round_done_) {
    if (!right_closed_) {
      rc            = right_->close();
      right_closed_ = true;
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }

    rc = right_->open(trx_);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    right_closed_ = false;

    round_done_ = false;
  }

  rc = right_->next();
  if (rc != RC::SUCCESS) {
    if (rc == RC::RECORD_EOF) {
      round_done_ = true;
    }
    return rc;
  }

  right_tuple_ = right_->current_tuple()->copy();
  // joined_tuple_.set_right(right_->current_tuple());
  joined_tuple_.set_right(right_tuple_);
  return rc;
}
