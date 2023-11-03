#include "sql/executor/create_view_executor.h"

#include "session/session.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/create_view_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/table/table.h"
#include "sql/stmt/create_table_stmt.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "storage/db/db.h"

RC CreateViewExecutor::execute(SQLStageEvent *sql_event)
{
  Stmt    *stmt    = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::CREATE_VIEW,
      "create table executor can not run this command: %d",
      static_cast<int>(stmt->type()));

  CreateViewStmt *create_view_stmt = static_cast<CreateViewStmt *>(stmt);

  std::vector<AttrInfoSqlNode> attributes;

  // RC rc = session->get_current_db()->create_view(create_view_stmt->view_name().c_str(), create_view_stmt->fields(), create_view_stmt->select_stmt());
  RC rc = session->get_current_db()->create_table(create_view_stmt->view_name().c_str(), create_view_stmt->attributes().size(), create_view_stmt->attributes().data());
  Table *table = session->get_current_db()->find_table(create_view_stmt->view_name().c_str());
  table->set_is_view(true);
  table->set_view_select(create_view_stmt->select_stmt());
  table->set_is_updatable_view(create_view_stmt->is_updatable_view());
  table->set_offsets(create_view_stmt->offsets());
  table->set_table(create_view_stmt->table());
  // static_cast<SelectStmt*>(create_view_stmt->select_stmt())->query_exprs()

  return RC::SUCCESS;
}