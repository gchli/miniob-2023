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
#include "sql/expr/tuple_cell.h"
#include "sql/operator/aggregate_logical_operator.h"
#include "sql/operator/apply_logical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/order_by_logical_operator.h"
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
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
#include <cassert>
#include <cstddef>
#include <cstring>
#include <limits>
#include <memory>
#include <unordered_map>
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
  const std::vector<Table *> &tables = select_stmt->tables();
  // const std::vector<Field> &all_fields = select_stmt->query_fields();
  const auto                         &all_query_exprs = select_stmt->query_exprs();
  std::vector<shared_ptr<Expression>> query_field_exprs;
  std::vector<shared_ptr<Expression>> query_aggr_exprs;
  std::vector<shared_ptr<Expression>> query_func_exprs;
  std::vector<shared_ptr<Expression>> query_arithmetic_exprs;
  std::vector<shared_ptr<Expression>> aggr_exprs_in_arithmetic;
  // todo(ligch): 应该结合是否有group by进行判断，放在之后进行优化

  for (const auto &expr : all_query_exprs) {
    if (expr->type() == ExprType::AGGREGATE) {
      query_aggr_exprs.push_back(expr);
    } else if (expr->type() == ExprType::FIELD) {
      query_field_exprs.push_back(expr);
    } else if (expr->type() == ExprType::FUNCTION) {
      query_func_exprs.push_back(expr);
    } else if (expr->type() == ExprType::ARITHMETIC) {
      query_arithmetic_exprs.push_back(expr);
      const auto &arithmetic_expr = dynamic_pointer_cast<ArithmeticExpr>(expr);
      ArithmeticExpr::collect_aggregates_from_arithmetic_expr(arithmetic_expr.get(), aggr_exprs_in_arithmetic);
    }
  }

  bool has_aggr            = !query_aggr_exprs.empty() || !aggr_exprs_in_arithmetic.empty();
  bool has_field_query     = !query_field_exprs.empty();
  bool has_group_by        = !select_stmt->group_by_exprs().empty();
  bool has_func            = !query_func_exprs.empty();
  bool has_arithmetic_expr = !query_arithmetic_exprs.empty();

  if (has_aggr && has_field_query && !has_group_by) {
    LOG_WARN("select stmt has both aggregate and non-aggregate exprs and no group by exprs.");
    return RC::INVALID_ARGUMENT;
  }

  if (has_aggr && has_field_query && has_group_by) {
    for (const auto &expr : query_field_exprs) {
      auto iter = find_if(select_stmt->group_by_exprs().begin(),
          select_stmt->group_by_exprs().end(),
          [&](shared_ptr<Expression> group_by_expr) {
            if (expr->type() != group_by_expr->type())
              return false;
            if (strcmp(expr->field_name(), group_by_expr->field_name()) != 0)
              return false;
            if (strcmp(expr->table_name(), group_by_expr->table_name()) != 0)
              return false;
            return true;
          });
      if (iter == query_aggr_exprs.end()) {
        LOG_WARN("select stmt has both aggregate and non-aggregate exprs but query field isn't in group by exprs.");
        return RC::INVALID_ARGUMENT;
      }
    }
  }
  unique_ptr<LogicalOperator> table_oper(nullptr);

  const auto &join_exprs = select_stmt->join_stmts();
  bool        has_join   = select_stmt->join_stmts().size() > 0;
  // select t1.a, t2.b, t3.c from t1, t2 inner join t3 on t2.b = t3.c; 形如此还未实现。
  // 是否加一个join tables 的vector？
  // if (has_join && select_stmt->tables().size() > 1) {
  //   LOG_WARN("haven't implemented yet.");
  //   return RC::UNIMPLENMENT;
  // }
  //
  if (!has_join) {
    for (Table *table : tables) {
      std::vector<Field> fields;
      for (const auto &expr : all_query_exprs) {
        // todo(ligch): add exprtype::func
        if (expr->type() == ExprType::FIELD || expr->type() == ExprType::AGGREGATE) {
          const char *table_name = expr->table_name();
          if (0 == strcmp(table_name, table->name())) {
            fields.push_back(expr->get_field());
          }
          continue;
        }
        if (expr->type() == ExprType::FUNCTION) {
          // second arg expression in func_expr should be value, so only need to check the first arg.
          const auto &converted_func_expr = dynamic_pointer_cast<FunctionExpr>(expr);
          if (converted_func_expr->get_first_expr_type() == ExprType::FIELD) {
            const char *table_name = converted_func_expr->get_first_expr()->table_name();
            if (0 == strcmp(table_name, table->name())) {
              fields.push_back(expr->get_field());
            }
          }
          continue;
        }

        if (expr->type() == ExprType::ARITHMETIC) {
          // second arg expression in func_expr should be value, so only need to check the first arg.
          const auto &converted_arithmetic_expr = dynamic_pointer_cast<ArithmeticExpr>(expr);
          RC          rc                        = ArithmeticExpr::collect_fields_from_arithmetic_expr(
              converted_arithmetic_expr.get(), fields, table->name());
          if (rc != RC::SUCCESS) {
            return rc;
          }
          continue;
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
    Table *cur_table = tables[0];

    auto get_table_fields = [](Table *table) -> std::vector<Field> {
      std::vector<Field> ret;
      for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
        ret.emplace_back(table, table->table_meta().field(i));
      }
      return ret;
    };
    std::vector<Field> fields = get_table_fields(cur_table);
    table_oper = unique_ptr<LogicalOperator>(new TableGetLogicalOperator(cur_table, fields, true /*readonly*/));

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
  if (select_stmt->filter_stmt() != nullptr) {  // should we check it?
    RC rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
    if (rc == RC::NEED_APPLY) {
      rc = create_apply_plan(select_stmt->filter_stmt(), std::move(table_oper), predicate_oper);
    } else if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
      return rc;
    }
  }

  bool has_order_by = !select_stmt->order_by_stmts().empty();
  // todo(ligch): 可以简化逻辑

  unique_ptr<LogicalOperator> order_by_oper;
  unique_ptr<LogicalOperator> select_oper;
  if (has_order_by) {
    order_by_oper = std::move(make_unique<OrderByLogicalOperator>(select_stmt->order_by_stmts()));
  }

  if (!has_aggr && !has_group_by) {
    auto proj_oper = std::move(make_unique<ProjectLogicalOperator>(all_query_exprs, select_stmt->field_alias()));
    select_oper    = std::move(proj_oper);
  } else {
    auto aggr_oper = std::move(make_unique<AggregateLogicalOperator>(all_query_exprs, select_stmt->field_alias()));
    if (has_group_by) {
      aggr_oper->set_group_bys(select_stmt->group_by_exprs());
    }
    if (select_stmt->having_stmt() != nullptr) {
      aggr_oper->set_having(select_stmt->having_stmt());
      aggr_oper->set_having_exprs(select_stmt->having_exprs());
    }
    select_oper = std::move(aggr_oper);
  }

  if (predicate_oper) {
    if (table_oper) {  // 这他妈是废话啊，table_oper不可能为空啊
      predicate_oper->add_child(std::move(table_oper));
    }
    select_oper->add_child(std::move(predicate_oper));
  } else {
    if (table_oper) {
      select_oper->add_child(std::move(table_oper));
    }
  }

  unique_ptr<LogicalOperator> logical_oper;

  logical_oper = std::move(select_oper);
  if (order_by_oper) {
    order_by_oper->add_child(std::move(logical_oper));
    logical_oper = std::move(order_by_oper);
  }

  logical_operator.swap(logical_oper);
  return RC::SUCCESS;
}

unique_ptr<Expression> create_expr_from_filter_obj(const FilterObj &filter_obj)
{
  Expression *expr;
  switch (filter_obj.type) {
    case FilterObj::FilterObjType::FILTER_OBJ_ATTR: {
      expr = new FieldExpr(filter_obj.field);
    } break;
    case FilterObj::FilterObjType::FILTER_OBJ_VALUE: {
      expr = new ValueExpr(filter_obj.value);
    } break;
    case FilterObj::FilterObjType::FILTER_OBJ_VALUES: {
      expr = new ValuesExpr(filter_obj.values_);
    } break;
    case FilterObj::FilterObjType::FILTER_OBJ_SELECT: {
      expr = new SelectExpr(filter_obj.select_stmt_);
    } break;
    case FilterObj::FilterObjType::FILTER_OBJ_EXPR: {
      if (filter_obj.expression->type() == ExprType::FUNCTION) {
        const auto &func_expr = dynamic_pointer_cast<FunctionExpr>(filter_obj.expression);
        expr                  = new FunctionExpr(func_expr->function_type(),
            func_expr->get_first_expr(),
            func_expr->get_second_expr(),
            func_expr->get_alias());
        break;
      }
      if (filter_obj.expression->type() == ExprType::AGGREGATE) {
        const auto &aggr_expr = dynamic_pointer_cast<AggregateExpr>(filter_obj.expression);
        expr                  = new AggregateExpr(aggr_expr->aggregate_type(), aggr_expr->get_field());
        break;
      }
      if (filter_obj.expression->type() == ExprType::ARITHMETIC) {
        const auto &arithmetic_expr = dynamic_pointer_cast<ArithmeticExpr>(filter_obj.expression);
        expr                        = new ArithmeticExpr(arithmetic_expr->arithmetic_type(),
            std::move(arithmetic_expr->left()),
            std::move(arithmetic_expr->right()));
        break;
      }

    } break;
    case FilterObj::FilterObjType::FILTER_OBJ_FATHRE_ATTR: {  // 子查询，需要父亲的属性
      (void)expr;
      auto ctx  = FilterCtx::get_instance();
      auto iter = ctx.tuple_maps_.find(filter_obj.field.table()->name());
      if (iter == ctx.tuple_maps_.end()) {
        LOG_WARN("failed to find table in tuple_maps. table=%s", filter_obj.field.table()->name());
        return nullptr;
      }
      auto  tuple = iter->second;
      Value value;
      RC rc = tuple->find_cell(TupleCellSpec(filter_obj.field.table()->name(), filter_obj.field.field_name()), value);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to find cell in tuple. table=%s, field=%s", filter_obj.field.table()->name(), filter_obj.field.field_name());
        return nullptr;
      }
      expr = new ValueExpr(value);
      //   expr = new FatherFieldExpr(filter_obj.field);
    } break;
    default: LOG_WARN("unhandeld filter obj type. type=%d", filter_obj.type);
  }

  return unique_ptr<Expression>(expr);
}

RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *>    &filter_units = filter_stmt->filter_units();
  bool                                is_and       = true;
  for (const FilterUnit *filter_unit : filter_units) {
    const FilterObj       &filter_obj_left  = filter_unit->left();
    const FilterObj       &filter_obj_right = filter_unit->right();
    unique_ptr<Expression> left;
    unique_ptr<Expression> right;
    if (filter_obj_left.is_select() || filter_obj_right.is_select()) {
      // 如果有个filterobj是select，那么这个filterstmt就需要apply
      return RC::NEED_APPLY;
    }

    left  = create_expr_from_filter_obj(filter_obj_left);
    right = create_expr_from_filter_obj(filter_obj_right);

    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);

    is_and = is_and && filter_unit->is_and();
  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr;
    if (is_and) {
      conjunction_expr.reset(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
    } else {
      conjunction_expr.reset(new ConjunctionExpr(ConjunctionExpr::Type::OR, cmp_exprs));
    }
    predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
  }

  logical_operator = std::move(predicate_oper);
  return RC::SUCCESS;
}

// 把Filter里边的Unit分开，不需要子查询的放到左边，需要子查询的放到右边
RC LogicalPlanGenerator::create_apply_plan(FilterStmt *filter_stmt, std::unique_ptr<LogicalOperator> &&table_oper,
    std::unique_ptr<LogicalOperator> &predicate_oper)
{
  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *>    &filter_units = filter_stmt->filter_units();
  std::vector<const FilterUnit *>     subselect_filter_units;
  bool                                is_and = true;
  for (const FilterUnit *filter_unit : filter_units) {
    const FilterObj &filter_obj_left  = filter_unit->left();
    const FilterObj &filter_obj_right = filter_unit->right();
    if (filter_obj_left.is_select() || filter_obj_right.is_select()) {
      subselect_filter_units.emplace_back(filter_unit);
      continue;
    }
    unique_ptr<Expression> left;
    unique_ptr<Expression> right;

    left  = create_expr_from_filter_obj(filter_obj_left);
    right = create_expr_from_filter_obj(filter_obj_right);

    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);

    is_and = is_and && filter_unit->is_and();
  }

  unique_ptr<LogicalOperator> left;
  if (!cmp_exprs.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
    left = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
    left->add_child(std::move(table_oper));
  } else {
    left = std::move(table_oper);
  }

  for (const auto *filter_unit : subselect_filter_units) {
    const FilterObj       &filter_obj_left  = filter_unit->left();
    const FilterObj       &filter_obj_right = filter_unit->right();
    unique_ptr<Expression> left;
    unique_ptr<Expression> right;

    left  = create_expr_from_filter_obj(filter_obj_left);
    right = create_expr_from_filter_obj(filter_obj_right);

    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }
  if (!cmp_exprs.empty()) {
    predicate_oper = make_unique<ApplyLogicalOperator>(std::move(cmp_exprs),
        is_and);  // 应该是所有的cmp expr做and，这里貌似只有and，就省去了，传进去的expression都是ComparisonExpr
  }

  predicate_oper->add_child(std::move(left));  // 左儿子是predicate

  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table                          *table = insert_stmt->table();
  std::vector<std::vector<Value>> insert_values(
      insert_stmt->insert_values(), insert_stmt->insert_values() + insert_stmt->insert_amount());

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, insert_values);
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

  int                                col_update = update_stmt->field_metas().size();
  std::unordered_map<size_t, size_t> select_oper_map;
  int                                oper_cnt = 1;

  for (int i = 0; i < col_update; i++) {
    if (update_stmt->select_map().find(i) != update_stmt->select_map().end()) {
      select_oper_map.emplace(i, oper_cnt++);
    }
  }

  unique_ptr<LogicalOperator> update_oper(new UpdateLogicalOperator(
      table, std::move(update_stmt->field_metas()), std::move(update_stmt->value_map()), std::move(select_oper_map)));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }

  for (int i = 0; i < col_update; i++) {
    if (update_stmt->select_map().find(i) != update_stmt->select_map().end()) {
      unique_ptr<LogicalOperator> select_oper;
      rc = create_plan(&update_stmt->select_map()[i], select_oper);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      update_oper->add_child(std::move(select_oper));
    }
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
