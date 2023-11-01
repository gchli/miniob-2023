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

#include "sql/stmt/create_table_stmt.h"
#include "common/log/log.h"
#include "event/sql_debug.h"
#include "sql/operator/physical_operator.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"
#include "sql/parser/value.h"
#include "sql/stmt/select_stmt.h"
#include "storage/db/db.h"
#include <memory>
#include <vector>

RC CreateSelectToValues(Stmt *select_stmt, std::shared_ptr<std::vector<std::vector<Value>>> &values)
{
  unique_ptr<LogicalOperator> logical_oper;
  LogicalPlanGenerator        logical_plan_generator;
  RC                          rc = RC::SUCCESS;
  rc                             = logical_plan_generator.create(select_stmt, logical_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create logical plan. rc=%s", strrc(rc));
    return rc;
  }
  PhysicalPlanGenerator        physical_plan_generator;
  unique_ptr<PhysicalOperator> physical_oper;
  rc = physical_plan_generator.create(*logical_oper, physical_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create physical plan. rc=%s", strrc(rc));
    return rc;
  }
  rc = physical_oper->open(nullptr);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open physical plan. rc=%s", strrc(rc));
    return rc;
  }
  while (physical_oper->next() == RC::SUCCESS) {
    Tuple *tuple = physical_oper->current_tuple();
    Value  value;
    values->emplace_back(std::vector<Value>());
    for (int i = 0; i < tuple->cell_num(); i++) {
      tuple->cell_at(i, value);
      values->back().emplace_back(value);
    }
  }
  return RC::SUCCESS;
}

RC CreateTableStmt::create(Db *db, const CreateTableSqlNode &create_table, Stmt *&stmt)
{
  if (create_table.select == nullptr) {
    stmt = new CreateTableStmt(create_table.relation_name, create_table.attr_infos);
    sql_debug("create table statement: table name %s", create_table.relation_name.c_str());
  } else {
    Stmt *select_stmt;
    RC    rc = SelectStmt::create(db, *create_table.select, select_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("error create select statement for create");
      return rc;
    }
    std::vector<AttrInfoSqlNode> attr_infos;
    if (!create_table.attr_infos.empty()) {
      attr_infos = create_table.attr_infos;
    } else {
      for (auto &expr : static_cast<SelectStmt *>(select_stmt)->query_exprs()) {
        attr_infos.emplace_back(AttrInfoSqlNode{expr->value_type(), expr->name_create(), 4, true});
      }
    }
    auto values = std::make_shared<std::vector<std::vector<Value>>>();
    rc          = CreateSelectToValues(select_stmt, values);
    if (rc != RC::SUCCESS) {
      LOG_WARN("error collect select values for create");
      return rc;
    }
    stmt = new CreateTableStmt(create_table.relation_name, attr_infos, values);
  }
  return RC::SUCCESS;
}
