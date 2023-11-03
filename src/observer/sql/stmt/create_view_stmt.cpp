#include "sql/stmt/create_view_stmt.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/create_table_stmt.h"
#include "sql/stmt/select_stmt.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

RC CreateViewStmt::create(Db *db, const CreateViewSqlNode &create_view, Stmt *&stmt)
{
  stmt = nullptr;

  // 1. 创建一个SelectStmt
  Stmt *select_stmt = nullptr;
  RC rc = SelectStmt::create(db, *create_view.select, select_stmt);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  std::vector<std::string> fields;
  std::vector<AttrInfoSqlNode> attributes;
  const auto &exprs = dynamic_cast<SelectStmt*>(select_stmt)->query_exprs();
  const auto &alias = dynamic_cast<SelectStmt*>(select_stmt)->field_alias();
  for (size_t i = 0; i < exprs.size(); i++) {
    if (alias[i] == "") {
      fields.emplace_back(exprs[i]->name());
    } else {
      fields.emplace_back(alias[i]);
    }
    attributes.emplace_back(AttrInfoSqlNode{exprs[i]->value_type(), fields.back(), 4, true});
  }


  // 2. 创建CreateViewStmt
  stmt = new CreateViewStmt(create_view.view_name, select_stmt, fields, attributes);
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