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

#include "sql/stmt/update_stmt.h"
#include "common/log/log.h"
#include "sql/parser/value.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/field/field_meta.h"
#include <cstdint>
#include <vector>

UpdateStmt::UpdateStmt(Table *table, const std::vector<Value> &values, const std::vector<std::string> &attribute_names, FilterStmt *filter_stmt)
    : table_(table), values_(values), attribute_names_(attribute_names), filter_stmt_(filter_stmt)
{}

UpdateStmt::~UpdateStmt()
{
  if (filter_stmt_ != nullptr) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  const char *table_name = update.relation_name.c_str();
  if (nullptr == db || nullptr == table_name ) {
    LOG_WARN("invalid argument. db=%p, table_name=%p",
        db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, table, &table_map, update.conditions.data(), static_cast<int>(update.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  std::vector<std::string> attribute_names;
  std::vector<Value> values;
  int col_cnt = update.update_list.size();
  for (int i = 0; i < col_cnt; i++) {
    const FieldMeta *field_meta;
    const std::string attribute_name = update.update_list[i].attribute_name;
    const Value value = update.update_list[i].value;
    RC rc = table->get_field_meta_by_name(field_meta, attribute_name);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
      return rc;
    }

    if (field_meta->type() != value.attr_type()) {
      if (field_meta->type() == AttrType::DATES && value.attr_type() == AttrType::CHARS) {
        LOG_DEBUG("field type mismatch, convert string to date. table=%s, field=%s, field type=%d, value_type=%d",
          table_name, field_meta->name(), field_meta->type(), value.attr_type());
        if (!is_date_valid(value.get_string())) {
          LOG_WARN("invalid date string. table=%s, field=%s, value=%s",
              table_name, field_meta->name(), value.get_string().c_str());
          return RC::INVALID_ARGUMENT;
        }
      } if (field_meta->nullable() && value.is_null()) {
        LOG_DEBUG("field convert null to nullable. table=%s, field=%s, field type=%d, value_type=%d",
          table_name, field_meta->name(), field_meta->type(), value.attr_type());
      } else {
        rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
        LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
        return rc;         
      }
    }
    attribute_names.emplace_back(update.update_list[i].attribute_name);
    values.emplace_back(update.update_list[i].value);
  }
  stmt = new UpdateStmt(table, values, attribute_names, filter_stmt);

  return RC::SUCCESS;
}
