/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "sql/operator/aggregate_logical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/update_logical_operator.h"

#include "sql/stmt/stmt.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "storage/field/field.h"
#include "storage/table/table.h"
#include <cassert>
#include <memory>
#include <vector>

using namespace std;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);
      rc                  = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);
      rc                      = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);
      rc                      = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);
      rc                      = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);
      rc                        = create_plan(explain_stmt, logical_operator);
    } break;

    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);
      rc                      = create_plan(update_stmt, logical_operator);
    } break;
    default: {
      rc = RC::UNIMPLENMENT;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> table_oper(nullptr);

  const std::vector<Table *> &tables = select_stmt->tables();
  // const std::vector<Field> &all_fields = select_stmt->query_fields();
  const auto &all_exprs = select_stmt->query_exprs();

  // todo(ligch): 应该结合是否有group by进行判断，放在之后进行优化
  bool has_aggr = false;
  auto iter     = find_if(all_exprs.begin(), all_exprs.end(), [](const shared_ptr<Expression> &expr) {
    return expr->type() == ExprType::AGGREGATE;
  });
  if (iter != all_exprs.end()) {
    has_aggr = true;
  }

  iter = find_if(all_exprs.begin(), all_exprs.end(), [](const shared_ptr<Expression> &expr) {
    return expr->type() != ExprType::AGGREGATE;
  });
  if (has_aggr && (iter != all_exprs.end())) {
    LOG_WARN("select stmt has both aggregate and non-aggregate exprs.");
    return RC::INVALID_ARGUMENT;
  }

  const auto &join_exprs = select_stmt->join_stmts();
  bool        has_join   = select_stmt->join_stmts().size() > 0;
  // select t1.a, t2.b, t3.c from t1, t2 inner join t3 on t2.b = t3.c; 形如此还未实现。
  if (has_join && select_stmt->tables().size() > 1) {
    LOG_WARN("haven't implemented yet.");
    return RC::UNIMPLENMENT;
  }
  //
  if (!has_join) {
    for (Table *table : tables) {
      std::vector<Field> fields;
      for (const auto &expr : all_exprs) {
        // todo(ligch): add exprtype::func
        if (expr->type() == ExprType::FIELD || expr->type() == ExprType::AGGREGATE) {
          const char *table_name = expr->table_name();
          if (0 == strcmp(table_name, table->name())) {
            fields.push_back(expr->get_field());
          }
        }
      }
      unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, true /*readonly*/));
      if (table_oper == nullptr) {
        table_oper = std::move(table_get_oper);
      } else {
        JoinLogicalOperator *join_oper = new JoinLogicalOperator;
        join_oper->add_child(std::move(table_oper));
        join_oper->add_child(std::move(table_get_oper));
        table_oper = unique_ptr<LogicalOperator>(join_oper);
      }
    }
  } else {
    assert(tables.size() == 1);
    Table *cur_table = tables[0];

    auto get_table_fields = [](Table *table) -> std::vector<Field> {
      std::vector<Field> ret;
      for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
        ret.emplace_back(table, table->table_meta().field(i));
      }
      return ret;
    };
    std::vector<Field>          fields = get_table_fields(cur_table);
    unique_ptr<LogicalOperator> table_oper(new TableGetLogicalOperator(cur_table, fields, true /*readonly*/));

    for (const auto &join_stmt : select_stmt->join_stmts()) {
      cur_table = join_stmt->get_table();
      fields    = get_table_fields(cur_table);
      unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(cur_table, fields, true /*readonly*/));
      JoinLogicalOperator        *join_oper = new JoinLogicalOperator(join_stmt);
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
  }

  unique_ptr<LogicalOperator> predicate_oper;
  RC                          rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }
  // todo(ligch): 可以简化逻辑
  unique_ptr<LogicalOperator> logical_oper;
  if (!has_aggr) {
    logical_oper = std::move(make_unique<ProjectLogicalOperator>(all_exprs));
  } else {
    logical_oper = std::move(make_unique<AggregateLogicalOperator>(all_exprs));
  }

  if (predicate_oper) {
    if (table_oper) {
      predicate_oper->add_child(std::move(table_oper));
    }
    logical_oper->add_child(std::move(predicate_oper));
  } else {
    if (table_oper) {
      logical_oper->add_child(std::move(table_oper));
    }
  }

  logical_operator.swap(logical_oper);

  // if (!has_aggr) {
  //   unique_ptr<LogicalOperator> project_oper(new ProjectLogicalOperator(all_exprs));
  //   if (predicate_oper) {
  //     if (table_oper) {
  //       predicate_oper->add_child(std::move(table_oper));
  //     }
  //     project_oper->add_child(std::move(predicate_oper));
  //   } else {
  //     if (table_oper) {
  //       project_oper->add_child(std::move(table_oper));
  //     }
  //   }

  //   logical_operator.swap(project_oper);
  // } else {
  //   unique_ptr<LogicalOperator> aggregate_oper(new AggregateLogicalOperator(all_exprs));
  //   if (predicate_oper) {
  //     if (table_oper) {
  //       predicate_oper->add_child(std::move(table_oper));
  //     }
  //     aggregate_oper->add_child(std::move(predicate_oper));
  //   } else {
  //     if (table_oper) {
  //       aggregate_oper->add_child(std::move(table_oper));
  //     }
  //   }
  //   logical_operator.swap(aggregate_oper);
  // }
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *>    &filter_units = filter_stmt->filter_units();
  for (const FilterUnit *filter_unit : filter_units) {
    const FilterObj &filter_obj_left  = filter_unit->left();
    const FilterObj &filter_obj_right = filter_unit->right();

    unique_ptr<Expression> left(filter_obj_left.is_attr
                                    ? static_cast<Expression *>(new FieldExpr(filter_obj_left.field))
                                    : static_cast<Expression *>(new ValueExpr(filter_obj_left.value)));

    unique_ptr<Expression> right(filter_obj_right.is_attr
                                     ? static_cast<Expression *>(new FieldExpr(filter_obj_right.field))
                                     : static_cast<Expression *>(new ValueExpr(filter_obj_right.value)));

    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
    predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
  }

  logical_operator = std::move(predicate_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table        *table = insert_stmt->table();
  vector<Value> values(insert_stmt->values(), insert_stmt->values() + insert_stmt->value_amount());

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values);
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table             *table       = delete_stmt->table();
  FilterStmt        *filter_stmt = delete_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false /*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC                          rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt *update_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table             *table       = update_stmt->table();
  FilterStmt        *filter_stmt = update_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false /*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC                          rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> update_oper(
      new UpdateLogicalOperator(table, update_stmt->attribute_names(), update_stmt->values()));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(update_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Stmt                       *child_stmt = explain_stmt->child();
  unique_ptr<LogicalOperator> child_oper;
  RC                          rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}
