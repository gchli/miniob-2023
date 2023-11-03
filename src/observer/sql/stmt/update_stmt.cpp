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
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/db/db.h"
#include "storage/field/field_meta.h"
#include <cstddef>
#include <cstdint>
#include <vector>

UpdateStmt::UpdateStmt(Table *table, FilterStmt *filter_stmt, std::vector<const FieldMeta *> &&field_metas,
    std::unordered_map<size_t, Value> &&value_map, std::unordered_map<size_t, SelectStmt> &&select_map)
    : table_(table),
      filter_stmt_(filter_stmt),
      field_metas_(std::move(field_metas)),
      value_map_(std::move(value_map)),
      select_map_(std::move(select_map))
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
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p",
        db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  if (table->is_view() && !table->is_updatable_view()) {
    return RC::NOT_UPDATABLE_VIEW;
  }

  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(
      db, table, &table_map, update.conditions.data(), static_cast<int>(update.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  size_t                                 col_cnt = update.update_list.size();
  std::vector<const FieldMeta *>         field_metas;
  std::unordered_map<size_t, Value>      value_map;
  std::unordered_map<size_t, SelectStmt> select_map;

  for (int i = 0; i < col_cnt; ++i) {
    const auto       &update_pair = update.update_list[i];
    const FieldMeta  *field_meta;
    const std::string attribute_name = update_pair.attribute_name;
    Value             value          = update_pair.value;
    RC                rc             = table->get_field_meta_by_name(field_meta, attribute_name);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
      return rc;
    }

    if (field_meta->type() != value.attr_type() && !update_pair.is_select) {
      if (field_meta->type() == AttrType::DATES && value.attr_type() == AttrType::CHARS) {
        LOG_DEBUG("field type mismatch, convert string to date. table=%s, field=%s, field type=%d, value_type=%d",
          table_name, field_meta->name(), field_meta->type(), value.attr_type());
        if (!is_date_valid(value.get_string())) {
          LOG_WARN("invalid date string. table=%s, field=%s, value=%s",
              table_name, field_meta->name(), value.get_string().c_str());
          return RC::INVALID_ARGUMENT;
        }
      } else if (field_meta->nullable() && value.is_null()) {
        LOG_DEBUG("field convert null to nullable. table=%s, field=%s, field type=%d, value_type=%d",
          table_name, field_meta->name(), field_meta->type(), value.attr_type());
      } else if (field_meta->type() == TEXTS && value.attr_type() == CHARS) {
        // continue;
      } else if ((rc = value.convert_to(field_meta->type())) != RC::SUCCESS) {
        rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
        LOG_WARN("failed to create update statement. rc=%d:%s", rc, strrc(rc));
        return rc;
      }
    }
    field_metas.emplace_back(field_meta);

    if (update_pair.is_select) {
      Stmt *select_stmt = nullptr;
      rc                = SelectStmt::create(db, update_pair.select, select_stmt);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("failed to create select stmt for update. rc=%d:%s", rc, strrc(rc));
        return rc;
      }
      if (static_cast<SelectStmt *>(select_stmt)->query_exprs().size() != 1) {
        rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
        LOG_WARN("failed to create update statement, not 1 expr", rc, strrc(rc));
        return rc;
      }
      select_map.emplace(i, *static_cast<SelectStmt *>(select_stmt));
    } else {
      value_map.emplace(i, value);
    }
  }
  stmt = new UpdateStmt{table, filter_stmt, std::move(field_metas), std::move(value_map), std::move(select_map)};

  return RC::SUCCESS;
}
