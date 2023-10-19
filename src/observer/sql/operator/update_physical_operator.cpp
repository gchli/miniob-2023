#include "sql/operator/update_physical_operator.h"

#include "common/log/log.h"
#include "sql/operator/delete_physical_operator.h"
#include "storage/field/field_meta.h"
#include "storage/record/record.h"

#include "storage/trx/trx.h"
#include "sql/stmt/delete_stmt.h"

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

  const FieldMeta *field_meta;
  rc = table_->get_field_meta_by_name(field_meta, attribute_name_);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }
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
    rc = table_->make_update_record(new_record, old_record, attribute_name_, value_);
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
    // rc = trx_->delete_record(table_, old_record);
    // if (rc != RC::SUCCESS) {
    //   LOG_WARN("failed to update record: %s", strrc(rc));
    //   return rc;
    // }

    // rc = trx_->insert_record(table_, new_record);
    // if (rc != RC::SUCCESS) {
    //   LOG_WARN("failed to update record by transaction. rc=%s", strrc(rc));
    // }
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
