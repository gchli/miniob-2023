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
// Created by Wangyunlai.wyl on 2021/5/18.
//

#include "storage/index/index_meta.h"
#include "sql/parser/parse_defs.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "json/json.h"
#include <algorithm>

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");
const static Json::StaticString FIELD_UNIQUE("unique");

RC IndexMeta::init(const char *name, const std::vector<const FieldMeta *> &field_metas, bool unique)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  unique_ = unique;
  for (const auto &file_meta : field_metas) {
    fields_.emplace_back(file_meta->name());
  }
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME] = name_;
  Json::Value fields_value;
  for (const std::string &field : fields_) {
    Json::Value field_value;
    field_value[FIELD_NAME] = field;
    fields_value.append(std::move(field_value));
  }
  json_value[FIELD_FIELD_NAME] = std::move(fields_value);
  json_value[FIELD_UNIQUE] = unique_;
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &fields_value = json_value[FIELD_FIELD_NAME];
  const Json::Value &unique_value = json_value[FIELD_UNIQUE];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!fields_value.isArray()) {
    LOG_ERROR("Field names of index [%s] is not an array. json value=%s",
        name_value.asCString(),
        fields_value.toStyledString().c_str());
    return RC::INTERNAL;
  }
  int field_num = fields_value.size();
  std::vector<const FieldMeta *> fields(field_num);
  for (int i = 0; i < field_num; i++) {
    const Json::Value &field_value = fields_value[i];
    if (!field_value[FIELD_NAME].isString()) {
      LOG_ERROR("field name is not a string. json value=%s", field_value.toStyledString().c_str());
      return RC::INTERNAL;
    }
    const char *field_name = field_value[FIELD_NAME].asCString();
    const FieldMeta *field = table.field(field_name);
    if (nullptr == field) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    fields[i] = field;
  }

  if (!unique_value.asBool()) {
    LOG_ERROR("unique value not a bool. json value=%s", unique_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  return index.init(name_value.asCString(), fields, unique_value.asBool());
}

const char *IndexMeta::name() const
{
  return name_.c_str();
}

const std::vector<std::string> IndexMeta::fields() const
{
  return fields_;
}

const bool IndexMeta::unique() const {
  return unique_;
}

void IndexMeta::desc(std::ostream &os) const
{
  os << "index name=" << name_ << ", field=";
  for (const auto &field : fields_) {
    os << field << ",";
  }
  os << "unique:" << unique_ << ",";
}