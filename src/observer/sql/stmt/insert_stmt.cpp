/* Copyright (c) 2021OceanBase and/or its affiliates. All rights reserved.
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

#include "sql/stmt/insert_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "sql/parser/value.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "common/date.h"
#include <functional>
#include <memory>
#include <string>

InsertStmt::InsertStmt(Table *table, const std::vector<Value> *insert_values, int insert_amount)
    : table_(table), insert_values_(insert_values), insert_amount_(insert_amount)
{}

RC InsertStmt::create(Db *db, const InsertSqlNode &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || inserts.insert_values.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d",
        db, table_name, static_cast<int>(inserts.insert_values.size()));
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  for (int i = 0; i < inserts.insert_values.size(); i++) {
    // check the fields number
    const Value     *values     = inserts.insert_values[i].data();
    const int        value_num  = static_cast<int>(inserts.insert_values[i].size());
    const TableMeta &table_meta = table->table_meta();
    const int        field_num  = table_meta.field_num() - table_meta.sys_field_num();
    if (field_num != value_num) {
      LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
      return RC::SCHEMA_FIELD_MISSING;
    }

    // check fields type
    const int sys_field_num = table_meta.sys_field_num();
    for (int j = 0; j < value_num; j++) {
      const FieldMeta *field_meta = table_meta.field(j + sys_field_num);
      const AttrType   field_type = field_meta->type();
      const AttrType   value_type = values[j].attr_type();
      if (field_type != value_type) {
        if (field_type == AttrType::TEXTS && value_type == AttrType::CHARS) {
          // auto       &text_hashmap = table->get_text_hashmap();
          // std::string text_hash    = to_string(std::hash<std::string>()(values[j].get_string()));
          // if (text_hashmap.find(text_hash) == text_hashmap.end()) {
          //   text_hashmap.insert({text_hash, make_shared<std::string>(values[j].get_string())});
          // }
          // inserts.insert_values[i][j].set_text_hash(text_hash.c_str());
          LOG_DEBUG("field type mismatch, convert string to text. table=%s, field=%s, field type=%d, value_type=%d",
              table_name, field_meta->name(), field_type, value_type);
          continue;
        }
        if (field_type == AttrType::DATES && value_type == AttrType::CHARS) {
          LOG_DEBUG("field type mismatch, convert string to date. table=%s, field=%s, field type=%d, value_type=%d",
            table_name, field_meta->name(), field_type, value_type);
          if (!is_date_valid(values[j].get_string())) {
            LOG_WARN("invalid date string. table=%s, field=%s, value=%s",
                table_name, field_meta->name(), values[j].get_string().c_str());
            return RC::INVALID_ARGUMENT;
          }
          continue;
        }
        if (field_meta->nullable() && values[j].is_null()) {
          LOG_DEBUG("field is nullable and value is null. table=%s, field=%s, field type=%d, value_type=%d",
              table_name, field_meta->name(), field_type, value_type);
          continue;
        }
        // TODO try to convert the value type to field type
        LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
            table_name, field_meta->name(), field_type, value_type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }
  }

  // everything alright
  stmt = new InsertStmt(table, inserts.insert_values.data(), inserts.insert_values.size());
  return RC::SUCCESS;
}
