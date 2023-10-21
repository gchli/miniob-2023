#pragma once

#include <vector>
#include <unordered_map>
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/stmt.h"
#include "sql/expr/expression.h"

class Db;
class Table;
class FieldMeta;

class JoinStmt
{
public:
  JoinStmt() = default;
  JoinStmt(Table *table, shared_ptr<FilterStmt> filter_stmt) : table_(table), filter_stmt_(filter_stmt) {}
  ~JoinStmt() {}

  void                   set_filter() {}
  shared_ptr<FilterStmt> get_filter() const { return filter_stmt_; }
  void                   set_table() {}
  //   shared_ptr<Table>      get_table() const { return table_; }
  Table *get_table() const { return table_; }

private:
  //   shared_ptr<Table>      table_;
  Table                 *table_;
  shared_ptr<FilterStmt> filter_stmt_;
};
