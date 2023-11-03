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
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/insert_physical_operator.h"
#include "sql/parser/value.h"
#include "sql/stmt/insert_stmt.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include <regex.h>
#include <vector>

using namespace std;

InsertPhysicalOperator::InsertPhysicalOperator(Table *table, vector<vector<Value>> &&insert_values)
    : table_(table), insert_values_(std::move(insert_values))
{}

RC InsertPhysicalOperator::open(Trx *trx)
{
  std::vector<std::vector<Value>> new_values;
  if (table_->is_view() && table_->is_updatable_view() && table_->table() != nullptr) {
      Table *actual_table = table_->table();
      new_values.resize(insert_values_.size());
      int field_num = actual_table->table_meta().field_num() - table_->table_meta().sys_field_num();    
      int insert_count = insert_values_.size();
      auto offsets = table_->offsets();
      for (int i = 0; i < insert_count; i++) {
        new_values[i].resize(field_num);
        for (int j = 0; j < field_num; j++) {
          new_values[i][j].set_null();
        }
        for (int j = 0; j < insert_values_[i].size(); j++) {
          new_values[i][offsets[j]] = std::move(insert_values_[i][j]);
        }
      }

      insert_values_ = std::move(new_values);
      table_ = actual_table;
  }

  for (const auto &values : insert_values_) {
    Record record;
    RC rc = table_->make_record(static_cast<int>(values.size()), values.data(), record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to make record. rc=%s", strrc(rc));
      return rc;
    }

    rc = trx->insert_record(table_, record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
      return rc;
    }
  }
  
  return RC::SUCCESS;
}

RC InsertPhysicalOperator::next()
{
  return RC::RECORD_EOF;
}

RC InsertPhysicalOperator::close()
{
  return RC::SUCCESS;
}
