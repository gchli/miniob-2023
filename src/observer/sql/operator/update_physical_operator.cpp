#include "sql/operator/update_physical_operator.h"

#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/value.h"
#include "storage/field/field_meta.h"
#include "storage/record/record.h"

#include "storage/trx/trx.h"
#include "sql/stmt/delete_stmt.h"
#include <sstream>
#include <vector>

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];
  RC                                 rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  for (auto&& child : children_) {
    rc = child->open(trx);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to open child operator: %s", strrc(rc));
      return rc;
    }
  }

  for (auto pair : select_oper_) {
    PhysicalOperator *oper = children_[pair.second].get();
    Value value;
    rc = oper->next();
    if (rc != RC::SUCCESS) {
      if (rc == RC::RECORD_EOF) {
        LOG_INFO("no record found for update-select, fill with null");
        value.set_null();
        value_map_[pair.first] = value;
        continue;
      }
      LOG_WARN("failed to next child operator: %s", strrc(rc));
      return rc;
    }
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }
    if (tuple->cell_num() != 1) {
      LOG_WARN("invalid tuple cell num: %d to update", tuple->cell_num());
      return RC::INVALID_ARGUMENT;
    }
    rc = tuple->cell_at(0, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get cell value: %s", strrc(rc));
      return rc;
    }
    value_map_[pair.first] = value;
    rc = oper->next();
    if (rc != RC::RECORD_EOF) {
      LOG_WARN("more than one record in update-select");
      wrong_select_ = true;
    }
    rc = oper->close();
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to close child operator: %s", strrc(rc));
      return rc;
    }
  }

  trx_ = trx;

  while (RC::SUCCESS == (rc = child->next())) {
    if (wrong_select_) {
      LOG_WARN("more than one record in update-select");
      return RC::INVALID_ARGUMENT;
    }

    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    if (!table_->is_view()) {
      RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
      Record &record = row_tuple->record();
      records.emplace_back(record);
    } else {
      RowTuple *row_tuple = static_cast<RowTuple*>(static_cast<ProjectTuple *>(tuple)->get_tuple());
      Record &record = row_tuple->record();
      records.emplace_back(record);
    }
    // rc = trx_->delete_record(table_, record);
    // if (rc != RC::SUCCESS) {
    //   LOG_WARN("failed to delete record: %s", strrc(rc));
    //   return rc;
    // }
  }
  if (table_->is_view()) {
    Table *actual_table = table_->table();
    table_ = actual_table;
  }

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  while (!records.empty()) {
    Record old_record = records.back();
    records.pop_back();
    Record    new_record;
    rc = table_->make_update_record(new_record, old_record, field_metas_, value_map_);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
    new_record.set_rid(old_record.rid());
    rc = trx_->update_record(table_, old_record, new_record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
  }

  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}

std::string UpdatePhysicalOperator::param() const {
  std::stringstream ss;
  ss << this->table_->name();
  for (int i = 0; i < field_metas_.size(); i++) {
    ss << " " << this->field_metas_[i]->name();
  }
  return ss.str();
}