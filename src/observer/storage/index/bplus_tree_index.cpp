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
// Created by wangyunlai.wyl on 2021/5/19.
//

#include "storage/index/bplus_tree_index.h"
#include "common/log/log.h"
#include "storage/common/limits.h"
#include "storage/record/record_manager.h"

BplusTreeIndex::~BplusTreeIndex() noexcept
{
  close();
}

RC BplusTreeIndex::create(const char *file_name, const IndexMeta &index_meta, const std::vector<const FieldMeta *> &field_metas, RecordFileHandler *file_handler)
{
  if (inited_) {
    LOG_WARN("Failed to create index due to the index has been created before. file_name:%s, index:%s, field:%s",
        file_name,
        index_meta.name(),
        index_meta.fields()[0].c_str());
    return RC::RECORD_OPENNED;
  }

  // for (const auto field_meta : field_meta) {
    // field_meta_.emplace_back(*field_meta);
  // }
  
  Index::init(index_meta, *field_metas[0]);
  file_handler_ = file_handler;
  col_count_ = field_metas.size();
  for (size_t i = 0; i < col_count_; i++) {
    offsets_.push_back(field_metas[i]->offset());
    lens_.push_back(field_metas[i]->len());
    types_.push_back(field_metas[i]->type());
  }

  RC rc = index_handler_.create(file_name, field_meta_.type(), field_meta_.len());
  if (RC::SUCCESS != rc) {
    LOG_WARN("Failed to create index_handler, file_name:%s, index:%s, field:%s, rc:%s",
        file_name,
        index_meta.name(),
        index_meta.fields()[0].c_str(),
        strrc(rc));
    return rc;
  }

  inited_ = true;
  LOG_INFO(
      "Successfully create index, file_name:%s, index:%s, field:%s", file_name, index_meta.name(), index_meta.fields()[0].c_str());
  return RC::SUCCESS;
}

RC BplusTreeIndex::open(const char *file_name, const IndexMeta &index_meta, const std::vector<const FieldMeta *> &field_metas, RecordFileHandler *file_handler)
{
  if (inited_) {
    LOG_WARN("Failed to open index due to the index has been initedd before. file_name:%s, index:%s, field:%s",
        file_name,
        index_meta.name(),
        index_meta.fields()[0].c_str());
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta, *field_metas[0]);
  file_handler_ = file_handler;
  col_count_ = field_metas.size();
  for (size_t i = 0; i < col_count_; i++) {
    offsets_.push_back(field_metas[i]->offset());
    lens_.push_back(field_metas[i]->len());
    types_.push_back(field_metas[i]->type());
  }

  RC rc = index_handler_.open(file_name);
  if (RC::SUCCESS != rc) {
    LOG_WARN("Failed to open index_handler, file_name:%s, index:%s, field:%s, rc:%s",
        file_name,
        index_meta.name(),
        index_meta.fields()[0].c_str(),
        strrc(rc));
    return rc;
  }

  inited_ = true;
  LOG_INFO(
      "Successfully open index, file_name:%s, index:%s, field:%s", file_name, index_meta.name(), index_meta.fields()[0].c_str());
  return RC::SUCCESS;
}

RC BplusTreeIndex::close()
{
  if (inited_) {
    LOG_INFO("Begin to close index, index:%s, field:%s", index_meta_.name(), index_meta_.fields()[0].c_str());
    index_handler_.close();
    inited_ = false;
  }
  LOG_INFO("Successfully close index.");
  return RC::SUCCESS;
}

RC BplusTreeIndex::insert_entry(const char *record, const RID *rid)
{
  if (unique_) {
    RC rc;
    IndexScanner *scanner = create_scanner(
      record + field_meta_.offset(), field_meta_.len(), true,
      record + field_meta_.offset(), field_meta_.len(), true
    );
    if (scanner != nullptr) {
      if (col_count_ > 1) {
        RID rid;
        RecordPageHandler record_page_handler;
        record_page_handler.cleanup();
        while ((rc = scanner->next_entry(&rid)) == RC::SUCCESS) {
          Record oldrec;
          file_handler_->get_record(record_page_handler, &rid, true, &oldrec);
          bool all_equal = true;
          for (size_t i = 0; i < col_count_; i++) {
            int off = offsets_[i];
            int len = lens_[i];
            AttrType attr_type = types_[i];
            // if any column is null, don't insert into index
            if (is_mem_null((void *)(record + off), attr_type, len)) {
              all_equal = false;
              // scanner->destroy();
            //   return RC::SUCCESS;
            }
            if (strncmp(record + off, oldrec.data() + off, len) != 0) {
              all_equal = false;
              break;
            }
          }
          if (all_equal) {
            scanner->destroy();
            return RC::RECORD_DUPLICATE_KEY;
          }
        }
      } else {
        RID unused_rid;
        rc = scanner->next_entry(&unused_rid);
        bool is_null = is_mem_null((void *)(record + field_meta_.offset()), field_meta_.type(), field_meta_.len());
        if (rc == RC::SUCCESS && !is_null) {
          scanner->destroy();
          return RC::RECORD_DUPLICATE_KEY;
        }
      }
      scanner->destroy();
    }
  }
  return index_handler_.insert_entry(record + field_meta_.offset(), rid);
}

RC BplusTreeIndex::delete_entry(const char *record, const RID *rid)
{
  return index_handler_.delete_entry(record + field_meta_.offset(), rid);
}

IndexScanner *BplusTreeIndex::create_scanner(
    const char *left_key, int left_len, bool left_inclusive, const char *right_key, int right_len, bool right_inclusive)
{
  BplusTreeIndexScanner *index_scanner = new BplusTreeIndexScanner(index_handler_);
  RC rc = index_scanner->open(left_key, left_len, left_inclusive, right_key, right_len, right_inclusive);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open index scanner. rc=%d:%s", rc, strrc(rc));
    delete index_scanner;
    return nullptr;
  }
  return index_scanner;
}

RC BplusTreeIndex::sync()
{
  return index_handler_.sync();
}

////////////////////////////////////////////////////////////////////////////////
BplusTreeIndexScanner::BplusTreeIndexScanner(BplusTreeHandler &tree_handler) : tree_scanner_(tree_handler)
{}

BplusTreeIndexScanner::~BplusTreeIndexScanner() noexcept
{
  tree_scanner_.close();
}

RC BplusTreeIndexScanner::open(
    const char *left_key, int left_len, bool left_inclusive, const char *right_key, int right_len, bool right_inclusive)
{
  return tree_scanner_.open(left_key, left_len, left_inclusive, right_key, right_len, right_inclusive);
}

RC BplusTreeIndexScanner::next_entry(RID *rid)
{
  return tree_scanner_.next_entry(*rid);
}

RC BplusTreeIndexScanner::destroy()
{
  delete this;
  return RC::SUCCESS;
}
