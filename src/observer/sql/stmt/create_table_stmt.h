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
// Created by Wangyunlai on 2023/6/13.
//

#pragma once

#include <string>
#include <vector>

#include "sql/stmt/stmt.h"

class Db;

/**
 * @brief 表示创建表的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class CreateTableStmt : public Stmt
{
public:
  CreateTableStmt(const std::string &table_name, const std::vector<AttrInfoSqlNode> &attr_infos)
      : table_name_(table_name), attr_infos_(attr_infos)
  {}
  CreateTableStmt(const std::string &table_name, const std::vector<AttrInfoSqlNode> &attr_infos,
      std::shared_ptr<std::vector<std::vector<Value>>> values)
      : table_name_(table_name), attr_infos_(attr_infos), values_(values), create_select_(true)
  {}
  virtual ~CreateTableStmt() = default;

  StmtType type() const override { return StmtType::CREATE_TABLE; }

  const std::string                  &table_name() const { return table_name_; }
  const std::vector<AttrInfoSqlNode> &attr_infos() const { return attr_infos_; }

  static RC                                         create(Db *db, const CreateTableSqlNode &create_table, Stmt *&stmt);
  bool                                              is_create_select() { return create_select_; }
  void                                              set_create_select(bool select) { create_select_ = select; }
  std::shared_ptr<std::vector<std::vector<Value>>> &get_values() { return values_; };
  void set_values(std::shared_ptr<std::vector<std::vector<Value>>> values) { values_ = values; }

private:
  std::shared_ptr<std::vector<std::vector<Value>>> values_{nullptr};
  bool                                             create_select_{false};
  std::string                                      table_name_;
  std::vector<AttrInfoSqlNode>                     attr_infos_;
};

RC CreateSelectToValues(Stmt *select_stmt, std::shared_ptr<std::vector<std::vector<Value>>> &values);