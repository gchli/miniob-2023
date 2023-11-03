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

#include <memory>
#include <string>
#include <vector>

#include "sql/parser/parse_defs.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"

class Db;

/**
 * @brief 表示创建表的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class CreateViewStmt : public Stmt
{
public:
  CreateViewStmt(const std::string &view_name, Stmt *select_stmt, std::vector<std::string> fields, std::vector<AttrInfoSqlNode> attributes, bool is_updatable_view)
        : view_name_(view_name),
          select_stmt_(select_stmt),
          fields_(fields),
          attributes_(attributes),
          is_updatable_view_(is_updatable_view)
  {}
  virtual ~CreateViewStmt() = default;

  StmtType type() const override { return StmtType::CREATE_VIEW; }

  const std::string &view_name() const { return view_name_; }
  Stmt *select_stmt() { return select_stmt_; }
  const std::vector<std::string> &fields() const { return fields_; }
  const std::vector<AttrInfoSqlNode> &attributes() const { return attributes_; }
  bool is_updatable_view() const { return is_updatable_view_; }
  

  static RC create(Db *db, const CreateViewSqlNode &create_view, Stmt *&stmt);

private:
  std::string view_name_;
  Stmt *select_stmt_;
  std::vector<std::string> fields_;
  std::vector<AttrInfoSqlNode> attributes_;
  bool is_updatable_view_;
};