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
// Created by WangYunlai on 2022/07/01.
//

#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include <memory>

RC ProjectPhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC                rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
  if (!order_by_exprs_.empty()) {
    while (RC::SUCCESS == (rc = child->next())) {
      // only jointuple rowtuple implement copy
      ordered_tuples_.push_back(shared_ptr<Tuple>(child->current_tuple()->copy()));
    }
    sort(ordered_tuples_.begin(), ordered_tuples_.end(), [this](shared_ptr<Tuple> t1, shared_ptr<Tuple> t2) {
      for (int i = 0; i < order_by_exprs_.size(); ++i) {
        const auto &order_by_expr = order_by_exprs_[i];
        const auto &order_by_type = order_by_type_[i];
        Value       val1, val2;
        order_by_expr->get_value(*t1, val1);
        order_by_expr->get_value(*t2, val2);
        int comp_result = val1.compare(val2);
        if (comp_result != 0) {
          return order_by_type == ASC_T ? comp_result < 0 : comp_result > 0;
        }
      }
      return true;
    });
  }
  return RC::SUCCESS;
}

RC ProjectPhysicalOperator::next()
{
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }
  if (!order_by_exprs_.empty()) {
    if (cur_index >= ordered_tuples_.size()) {
      return RC::RECORD_EOF;
    }
    tuple_.set_tuple(ordered_tuples_[cur_index++].get());
    return RC::SUCCESS;
  }
  return children_[0]->next();
}

RC ProjectPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}

Tuple *ProjectPhysicalOperator::current_tuple()
{
  if (order_by_exprs_.empty()) {
    tuple_.set_tuple(children_[0]->current_tuple());
  }

  return &tuple_;
}

void ProjectPhysicalOperator::add_projection(const Table *table, const FieldMeta *field_meta)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  TupleCellSpec *spec = new TupleCellSpec(table->name(), field_meta->name(), field_meta->name());
  tuple_.add_cell_spec(spec);
}
