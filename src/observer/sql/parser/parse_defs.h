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
// Created by Meiyi
//

#pragma once

#include <stddef.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>

#include "sql/parser/value.h"

class Expression;

/**
 * @defgroup SQLParser SQL Parser
 */

enum AggrType
{
  INVALID_T,
  MAX_T,
  MIN_T,
  AVG_T,
  SUM_T,
  COUNT_T,
  ARITHMETIC_T,
  FUNC_T,
  FIELD_T,
};

enum FuncType
{
  UNDEFINED_T,
  LENGTH_T,
  ROUND_T,
  DATE_FORMAT_T,
};

enum OrderType
{
  ASC_T,
  DESC_T
};

struct FuncArgSqlNode
{
  bool        is_valid{false};
  bool        is_attr{false};
  std::string relation_name;   ///< relation name (may be NULL) 表名
  std::string attribute_name;  ///< attribute name              属性名
  Value       value;
};

/**
 * @brief 描述一个属性
 * @ingroup SQLParser
 * @details 属性，或者说字段(column, field)
 * Rel -> Relation
 * Attr -> Attribute
 */
struct RelAttrSqlNode
{
  std::string relation_name;   ///< relation name (may be NULL) 表名
  std::string attribute_name;  ///< attribute name              属性名

  bool     is_aggr{false};
  AggrType aggr_type;

  bool           is_func{false};
  FuncType       func_type;
  FuncArgSqlNode first_func_arg;
  FuncArgSqlNode second_func_arg;

  bool        is_expr{false};
  Expression *expr{nullptr};
  std::string alias{""};
};

/**
 * @brief 描述比较运算符
 * @ingroup SQLParser
 */
enum CompOp
{
  EQUAL_TO,      ///< "="
  LESS_EQUAL,    ///< "<="
  NOT_EQUAL,     ///< "<>"
  LESS_THAN,     ///< "<"
  GREAT_EQUAL,   ///< ">="
  GREAT_THAN,    ///< ">"
  STR_LIKE,      ///< "LIKE"
  STR_NOT_LIKE,  ///< "NOT LIKE",
  IS,            ///< "IS"
  IS_NOT,        ///< "IS NOT"
  IN,            ///< "IN"
  IN_NOT,        ///< "NOT IN",
  EXIST,         ///< "EXIST",
  EXIST_NOT,     ///< "NOT EXIST"
  NO_OP
};

inline bool is_values_op(CompOp op) { return op == IN || op == IN_NOT || op == EXIST || op == EXIST_NOT; }

enum CondOp
{
  AND_T,
  OR_T,
};
/**
 * @brief 表示一个条件比较
 * @ingroup SQLParser
 * @details 条件比较就是SQL查询中的 where a>b 这种。
 * 一个条件比较是有两部分组成的，称为左边和右边。
 * 左边和右边理论上都可以是任意的数据，比如是字段（属性，列），也可以是数值常量。
 * 这个结构中记录的仅仅支持字段和值。
 */

struct SelectSqlNode;

struct ConditionSqlNode
{
  bool is_and   = true;
  int  unary_op = 0;

  int            left_is_attr;
  RelAttrSqlNode left_attr;
  Value          left_value;

  int            left_is_select = 0;
  SelectSqlNode *left_select;

  CompOp comp;  ///< comparison operator

  int            right_is_attr;
  RelAttrSqlNode right_attr;
  Value          right_value;

  int            right_is_select = 0;
  SelectSqlNode *right_select;

  std::vector<Value> values;
};

/**
 * @brief 描述一个select语句
 * @ingroup SQLParser
 * @details 一个正常的select语句描述起来比这个要复杂很多，这里做了简化。
 * 一个select语句由三部分组成，分别是select, from, where。
 * select部分表示要查询的字段，from部分表示要查询的表，where部分表示查询的条件。
 * 比如 from 中可以是多个表，也可以是另一个查询语句，这里仅仅支持表，也就是 relations。
 * where 条件 conditions，这里表示使用AND串联起来多个条件。正常的SQL语句会有OR，NOT等，
 * 甚至可以包含复杂的表达式。
 */
struct InnerJoinSqlNode
{
  std::string                   relation_name;
  std::vector<ConditionSqlNode> join_conditions;
};

struct OrderBySqlNode
{
  RelAttrSqlNode attr;
  OrderType      order_type;
};

struct SelectSqlNode
{
  std::vector<RelAttrSqlNode> attributes;  ///< attributes in select clause
  // std::vector<std::string>                     relations;   ///< 查询的表
  std::vector<std::pair<std::string, std::string>> relations;  ///< 查询的表 (relation name, alias)
  // std::unordered_map<std::string, std::string> relations_alias;
  std::vector<ConditionSqlNode> conditions;  ///< 查询条件，使用AND串联起来多个条件
  std::vector<InnerJoinSqlNode> joins;
  std::vector<OrderBySqlNode>   order_bys;
  std::vector<RelAttrSqlNode>   group_bys;
  std::vector<ConditionSqlNode> havings;
};

/**
 * @brief 算术表达式计算的语法树
 * @ingroup SQLParser
 */
struct CalcSqlNode
{
  std::vector<Expression *> expressions;  ///< calc clause

  ~CalcSqlNode();
};

/**
 * @brief 描述一个insert语句
 * @ingroup SQLParser
 * @details 于Selects类似，也做了很多简化
 */
struct InsertSqlNode
{
  std::string                     relation_name;  ///< Relation to insert into
  std::vector<std::vector<Value>> insert_values;  ///< 要插入的值
};

/**
 * @brief 描述一个delete语句
 * @ingroup SQLParser
 */
struct DeleteSqlNode
{
  std::string                   relation_name;  ///< Relation to delete from
  std::vector<ConditionSqlNode> conditions;
};

/**
 * update set a=xx, b=xx
 * 记录 a xx, b xx
 */
struct UpdateListSqlNode
{
  std::string   attribute_name;
  Value         value;
  SelectSqlNode select;
  bool          is_select = false;
};

/**
 * @brief 描述一个update语句
 * @ingroup SQLParser
 */
struct UpdateSqlNode
{
  std::string relation_name;  ///< Relation to update
  // std::string                   attribute_name;  ///< 更新的字段，仅支持一个字段
  // Value                         value;           ///< 更新的值，仅支持一个字段
  std::vector<UpdateListSqlNode> update_list;
  std::vector<ConditionSqlNode>  conditions;
};

/**
 * @brief 描述一个属性
 * @ingroup SQLParser
 * @details 属性，或者说字段(column, field)
 * Rel -> Relation
 * Attr -> Attribute
 */
struct AttrInfoSqlNode
{
  AttrType    type;      ///< Type of attribute
  std::string name;      ///< Attribute name
  size_t      length;    ///< Length of attribute
  bool        nullable;  //< is nullable of attribute
};

/**
 * @brief 描述一个create table语句
 * @ingroup SQLParser
 * @details 这里也做了很多简化。
 */
struct CreateTableSqlNode
{
  std::string                  relation_name;  ///< Relation name
  std::vector<AttrInfoSqlNode> attr_infos;     ///< attributes
  SelectSqlNode               *select{nullptr};
};

/**
 * @brief 描述一个create view语句
 * @ingroup SQLParser
 */
struct CreateViewSqlNode
{
  std::string    view_name;
  SelectSqlNode *select;
  std::vector<std::string> attributes;
};

/**
 * @brief 描述一个drop table语句
 * @ingroup SQLParser
 */
struct DropTableSqlNode
{
  std::string relation_name;  ///< 要删除的表名
};

/**
 * @brief 描述一个create index语句
 * @ingroup SQLParser
 * @details 创建索引时，需要指定索引名，表名，字段名。
 * 正常的SQL语句中，一个索引可能包含了多个字段，这里仅支持一个字段。
 */
struct CreateIndexSqlNode
{
  std::string index_name;     ///< Index name
  std::string relation_name;  ///< Relation name
  // std::string attribute_name;  ///< Attribute name
  std::vector<std::string> attributes;  ///< Attribute names
  bool                     unique;
};

/**
 * @brief 描述一个drop index语句
 * @ingroup SQLParser
 */
struct DropIndexSqlNode
{
  std::string index_name;     ///< Index name
  std::string relation_name;  ///< Relation name
};

/**
 * @brief 描述一个desc table语句
 * @ingroup SQLParser
 * @details desc table 是查询表结构信息的语句
 */
struct DescTableSqlNode
{
  std::string relation_name;
};

/**
 * @brief 描述一个load data语句
 * @ingroup SQLParser
 * @details 从文件导入数据到表中。文件中的每一行就是一条数据，每行的数据类型、字段个数都与表保持一致
 */
struct LoadDataSqlNode
{
  std::string relation_name;
  std::string file_name;
};

/**
 * @brief 设置变量的值
 * @ingroup SQLParser
 * @note 当前还没有查询变量
 */
struct SetVariableSqlNode
{
  std::string name;
  Value       value;
};

class ParsedSqlNode;

/**
 * @brief 描述一个explain语句
 * @ingroup SQLParser
 * @details 会创建operator的语句，才能用explain输出执行计划。
 * 一个command就是一个语句，比如select语句，insert语句等。
 * 可能改成SqlCommand更合适。
 */
struct ExplainSqlNode
{
  std::unique_ptr<ParsedSqlNode> sql_node;
};

/**
 * @brief 解析SQL语句出现了错误
 * @ingroup SQLParser
 * @details 当前解析时并没有处理错误的行号和列号
 */
struct ErrorSqlNode
{
  std::string error_msg;
  int         line;
  int         column;
};

/**
 * @brief 表示一个SQL语句的类型
 * @ingroup SQLParser
 */
enum SqlCommandFlag
{
  SCF_ERROR = 0,
  SCF_CALC,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_DROP_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_BEGIN,  ///< 事务开始语句，可以在这里扩展只读事务
  SCF_COMMIT,
  SCF_CLOG_SYNC,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT,
  SCF_EXPLAIN,
  SCF_SET_VARIABLE,  ///< 设置变量
  SCF_CREATE_VIEW
};
/**
 * @brief 表示一个SQL语句
 * @ingroup SQLParser
 */
class ParsedSqlNode
{
public:
  enum SqlCommandFlag flag;
  ErrorSqlNode        error;
  CalcSqlNode         calc;
  SelectSqlNode       selection;
  InsertSqlNode       insertion;
  DeleteSqlNode       deletion;
  UpdateSqlNode       update;
  CreateTableSqlNode  create_table;
  DropTableSqlNode    drop_table;
  CreateIndexSqlNode  create_index;
  DropIndexSqlNode    drop_index;
  DescTableSqlNode    desc_table;
  LoadDataSqlNode     load_data;
  ExplainSqlNode      explain;
  SetVariableSqlNode  set_variable;
  CreateViewSqlNode   create_view;

public:
  ParsedSqlNode();
  explicit ParsedSqlNode(SqlCommandFlag flag);
};

/**
 * @brief 表示语法解析后的数据
 * @ingroup SQLParser
 */
class ParsedSqlResult
{
public:
  void                                         add_sql_node(std::unique_ptr<ParsedSqlNode> sql_node);
  std::vector<std::unique_ptr<ParsedSqlNode>> &sql_nodes() { return sql_nodes_; }

private:
  std::vector<std::unique_ptr<ParsedSqlNode>> sql_nodes_;  ///< 这里记录SQL命令。虽然看起来支持多个，但是当前仅处理一个
};
