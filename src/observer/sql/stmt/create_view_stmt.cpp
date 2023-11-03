#include "sql/stmt/create_view_stmt.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/create_table_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/field/field.h"
#include "storage/field/field_meta.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

RC CreateViewStmt::create(Db *db, CreateViewSqlNode &create_view, Stmt *&stmt)
{
  stmt = nullptr;

  // for (auto &attr : create_view.select->attributes) {
  //   std::string alias;
  //   if (attr.expr->type() == ExprType::FIELD) {
  //     alias = create_view.view_name + '.' + attr.expr->name();
  //   } else {
  //     alias = create_view.view_name + '.' + attr.alias;
  //   }
  //   attr.alias = alias;
  // }
  // 1. 创建一个SelectStmt
  Stmt *select_stmt = nullptr;
  RC rc = SelectStmt::create(db, *create_view.select, select_stmt);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  bool is_updatable_view = true;
  is_updatable_view = static_cast<SelectStmt*>(select_stmt)->tables().size() > 1 ? false : true;

  std::vector<std::string> fields;
  std::vector<AttrInfoSqlNode> attributes;
  std::unordered_map<std::string, std::shared_ptr<Expression>> view_field_map;
  const auto &exprs = dynamic_cast<SelectStmt*>(select_stmt)->query_exprs();
  const auto &alias = dynamic_cast<SelectStmt*>(select_stmt)->field_alias();
  bool use_attr = create_view.attributes.size() > 0;
  for (size_t i = 0; i < exprs.size(); i++) {
    if (use_attr) {
      fields.emplace_back(create_view.attributes[i]);
    } else if (alias[i] == "") {
      fields.emplace_back(exprs[i]->name());
    } else {
      fields.emplace_back(alias[i]);
    }
    attributes.emplace_back(AttrInfoSqlNode{exprs[i]->value_type(), fields.back(), 4, true});
    view_field_map.emplace(fields.back(), exprs[i]);
    if (exprs[i]->type() != ExprType::FIELD) {
      is_updatable_view = false;
    }
  }

  std::vector<int> offsets; // select b, a from table1; b a在原表中的fields下表，方便更新与重建
  Table *table;
  if (is_updatable_view) {
    table = db->find_table(static_cast<SelectStmt*>(select_stmt)->tables()[0]->name());
    for (size_t i = 0; i < exprs.size(); i++) {
      auto field_expr = static_cast<FieldExpr*>(exprs[i].get());
      auto field_name = field_expr->field_name();
      int offset;
      rc = table->get_field_offset_in_fields(offset, field_name);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
        return rc;
      }
      offsets.emplace_back(offset);
    }
  }

  SelectStmt *select_stmt_ptr = static_cast<SelectStmt*>(select_stmt);
  auto &field_alias = select_stmt_ptr->field_alias();
  auto &query_exprs = select_stmt_ptr->query_exprs();
  int col_cnt = field_alias.size();
  for (int i = 0; i < col_cnt; i++) {
      field_alias[i] = create_view.view_name + '.' + fields[i];
  }

  // 2. 创建CreateViewStmt
  stmt = new CreateViewStmt(create_view.view_name, select_stmt, fields, attributes, is_updatable_view, offsets, table);
  // Stmt *select_stmt;
  // RC    rc = SelectStmt::create(db, *create_view.select, select_stmt);
  // if (rc != RC::SUCCESS) {
  //   LOG_WARN("error create select statement for create");
  //   return rc;
  // }
  // std::vector<AttrInfoSqlNode> attr_infos;
  // for (auto &expr : static_cast<SelectStmt *>(select_stmt)->query_exprs()) {
  //   attr_infos.emplace_back(AttrInfoSqlNode{expr->value_type(), expr->name_create(), 4, true});
  // }
  // auto values = std::make_shared<std::vector<std::vector<Value>>>();
  // rc          = CreateSelectToValues(select_stmt, values);
  // if (rc != RC::SUCCESS) {
  //   LOG_WARN("error collect select values for create");
  //   return rc;
  // }

  // stmt = new CreateTableStmt(create_view.view_name, attr_infos, values);

  return RC::SUCCESS;
}