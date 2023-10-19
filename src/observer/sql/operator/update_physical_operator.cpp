#include "sql/operator/update_physical_operator.h"

#include "common/log/log.h"
#include "storage/field/field_meta.h"
#include "storage/record/record.h"

#include "storage/trx/trx.h"
#include "sql/stmt/delete_stmt.h"
#include <sstream>

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

  trx_ = trx;

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  PhysicalOperator *child = children_[0].get();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple  = static_cast<RowTuple *>(tuple);
    Record   &old_record = row_tuple->record();
    Record    new_record;
    rc = table_->make_update_record(new_record, old_record, attribute_names_, values_);
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
  for (int i = 0; i < attribute_names_.size(); i++) {
    ss << " " << this->attribute_names_[i] << "=" << this->values_[i].to_string();
  }
  return ss.str();
}