
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        CALC
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        TEXT_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        OR
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        EQ
        LT
        GT
        LE
        GE
        NE
        MAX
        MIN
        AVG
        SUM
        COUNT
        LIKE
        NOT
        UNIQUE
        NULL_T
        IS_T
        INNER
        JOIN
        ORDER
        BY
        ASC
        HAVING
        GROUP
        IN_T
        EXIST_T
        LENGTH
        DATE_FORMAT
        ROUND
        AS
        VIEW

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
  ParsedSqlNode *                   sql_node;
  ConditionSqlNode *                condition;
  Value *                           value;
  enum CompOp                       comp;
  enum CondOp                       join_op;
  enum AggrType                     aggr_t;
  enum FuncType                     func_t;
  enum OrderType                    order_t;
  RelAttrSqlNode *                  aggr_func;
  RelAttrSqlNode *                  normal_func;
  RelAttrSqlNode *                  expr_attr;
  RelAttrSqlNode *                  rel_attr;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  Expression *                      expression;
  std::vector<Expression *> *       expression_list;
  std::vector<Value> *              value_list;
  std::vector<std::vector<Value>> * insert_list;
  std::vector<ConditionSqlNode> *   condition_list;
  std::vector<RelAttrSqlNode> *     rel_attr_list;
  std::vector<std::pair<std::string, std::string>> *        relation_list;
  std::vector<std::string> *        attribute_list;
  std::vector<UpdateListSqlNode> *  update_list;
  UpdateListSqlNode *               update_pair;
  InnerJoinSqlNode *                inner_join;
  SelectSqlNode *                   select_body;
  std::vector<InnerJoinSqlNode> *   inner_join_list;
  OrderBySqlNode *                  order_by_attr;
  std::vector<OrderBySqlNode> *     order_by_list;
  char *                            string;
  int                               number;
  float                             floats;
  bool                              is_null;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <aggr_t>              aggr_type
%type <aggr_func>           aggr_func
%type <func_t>              func_type
%type <normal_func>         normal_func
%type <expr_attr>           expr_attr
%type <string>              alias_optional;
%type <condition>           condition
%type <value>               value
%type <value>               minus_value
%type <value>               all_value
%type <number>              number
%type <comp>                comp_op
%type <order_t>             order_type
%type <order_by_attr>       order_by_attr
%type <order_by_list>       order_by
%type <order_by_list>       order_by_list
%type <rel_attr>            rel_attr
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <value_list>          cond_value_list
%type <condition_list>      where
%type <condition_list>      condition_list
%type <condition_list>      having
%type <condition>           join_condition
%type <condition_list>      join_condition_list
%type <rel_attr_list>       select_attr
%type <relation_list>       rel_list
%type <rel_attr_list>       attr_list
%type <rel_attr_list>       group_by
%type <expression>          expression
%type <expression_list>     expression_list
%type <attribute_list>      id_list
%type <is_null>             attr_null
%type <update_list>         update_list
%type <update_pair>         update_pair
%type <insert_list>         insert_list
%type <inner_join>          inner_join
%type <inner_join_list>     inner_join_list
%type <select_body>         select_body
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
%type <sql_node>            create_view_stmt
// commands should be a list but I use a single command instead
%type <sql_node>            commands


/* %left EQ LT GT LE NE */
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%left AS DOT
%right ID
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
  | create_view_stmt
    ;

exit_stmt:
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_view_stmt:
    CREATE VIEW ID AS select_body {
      $$ = new ParsedSqlNode(SCF_CREATE_VIEW);
      $$->create_view.view_name = $3;
      $$->create_view.select = $5;
      free($3);
    }
    | CREATE VIEW ID LBRACE ID id_list RBRACE AS select_body {
      $$ = new ParsedSqlNode(SCF_CREATE_VIEW);
      $$->create_view.view_name = $3;
      $$->create_view.select = $9;
      if ($6 != nullptr) {
        $$->create_view.attributes = *$6;
      } else {
        $$->create_view.attributes = std::vector<std::string>();
      }
      $$->create_view.attributes.emplace_back($5);
      std::reverse($$->create_view.attributes.begin(), $$->create_view.attributes.end());
      free($3);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID id_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;

      if ($8 != nullptr) {
        create_index.attributes = *$8;
      } else {
        create_index.attributes = std::vector<std::string>();
      }
      std::string first = $7;
      create_index.attributes.insert(create_index.attributes.begin(), first);
      create_index.unique = false;

      free($3);
      free($5);
      free($7);
      free($8);
    }
    | CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $4;
      create_index.relation_name = $6;

      if ($9 != nullptr) {
        create_index.attributes = *$9;
      } else {
        create_index.attributes = std::vector<std::string>();
      }
      std::string first = $8;
      create_index.attributes.insert(create_index.attributes.begin(), first);
      create_index.unique = true;

      free($4);
      free($6);
      free($8);
      free($9);
    }
    ;

id_list:
  {
    $$ = nullptr;
  }
  | COMMA ID id_list
  {
    if ($3 != nullptr) {
      $$ = $3;
    } else {
      $$ = new std::vector<std::string>;
    }

    $$->emplace_back($2);
    free($2);
  }
  ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
    }
    | CREATE TABLE ID AS select_body
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      create_table.select = $5;
    }
    | CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE select_body
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;

      create_table.select = $8;
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;

attr_def:
    ID type LBRACE number RBRACE attr_null
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->nullable = $6;
      free($1);
    }
    | ID TEXT_T attr_null
    {
      $$ = new AttrInfoSqlNode;
      $$->type = TEXTS;
      $$->name = $1;
      $$->length = 8;
      $$->nullable = $3;
      free($1);
    }
    | ID type attr_null
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->nullable = $3;
      free($1);
    }
    ;

attr_null:
  {
    $$ = true;
  }
  | NOT NULL_T
  {
    $$ = false;
  }
  | NULL_T
  {
    $$ = true;
  }
  ;

number:
    NUMBER {$$ = $1;}
    ;


type:
    INT_T      { $$=INTS; }
    | STRING_T { $$=CHARS; }
    | FLOAT_T  { $$=FLOATS; }
    | DATE_T   { $$=DATES; }
    /* | TEXT_T   { $$=TEXTS; } */
    ;

func_type:
    LENGTH { $$=LENGTH_T; }
    | DATE_FORMAT { $$=DATE_FORMAT_T; }
    | ROUND { $$=ROUND_T; }
    ;

expr_attr:
    expression alias_optional {
      $$ = new RelAttrSqlNode;
      $$->is_expr = true;
      $$->expr = $1;
      $$->alias = $2;
    }

normal_func:
    func_type LBRACE rel_attr RBRACE
    {
      $$ = new RelAttrSqlNode;
      $$->is_aggr = false;

      $$->is_func = true;
      $$->func_type = $1;
      $$->first_func_arg.is_valid = true;
      $$->first_func_arg.is_attr = true;
      $$->first_func_arg.relation_name = $3->relation_name;
      $$->first_func_arg.attribute_name = $3->attribute_name;

      $$->second_func_arg.is_valid = false;

      free($3);
    }
    |
    func_type LBRACE rel_attr COMMA all_value RBRACE
    {
      $$ = new RelAttrSqlNode;
      $$->is_aggr = false;

      $$->is_func = true;
      $$->func_type = $1;
      $$->first_func_arg.is_valid = true;
      $$->first_func_arg.is_attr = true;
      $$->first_func_arg.relation_name = $3->relation_name;
      $$->first_func_arg.attribute_name = $3->attribute_name;

      $$->second_func_arg.is_valid = true;
      $$->second_func_arg.is_attr = false;
      $$->second_func_arg.value = *$5;

      free($3);
      free($5);
    }
    |
    func_type LBRACE all_value RBRACE
    {
      $$ = new RelAttrSqlNode;
      $$->is_aggr = false;

      $$->is_func = true;
      $$->func_type = $1;
      $$->first_func_arg.is_valid = true;
      $$->first_func_arg.is_attr = false;
      $$->first_func_arg.value = *$3;

      $$->second_func_arg.is_valid = false;
      free($3);

    }
    |
    func_type LBRACE all_value COMMA all_value RBRACE
    {
      $$ = new RelAttrSqlNode;
      $$->is_aggr = false;

      $$->is_func = true;
      $$->func_type = $1;
      $$->first_func_arg.is_valid = true;
      $$->first_func_arg.is_attr = false;
      $$->first_func_arg.value = *$3;

      $$->second_func_arg.is_valid = true;
      $$->second_func_arg.is_attr = false;
      $$->second_func_arg.value = *$5;

      free($3);
      free($5);
    }
    ;

aggr_type:
    MAX { $$=MAX_T; }
    | MIN { $$=MIN_T; }
    | AVG { $$=AVG_T; }
    | SUM { $$=SUM_T; }
    | COUNT { $$=COUNT_T; }
    ;

aggr_func:
    aggr_type LBRACE ID RBRACE
    {
      $$ = new RelAttrSqlNode;
      $$->is_aggr = true;
      $$->aggr_type = $1;
      $$->attribute_name = $3;
      free($3);
    }
    | aggr_type LBRACE ID DOT ID RBRACE {
      $$ = new RelAttrSqlNode;
      $$->is_aggr = true;
      $$->aggr_type = $1;
      $$->relation_name  = $3;
      $$->attribute_name = $5;
      free($3);
      free($5);

		}
		| aggr_type LBRACE '*' RBRACE {
      $$ = new RelAttrSqlNode;
      $$->is_aggr = true;
      $$->aggr_type = $1;
      $$->attribute_name = "*";

		}
    ;

insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE all_value value_list RBRACE insert_list
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      std::vector<Value> first_value;
      if ($7 != nullptr) {
        first_value.swap(*$7);
      }
      first_value.emplace_back(*$6);
      std::reverse(first_value.begin(), first_value.end());

      if ($9 != nullptr) {
        $$->insertion.insert_values.swap(*$9);
      }
      $$->insertion.insert_values.emplace_back(std::move(first_value));
      std::reverse($$->insertion.insert_values.begin(), $$->insertion.insert_values.end());

      delete $6;
      free($3);
      delete $9;
      delete $7;
    }
    ;

insert_list:
  {
    $$ = nullptr;
  }
  | COMMA LBRACE all_value value_list RBRACE insert_list
  {
    std::vector<Value> first_value;
    if ($4 != nullptr) {
      first_value.swap(*$4);
    }
    first_value.emplace_back(*$3);
    std::reverse(first_value.begin(), first_value.end());

    if ($6 != nullptr) {
      $$ = $6;
    } else {
      $$ = new std::vector<std::vector<Value>>;
    }
    $$->emplace_back(std::move(first_value));
    delete $6;
  }
  ;

value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA all_value value_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;

all_value:
    minus_value
    {
      $$ = $1;
    }
    |
    value
    {
      $$ = $1;
    }

minus_value:     '-' NUMBER {
      $$ = new Value(0-(int)$2);
      @$ = @2;
    }
    |'-' FLOAT {
      $$ = new Value(0-(float)$2);
      @$ = @2;
    }

value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
    }
    |NULL_T {
      $$ = new Value(); // UNDEFINED TYPE HERE
      $$->set_null();
    }
    ;

delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions.swap(*$4);
        delete $4;
      }
      free($3);
    }
    ;

update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET update_pair update_list where
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;

      if ($5 != nullptr) {
        $$->update.update_list.swap(*$5);
        delete $5;
      }
      $$->update.update_list.emplace_back(*$4);
      delete $4;
      std::reverse($$->update.update_list.begin(), $$->update.update_list.end());

      if ($6 != nullptr) {
        $$->update.conditions.swap(*$6);
        delete $6;
      }
      free($2);
    }

update_pair:
  ID EQ value
  {
    $$ = new UpdateListSqlNode{$1, *$3, SelectSqlNode{}, false};
    free($3);
  }
  | ID EQ LBRACE select_body RBRACE
  {
    $$ = new UpdateListSqlNode{$1, Value{}, *$4, true};
    free($4);
  }

update_list:
    {
      $$ = nullptr;
    }
    | COMMA update_pair update_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<UpdateListSqlNode>;
      }

      $$->emplace_back(*$2);
      free($2);
    }
    ;

select_stmt:        /*  select 语句的语法解析树*/
    //join_list 后有可能出现rel_list吗？
    select_body
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      $$->selection = *$1;
      delete $1;
    }
    ;


select_body:
    SELECT select_attr FROM ID alias_optional rel_list inner_join_list where group_by having order_by
    {
      $$ = new SelectSqlNode;
      if ($2 != nullptr) {
        $$->attributes.swap(*$2);
        delete $2;
      }

      // relation list
      if ($6 != nullptr) {
        $$->relations.swap(*$6);
        delete $6;
      }
      $$->relations.push_back({$4, $5});
      std::reverse($$->relations.begin(), $$->relations.end());

      // inner join
      if ($7 != nullptr) {
        $$->joins.swap(*$7);
        std::reverse($$->joins.begin(), $$->joins.end());
        delete $7;
      }

      // where conditions
      if ($8 != nullptr) {
        $$->conditions.swap(*$8);
        delete $8;
      }

      // group by
      if ($9 != nullptr) {
        $$->group_bys.swap(*$9);
        delete $9;
      }

      // having
      if ($10 != nullptr) {
        $$->havings.swap(*$10);
        delete $10;
      }

      // order by
      if ($11 != nullptr) {
        $$->order_bys.swap(*$11);
        delete $11;
      }
      std::reverse($$->order_bys.begin(), $$->order_bys.end());
      free($4);
    }
    | SELECT expr_attr attr_list
    {
      $$ = new SelectSqlNode;
      if ($3 != nullptr) {
        $$->attributes.swap(*$3);
        delete $3;
      }
      $$->attributes.emplace_back(*$2);
      free($2);
    }
    ;

calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      std::reverse($2->begin(), $2->end());
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression
    {
      $$ = new std::vector<Expression*>;
      $$->emplace_back($1);
    }
    | expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Expression *>;
      }
      $$->emplace_back($1);
    }
    ;

expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
      LOG_DEBUG("ADD");
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
      LOG_DEBUG("SUB");
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
      LOG_DEBUG("MUL");
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
      LOG_DEBUG("DIV");
    }
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
      LOG_DEBUG("()");
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
      LOG_DEBUG("-");
    }
    | rel_attr {
      $$ = new FieldExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | aggr_func {
      $$ = new AggregateExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | normal_func {
      $$ = new FunctionExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
;


select_attr:
    '*' {
      $$ = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      attr.expr = new FieldExpr("*");
      attr.is_expr = true;
      $$->emplace_back(attr);
    }
    | expr_attr attr_list {
      if ($2 != nullptr) {
        $$ = $2;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }
      $$->emplace_back(*$1);
      delete $1;
    }
    ;

alias_optional:
    {
      $$ = strdup("");
    }
    | ID
    {
      $$ = strdup($1);
      free($1);
    }
    | AS ID {
      $$ = strdup($2);
      free($2);
    }
    | AS SUM {
      $$ = strdup("sum");
    }
    ;

rel_attr:
    ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->is_aggr = false;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      $$->alias = "";
      free($1);
      free($3);
    }
    | ID DOT '*' {
      $$ = new RelAttrSqlNode;
      $$->is_aggr = false;
      $$->relation_name  = $1;
      $$->attribute_name = '*';
      free($1);
    }
    | ID {
      $$ = new RelAttrSqlNode;
      $$->is_aggr = false;
      $$->attribute_name = $1;
      $$->alias = "";
      free($1);
    };


attr_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA expr_attr attr_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }

      $$->emplace_back(*$2);
      delete $2;
    }
    ;

rel_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID alias_optional rel_list {
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<std::pair<std::string, std::string>>;
      }

      $$->push_back({$2, $3});
      free($2);
      free($3);
    }
    ;

order_by:
    {
      $$ = nullptr;
    }
    | ORDER BY order_by_list
    {
      $$ = $3;
    }
    ;

order_type:
    {
      $$ = ASC_T;
    }
    |
    ASC
    {
      $$ = ASC_T;
    }
    |
    DESC
    {
      $$ = DESC_T;
    }
    ;

order_by_attr:
    rel_attr order_type
    {
        $$ = new OrderBySqlNode;
        $$->attr = *$1;
        $$->order_type = $2;
        delete $1;
    }
    ;

order_by_list:
    order_by_attr
    {
      $$ = new std::vector<OrderBySqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | order_by_attr COMMA order_by_list {
      $$ = $3;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;

where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;
    }
    ;


having:
    /* empty */
    {
      $$ = nullptr;
    }
    | HAVING condition_list {
      $$ = $2;
    }
    ;

group_by:
    {
      $$ = nullptr;
    }
    | GROUP BY expr_attr attr_list {
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }
      $$->emplace_back(*$3);
      delete $3;
    }
    ;

inner_join_list:
    {
      $$ = nullptr;
    }
    | inner_join inner_join_list {
      if ($2 != nullptr) {
        $$ = $2;
      } else {
        $$ = new std::vector<InnerJoinSqlNode>;
      }
      $$->emplace_back(*$1);
      delete $1;
    }
    ;

inner_join:
    INNER JOIN ID ON join_condition_list {
      $$ = new InnerJoinSqlNode;
      $$->relation_name = $3;
      $$->join_conditions.swap(*$5);
      delete $5;
    };

// 实现了expr之后需要扩展
join_condition:
    condition
    {
      $$ = $1;
    };

// 目前只支持AND且与condition_list相同
join_condition_list:
    {
      $$ = nullptr;
    }
    | join_condition
    {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | join_condition AND join_condition_list {
      $$ = $3;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;

condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition
    {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition OR condition_list {
      $$ = $3;
      $1->is_and = false;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;

cond_value_list:

    value COMMA value {
      $$ = new std::vector<Value>;
      $$->emplace_back(*$1);
      $$->emplace_back(*$3);
      delete $1;
      delete $3;
    }
    | value COMMA cond_value_list  {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$1);
      delete $1;
    }
    ;

condition:
    expr_attr comp_op expr_attr {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_attr = 1;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | expr_attr comp_op LBRACE select_body RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_select = 1;
      $$->right_select = $4;
      $$->comp = $2;
      delete $1;
    }
    | LBRACE select_body RBRACE comp_op expr_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_is_select = 1;
      $$->left_select = $2;
      $$->right_is_attr = 1;
      $$->right_attr = *$5;
      $$->comp = $4;
      delete $5;
    }
    | LBRACE select_body RBRACE comp_op LBRACE select_body RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->left_is_select = 1;
      $$->left_select = $2;
      $$->right_is_select = 1;
      $$->right_select = $6;
      $$->comp = $4;
    }
    | comp_op LBRACE select_body RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->left_is_select = 0;
      $$->right_is_select = 1;
      $$->right_select = $3;
      $$->comp = $1;
      $$->unary_op = 1;
    }
    | expr_attr comp_op LBRACE cond_value_list RBRACE
    {
      // HERE
      $$ = new ConditionSqlNode;
      $$->left_is_attr = 1;
      $$->left_attr = *$1;
      $$->right_is_select = 1;
      $$->comp = $2;
      $$->values.swap(*$4);
      std::reverse($$->values.begin(), $$->values.end());
    }
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE { $$ = STR_LIKE; }
    | NOT LIKE { $$ = STR_NOT_LIKE; }
    | IS_T { $$ = IS; }
    | IS_T NOT { $$ = IS_NOT; }
    | IN_T { $$ = IN; }
    | NOT IN_T { $$ = IN_NOT; }
    | EXIST_T { $$ = EXIST; }
    | NOT EXIST_T { $$ = EXIST_NOT; }
    ;

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);

      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
