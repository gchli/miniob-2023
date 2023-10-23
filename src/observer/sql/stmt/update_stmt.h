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

#pragma once

#include "common/rc.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include "storage/field/field_meta.h"
#include <string>
#include <unordered_map>

class Table;

struct UpdateUnit {
  const FieldMeta *update_field_meta;
  Value update_value; // maybe expression later
  SelectStmt select_stmt;
  bool is_select;
};

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt 
{
public:
  UpdateStmt() = default;
  UpdateStmt(Table *table, FilterStmt *filter_stmt, std::vector<const FieldMeta *> &&field_metas, std::unordered_map<size_t, Value> &&value_map, std::unordered_map<size_t, SelectStmt> &&select_map);
  ~UpdateStmt() override;

  StmtType type() const override
  {
    return StmtType::UPDATE;
  }
public:
  static RC create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt);

public:
  Table *table() const
  {
    return table_;
  }
  FilterStmt *filter_stmt() const
  {
    return filter_stmt_;
  }
  std::vector<const FieldMeta *> &field_metas()
  {
    return field_metas_;
  }
  std::unordered_map<size_t, Value> &value_map()
  {
    return value_map_;
  }
  std::unordered_map<size_t, SelectStmt> &select_map()
  {
    return select_map_;
  }
  
private:
  Table *table_ = nullptr;
  FilterStmt *filter_stmt_;
  std::vector<const FieldMeta *> field_metas_;
  std::unordered_map<size_t, Value> value_map_;
  std::unordered_map<size_t, SelectStmt> select_map_;
};
