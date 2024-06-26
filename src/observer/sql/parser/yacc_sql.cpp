/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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


#line 114 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    CREATE = 259,
    DROP = 260,
    TABLE = 261,
    TABLES = 262,
    INDEX = 263,
    CALC = 264,
    SELECT = 265,
    DESC = 266,
    SHOW = 267,
    SYNC = 268,
    INSERT = 269,
    DELETE = 270,
    UPDATE = 271,
    LBRACE = 272,
    RBRACE = 273,
    COMMA = 274,
    TRX_BEGIN = 275,
    TRX_COMMIT = 276,
    TRX_ROLLBACK = 277,
    INT_T = 278,
    STRING_T = 279,
    FLOAT_T = 280,
    DATE_T = 281,
    TEXT_T = 282,
    HELP = 283,
    EXIT = 284,
    DOT = 285,
    INTO = 286,
    VALUES = 287,
    FROM = 288,
    WHERE = 289,
    AND = 290,
    OR = 291,
    SET = 292,
    ON = 293,
    LOAD = 294,
    DATA = 295,
    INFILE = 296,
    EXPLAIN = 297,
    EQ = 298,
    LT = 299,
    GT = 300,
    LE = 301,
    GE = 302,
    NE = 303,
    MAX = 304,
    MIN = 305,
    AVG = 306,
    SUM = 307,
    COUNT = 308,
    LIKE = 309,
    NOT = 310,
    UNIQUE = 311,
    NULL_T = 312,
    IS_T = 313,
    INNER = 314,
    JOIN = 315,
    ORDER = 316,
    BY = 317,
    ASC = 318,
    HAVING = 319,
    GROUP = 320,
    IN_T = 321,
    EXIST_T = 322,
    LENGTH = 323,
    DATE_FORMAT = 324,
    ROUND = 325,
    AS = 326,
    VIEW = 327,
    NUMBER = 328,
    FLOAT = 329,
    ID = 330,
    SSS = 331,
    UMINUS = 332
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 129 "yacc_sql.y"

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

#line 280 "yacc_sql.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);

#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  85
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   390

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  174
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  323

#define YYUNDEFTOK  2
#define YYMAXUTOK   332


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    79,    77,     2,    78,     2,    80,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    81
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   248,   248,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   280,   286,   291,   297,   303,   309,
     315,   322,   328,   336,   342,   358,   379,   403,   406,   420,
     430,   446,   455,   476,   479,   492,   501,   510,   522,   525,
     529,   536,   541,   542,   543,   544,   549,   550,   551,   555,
     563,   580,   600,   616,   637,   638,   639,   640,   641,   645,
     653,   663,   669,   678,   703,   706,   727,   730,   742,   747,
     752,   756,   762,   766,   770,   775,   782,   795,   816,   821,
     828,   831,   846,   856,   905,   918,   928,   933,   945,   949,
     953,   957,   961,   966,   970,   975,   980,   985,   994,  1003,
    1012,  1024,  1027,  1032,  1036,  1039,  1045,  1054,  1061,  1072,
    1075,  1089,  1092,  1106,  1109,  1116,  1120,  1125,  1132,  1142,
    1148,  1157,  1160,  1168,  1171,  1177,  1180,  1192,  1195,  1207,
    1216,  1223,  1226,  1232,  1241,  1244,  1250,  1255,  1265,  1272,
    1284,  1295,  1305,  1315,  1324,  1333,  1347,  1348,  1349,  1350,
    1351,  1352,  1353,  1354,  1355,  1356,  1357,  1358,  1359,  1360,
    1364,  1377,  1385,  1395,  1396
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "TABLE",
  "TABLES", "INDEX", "CALC", "SELECT", "DESC", "SHOW", "SYNC", "INSERT",
  "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "TEXT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE",
  "AND", "OR", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN", "EQ",
  "LT", "GT", "LE", "GE", "NE", "MAX", "MIN", "AVG", "SUM", "COUNT",
  "LIKE", "NOT", "UNIQUE", "NULL_T", "IS_T", "INNER", "JOIN", "ORDER",
  "BY", "ASC", "HAVING", "GROUP", "IN_T", "EXIST_T", "LENGTH",
  "DATE_FORMAT", "ROUND", "AS", "VIEW", "NUMBER", "FLOAT", "ID", "SSS",
  "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_view_stmt", "create_index_stmt", "id_list",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "attr_null", "number", "type", "func_type", "expr_attr", "normal_func",
  "aggr_type", "aggr_func", "insert_stmt", "insert_list", "value_list",
  "all_value", "minus_value", "value", "delete_stmt", "update_stmt",
  "update_pair", "update_list", "select_stmt", "select_body", "calc_stmt",
  "expression_list", "expression", "select_attr", "alias_optional",
  "rel_attr", "attr_list", "rel_list", "order_by", "order_type",
  "order_by_attr", "order_by_list", "where", "having", "group_by",
  "inner_join_list", "inner_join", "join_condition", "join_condition_list",
  "condition_list", "cond_value_list", "condition", "comp_op",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,    43,    45,    42,
      47,   332
};
# endif

#define YYPACT_NINF (-267)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-111)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     340,    11,    40,   221,   107,   -44,    30,  -267,    27,    31,
      -5,  -267,  -267,  -267,  -267,  -267,    39,    66,   340,   123,
     124,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,    60,    73,   132,    86,    88,    90,   221,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,   142,  -267,   221,   167,  -267,   170,  -267,  -267,  -267,
      38,  -267,  -267,  -267,   169,    91,   156,  -267,  -267,   115,
     126,   161,   159,   164,  -267,  -267,  -267,  -267,     9,   168,
     133,    13,  -267,   171,    16,   -46,  -267,   -35,   -16,   221,
     221,   221,   221,   221,   221,   178,   -25,  -267,  -267,   137,
     181,   183,   144,    63,   145,   147,   208,   148,   203,   172,
     208,   179,  -267,  -267,  -267,    24,   103,  -267,  -267,   114,
     202,     5,   224,  -267,    65,    65,  -267,  -267,   169,  -267,
    -267,  -267,    15,   226,   182,  -267,   201,   234,  -267,   214,
     128,   240,  -267,   244,   187,   245,  -267,  -267,  -267,  -267,
    -267,   -29,  -267,   -29,  -267,  -267,   190,  -267,  -267,   247,
     -29,     3,  -267,  -267,  -267,  -267,  -267,  -267,  -267,    76,
     212,  -267,  -267,   149,  -267,   143,   252,    52,   144,   183,
     269,  -267,  -267,  -267,  -267,    56,    74,   147,   258,   204,
     260,   205,   263,   266,   267,   274,   218,   228,   264,   280,
    -267,  -267,  -267,  -267,   251,   182,   182,   208,   208,  -267,
     234,  -267,   230,   249,  -267,  -267,   236,  -267,   240,   208,
     245,   232,   245,   239,  -267,  -267,  -267,    15,   253,   183,
     228,   -29,   293,   149,     3,  -267,  -267,  -267,   294,   305,
    -267,  -267,  -267,  -267,   310,  -267,  -267,   312,   245,  -267,
     208,   247,   256,   271,  -267,   264,   313,   265,   318,   324,
     328,  -267,  -267,    56,  -267,   329,  -267,  -267,   319,   286,
     295,  -267,   341,  -267,     3,  -267,    63,  -267,  -267,  -267,
    -267,   182,   221,   182,   302,   -29,   346,   318,  -267,   330,
    -267,  -267,   169,  -267,   304,  -267,   264,  -267,   182,  -267,
     292,   352,  -267,    25,   353,  -267,   313,  -267,  -267,  -267,
     292,  -267,  -267
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     173,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      23,    12,    13,     8,     5,     7,     6,     4,    92,     3,
      18,    19,    20,     0,     0,     0,     0,     0,     0,     0,
      64,    65,    66,    67,    68,    85,    56,    57,    58,    82,
      83,   118,    84,     0,     0,   107,     0,   106,   105,    95,
      96,   104,   109,   108,   119,   111,     0,    32,    31,     0,
       0,     0,     0,     0,   171,     1,   174,     2,     0,     0,
       0,     0,    30,     0,     0,     0,   103,     0,     0,     0,
       0,     0,     0,     0,     0,    94,     0,   112,    59,     0,
       0,   131,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   102,   116,   117,     0,     0,    78,    79,     0,
       0,     0,     0,    97,    98,    99,   100,   101,   119,   115,
     114,   113,   111,     0,   144,    86,     0,    90,   172,     0,
       0,    43,    41,     0,     0,    37,    33,    39,    80,    81,
      62,     0,    60,     0,    72,    69,     0,    71,   120,   121,
       0,     0,   156,   157,   158,   159,   160,   161,   162,     0,
     164,   166,   168,     0,   132,   145,     0,     0,     0,   131,
       0,    52,    53,    54,    55,    48,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   137,    76,     0,
     163,   167,   169,   165,     0,   144,   144,     0,     0,    88,
      90,    87,     0,     0,    50,    46,     0,    47,    43,    40,
      37,     0,    37,     0,    63,    61,    70,   111,     0,   131,
     137,     0,     0,     0,     0,   150,   146,   147,     0,     0,
      91,   170,    49,    51,     0,    44,    42,     0,    37,    38,
       0,   121,     0,   135,   138,    76,    74,     0,   105,     0,
       0,   154,    89,    48,    35,     0,    34,   122,     0,     0,
     133,    77,     0,    73,     0,   152,     0,   151,   155,    45,
      36,   141,     0,   144,   123,     0,     0,   148,   149,   142,
     139,   140,   119,   134,     0,    93,    76,   153,   141,   136,
       0,     0,   143,   125,   129,   124,    74,   127,   126,   128,
       0,    75,   130
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -267,  -267,   355,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -120,  -267,  -267,   146,   174,  -188,
    -267,  -267,  -267,    -4,  -267,  -267,  -267,  -267,    59,  -244,
    -154,  -267,   -95,  -267,  -267,   188,   158,  -267,  -110,  -267,
     281,     2,  -267,  -138,   -96,  -135,   120,  -267,  -267,  -267,
      64,  -157,  -267,  -267,   150,  -267,  -267,    75,  -204,    99,
    -266,  -169,  -267,  -267,  -267,  -267
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,   202,    32,    33,   198,   151,   225,
     254,   196,    64,   183,    65,    66,    67,    34,   283,   242,
     126,   127,    68,    35,    36,   147,   189,    37,    38,    39,
      69,    75,    76,   108,    71,   105,   207,   305,   319,   314,
     315,   145,   294,   280,   239,   240,   299,   300,   184,   270,
     185,   186,    40,    41,    42,    87
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      74,   129,   128,   168,   169,    70,   152,   203,   227,   204,
     156,   246,   247,     4,   214,   139,   208,    43,   148,    44,
      49,   281,    55,   165,   130,   301,   115,   140,    55,   123,
     119,    77,   221,   124,   122,   166,   317,    78,    59,    60,
      61,    62,   301,   125,    59,    60,    47,    62,    48,   125,
     141,    94,    50,    51,    52,    53,    54,    99,    79,   131,
      55,   209,   311,   132,    80,    96,   128,    45,   128,   218,
      81,    56,    57,    58,   267,   128,    59,    60,    61,    62,
     116,    63,   263,    46,   120,   289,   106,   265,   318,   303,
     107,   226,   219,   100,   101,   102,   103,   158,   159,   261,
     138,    70,   134,   135,   136,   137,    83,   248,   249,    55,
     257,   223,   259,   224,    82,   100,   101,   102,   103,   256,
      55,   160,   161,    85,    49,    59,    60,    86,    62,   223,
     210,   224,   162,   163,   269,    88,    59,    60,   275,    62,
      90,   306,   211,   212,   102,   103,   128,    72,    89,   268,
     276,   191,   192,   193,   194,   195,    50,    51,    52,    53,
      54,    91,   106,    92,    55,    93,   107,   309,   100,   101,
     102,   103,    95,    94,   296,    56,    57,    58,   215,   216,
      59,    60,    61,    62,    97,    63,    73,    98,   104,   109,
     110,   297,   172,   173,   174,   175,   176,   177,   112,   171,
     128,   111,   113,   178,   179,   114,   117,   180,   118,   121,
     245,  -110,   142,   143,   313,   181,   182,   144,     4,   146,
     164,   149,   150,   153,   313,   172,   173,   174,   175,   176,
     177,    50,    51,    52,    53,    54,   178,   179,    49,    55,
     180,   154,   167,   170,   187,   190,    94,   155,   181,   182,
      56,    57,    58,   188,   157,    59,    60,    61,    62,   197,
      63,   199,   200,   285,   201,   205,   206,   213,   244,   217,
      50,    51,    52,    53,    54,   222,   229,   231,    55,   230,
     232,   233,   284,   241,   234,   235,    94,   238,   302,    56,
      57,    58,   236,   237,    59,    60,    61,    62,   243,    63,
      50,    51,    52,    53,    54,   251,   252,   258,    55,   253,
     260,   266,   271,   262,    50,    51,    52,    53,    54,    56,
      57,    58,    55,   272,    59,    60,    61,    62,   273,    63,
     274,   278,   282,    56,    57,    58,   279,   286,    59,    60,
      61,    62,   287,    63,     1,     2,   288,   290,   292,     3,
       4,     5,     6,     7,     8,     9,    10,   291,   295,   293,
      11,    12,    13,   304,   307,   308,   310,    61,    14,    15,
     316,   228,   320,    84,   255,   321,   220,    16,   250,    17,
     133,   277,    18,   312,   322,   298,     0,     0,     0,     0,
     264
};

static const yytype_int16 yycheck[] =
{
       4,    97,    97,   138,   142,     3,   116,   161,   196,   163,
     120,   215,   216,    10,   183,    40,   170,     6,   113,     8,
      17,   265,    57,    18,    40,   291,    17,    52,    57,    75,
      17,    75,   189,    79,    18,    30,    11,     7,    73,    74,
      75,    76,   308,    78,    73,    74,     6,    76,     8,    78,
      75,    49,    49,    50,    51,    52,    53,    19,    31,    75,
      57,   171,   306,    79,    33,    63,   161,    56,   163,    17,
      75,    68,    69,    70,   243,   170,    73,    74,    75,    76,
      71,    78,   239,    72,    71,   273,    71,   241,    63,   293,
      75,    17,   187,    77,    78,    79,    80,    73,    74,   237,
     104,    99,   100,   101,   102,   103,    40,   217,   218,    57,
     230,    55,   232,    57,    75,    77,    78,    79,    80,   229,
      57,    18,    19,     0,    17,    73,    74,     3,    76,    55,
      54,    57,    18,    19,   244,    75,    73,    74,   258,    76,
       8,   295,    66,    67,    79,    80,   241,    40,    75,   244,
     260,    23,    24,    25,    26,    27,    49,    50,    51,    52,
      53,    75,    71,    75,    57,    75,    75,   302,    77,    78,
      79,    80,    30,   171,   284,    68,    69,    70,    35,    36,
      73,    74,    75,    76,    17,    78,    79,    17,    19,    33,
      75,   286,    43,    44,    45,    46,    47,    48,    37,    17,
     295,    75,    43,    54,    55,    41,    38,    58,    75,    38,
     214,    33,    75,    32,   310,    66,    67,    34,    10,    75,
      18,    76,    75,    75,   320,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    17,    57,
      58,    38,    18,    17,    43,    31,   244,    75,    66,    67,
      68,    69,    70,    19,    75,    73,    74,    75,    76,    19,
      78,    17,    75,   267,    19,    75,    19,    55,    17,    17,
      49,    50,    51,    52,    53,     6,    18,    17,    57,    75,
      75,    18,    17,    19,    18,    18,   284,    59,   292,    68,
      69,    70,    18,    75,    73,    74,    75,    76,    18,    78,
      49,    50,    51,    52,    53,    75,    57,    75,    57,    73,
      71,    18,    18,    60,    49,    50,    51,    52,    53,    68,
      69,    70,    57,    18,    73,    74,    75,    76,    18,    78,
      18,    75,    19,    68,    69,    70,    65,    19,    73,    74,
      75,    76,    18,    78,     4,     5,    18,    18,    62,     9,
      10,    11,    12,    13,    14,    15,    16,    38,    17,    64,
      20,    21,    22,    61,    18,    35,    62,    75,    28,    29,
      18,   197,    19,    18,   228,   316,   188,    37,   220,    39,
      99,   261,    42,   308,   320,   286,    -1,    -1,    -1,    -1,
     240
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    14,    15,
      16,    20,    21,    22,    28,    29,    37,    39,    42,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    97,    98,   109,   115,   116,   119,   120,   121,
     144,   145,   146,     6,     8,    56,    72,     6,     8,    17,
      49,    50,    51,    52,    53,    57,    68,    69,    70,    73,
      74,    75,    76,    78,   104,   106,   107,   108,   114,   122,
     123,   126,    40,    79,   105,   123,   124,    75,     7,    31,
      33,    75,    75,    40,    84,     0,     3,   147,    75,    75,
       8,    75,    75,    75,   123,    30,   123,    17,    17,    19,
      77,    78,    79,    80,    19,   127,    71,    75,   125,    33,
      75,    75,    37,    43,    41,    17,    71,    38,    75,    17,
      71,    38,    18,    75,    79,    78,   112,   113,   114,   126,
      40,    75,    79,   122,   123,   123,   123,   123,   105,    40,
      52,    75,    75,    32,    34,   133,    75,   117,   114,    76,
      75,   100,   120,    75,    38,    75,   120,    75,    73,    74,
      18,    19,    18,    19,    18,    18,    30,    18,   127,   125,
      17,    17,    43,    44,    45,    46,    47,    48,    54,    55,
      58,    66,    67,   105,   140,   142,   143,    43,    19,   118,
      31,    23,    24,    25,    26,    27,   103,    19,    99,    17,
      75,    19,    96,   112,   112,    75,    19,   128,   112,   120,
      54,    66,    67,    55,   143,    35,    36,    17,    17,   114,
     117,   133,     6,    55,    57,   101,    17,   101,   100,    18,
      75,    17,    75,    18,    18,    18,    18,    75,    59,   136,
     137,    19,   111,    18,    17,   105,   140,   140,   120,   120,
     118,    75,    57,    73,   102,    99,   120,    96,    75,    96,
      71,   125,    60,   133,   136,   112,    18,   143,   114,   120,
     141,    18,    18,    18,    18,    96,   120,   128,    75,    65,
     135,   111,    19,   110,    17,   105,    19,    18,    18,   101,
      18,    38,    62,    64,   134,    17,   120,   114,   141,   138,
     139,   142,   105,   140,    61,   129,   112,    18,    35,   127,
      62,   111,   139,   126,   131,   132,    18,    11,    63,   130,
      19,   110,   132
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    94,    95,    95,    96,    96,    97,
      98,    98,    98,    99,    99,   100,   100,   100,   101,   101,
     101,   102,   103,   103,   103,   103,   104,   104,   104,   105,
     106,   106,   106,   106,   107,   107,   107,   107,   107,   108,
     108,   108,   108,   109,   110,   110,   111,   111,   112,   112,
     113,   113,   114,   114,   114,   114,   115,   116,   117,   117,
     118,   118,   119,   120,   120,   121,   122,   122,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   124,   124,
     124,   125,   125,   125,   125,   125,   126,   126,   126,   127,
     127,   128,   128,   129,   129,   130,   130,   130,   131,   132,
     132,   133,   133,   134,   134,   135,   135,   136,   136,   137,
     138,   139,   139,   139,   140,   140,   140,   140,   141,   141,
     142,   142,   142,   142,   142,   142,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     144,   145,   146,   147,   147
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     5,     9,     9,    10,     0,     3,     5,
       7,     5,     8,     0,     3,     6,     3,     3,     0,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       4,     6,     4,     6,     1,     1,     1,     1,     1,     4,
       6,     4,     4,     9,     0,     6,     0,     3,     1,     1,
       2,     2,     1,     1,     1,     1,     4,     6,     3,     5,
       0,     3,     1,    11,     3,     2,     1,     3,     3,     3,
       3,     3,     3,     2,     1,     1,     1,     1,     1,     1,
       2,     0,     1,     2,     2,     2,     3,     3,     1,     0,
       3,     0,     4,     0,     3,     0,     1,     1,     2,     1,
       3,     0,     2,     0,     2,     0,     4,     0,     2,     5,
       1,     0,     1,     3,     0,     1,     3,     3,     3,     3,
       3,     5,     5,     7,     4,     5,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     1,     2,     1,     2,
       7,     2,     4,     0,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 249 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1844 "yacc_sql.cpp"
    break;

  case 24:
#line 280 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1853 "yacc_sql.cpp"
    break;

  case 25:
#line 286 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1861 "yacc_sql.cpp"
    break;

  case 26:
#line 291 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1869 "yacc_sql.cpp"
    break;

  case 27:
#line 297 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1877 "yacc_sql.cpp"
    break;

  case 28:
#line 303 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1885 "yacc_sql.cpp"
    break;

  case 29:
#line 309 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1893 "yacc_sql.cpp"
    break;

  case 30:
#line 315 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1903 "yacc_sql.cpp"
    break;

  case 31:
#line 322 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1911 "yacc_sql.cpp"
    break;

  case 32:
#line 328 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1921 "yacc_sql.cpp"
    break;

  case 33:
#line 336 "yacc_sql.y"
                                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
      (yyval.sql_node)->create_view.view_name = (yyvsp[-2].string);
      (yyval.sql_node)->create_view.select = (yyvsp[0].select_body);
      free((yyvsp[-2].string));
    }
#line 1932 "yacc_sql.cpp"
    break;

  case 34:
#line 342 "yacc_sql.y"
                                                             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
      (yyval.sql_node)->create_view.view_name = (yyvsp[-6].string);
      (yyval.sql_node)->create_view.select = (yyvsp[0].select_body);
      if ((yyvsp[-3].attribute_list) != nullptr) {
        (yyval.sql_node)->create_view.attributes = *(yyvsp[-3].attribute_list);
      } else {
        (yyval.sql_node)->create_view.attributes = std::vector<std::string>();
      }
      (yyval.sql_node)->create_view.attributes.emplace_back((yyvsp[-4].string));
      std::reverse((yyval.sql_node)->create_view.attributes.begin(), (yyval.sql_node)->create_view.attributes.end());
      free((yyvsp[-6].string));
    }
#line 1950 "yacc_sql.cpp"
    break;

  case 35:
#line 359 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);

      if ((yyvsp[-1].attribute_list) != nullptr) {
        create_index.attributes = *(yyvsp[-1].attribute_list);
      } else {
        create_index.attributes = std::vector<std::string>();
      }
      std::string first = (yyvsp[-2].string);
      create_index.attributes.insert(create_index.attributes.begin(), first);
      create_index.unique = false;

      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
      free((yyvsp[-1].attribute_list));
    }
#line 1975 "yacc_sql.cpp"
    break;

  case 36:
#line 380 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);

      if ((yyvsp[-1].attribute_list) != nullptr) {
        create_index.attributes = *(yyvsp[-1].attribute_list);
      } else {
        create_index.attributes = std::vector<std::string>();
      }
      std::string first = (yyvsp[-2].string);
      create_index.attributes.insert(create_index.attributes.begin(), first);
      create_index.unique = true;

      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
      free((yyvsp[-1].attribute_list));
    }
#line 2000 "yacc_sql.cpp"
    break;

  case 37:
#line 403 "yacc_sql.y"
  {
    (yyval.attribute_list) = nullptr;
  }
#line 2008 "yacc_sql.cpp"
    break;

  case 38:
#line 407 "yacc_sql.y"
  {
    if ((yyvsp[0].attribute_list) != nullptr) {
      (yyval.attribute_list) = (yyvsp[0].attribute_list);
    } else {
      (yyval.attribute_list) = new std::vector<std::string>;
    }

    (yyval.attribute_list)->emplace_back((yyvsp[-1].string));
    free((yyvsp[-1].string));
  }
#line 2023 "yacc_sql.cpp"
    break;

  case 39:
#line 421 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2035 "yacc_sql.cpp"
    break;

  case 40:
#line 431 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 2055 "yacc_sql.cpp"
    break;

  case 41:
#line 447 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));

      create_table.select = (yyvsp[0].select_body);
    }
#line 2068 "yacc_sql.cpp"
    break;

  case 42:
#line 456 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-3].attr_info);

      create_table.select = (yyvsp[0].select_body);
    }
#line 2090 "yacc_sql.cpp"
    break;

  case 43:
#line 476 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2098 "yacc_sql.cpp"
    break;

  case 44:
#line 480 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2112 "yacc_sql.cpp"
    break;

  case 45:
#line 493 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].is_null);
      free((yyvsp[-5].string));
    }
#line 2125 "yacc_sql.cpp"
    break;

  case 46:
#line 502 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = TEXTS;
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 8;
      (yyval.attr_info)->nullable = (yyvsp[0].is_null);
      free((yyvsp[-2].string));
    }
#line 2138 "yacc_sql.cpp"
    break;

  case 47:
#line 511 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].is_null);
      free((yyvsp[-2].string));
    }
#line 2151 "yacc_sql.cpp"
    break;

  case 48:
#line 522 "yacc_sql.y"
  {
    (yyval.is_null) = true;
  }
#line 2159 "yacc_sql.cpp"
    break;

  case 49:
#line 526 "yacc_sql.y"
  {
    (yyval.is_null) = false;
  }
#line 2167 "yacc_sql.cpp"
    break;

  case 50:
#line 530 "yacc_sql.y"
  {
    (yyval.is_null) = true;
  }
#line 2175 "yacc_sql.cpp"
    break;

  case 51:
#line 536 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2181 "yacc_sql.cpp"
    break;

  case 52:
#line 541 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2187 "yacc_sql.cpp"
    break;

  case 53:
#line 542 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2193 "yacc_sql.cpp"
    break;

  case 54:
#line 543 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2199 "yacc_sql.cpp"
    break;

  case 55:
#line 544 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2205 "yacc_sql.cpp"
    break;

  case 56:
#line 549 "yacc_sql.y"
           { (yyval.func_t)=LENGTH_T; }
#line 2211 "yacc_sql.cpp"
    break;

  case 57:
#line 550 "yacc_sql.y"
                  { (yyval.func_t)=DATE_FORMAT_T; }
#line 2217 "yacc_sql.cpp"
    break;

  case 58:
#line 551 "yacc_sql.y"
            { (yyval.func_t)=ROUND_T; }
#line 2223 "yacc_sql.cpp"
    break;

  case 59:
#line 555 "yacc_sql.y"
                              {
      (yyval.expr_attr) = new RelAttrSqlNode;
      (yyval.expr_attr)->is_expr = true;
      (yyval.expr_attr)->expr = (yyvsp[-1].expression);
      (yyval.expr_attr)->alias = (yyvsp[0].string);
    }
#line 2234 "yacc_sql.cpp"
    break;

  case 60:
#line 564 "yacc_sql.y"
    {
      (yyval.normal_func) = new RelAttrSqlNode;
      (yyval.normal_func)->is_aggr = false;

      (yyval.normal_func)->is_func = true;
      (yyval.normal_func)->func_type = (yyvsp[-3].func_t);
      (yyval.normal_func)->first_func_arg.is_valid = true;
      (yyval.normal_func)->first_func_arg.is_attr = true;
      (yyval.normal_func)->first_func_arg.relation_name = (yyvsp[-1].rel_attr)->relation_name;
      (yyval.normal_func)->first_func_arg.attribute_name = (yyvsp[-1].rel_attr)->attribute_name;

      (yyval.normal_func)->second_func_arg.is_valid = false;

      free((yyvsp[-1].rel_attr));
    }
#line 2254 "yacc_sql.cpp"
    break;

  case 61:
#line 581 "yacc_sql.y"
    {
      (yyval.normal_func) = new RelAttrSqlNode;
      (yyval.normal_func)->is_aggr = false;

      (yyval.normal_func)->is_func = true;
      (yyval.normal_func)->func_type = (yyvsp[-5].func_t);
      (yyval.normal_func)->first_func_arg.is_valid = true;
      (yyval.normal_func)->first_func_arg.is_attr = true;
      (yyval.normal_func)->first_func_arg.relation_name = (yyvsp[-3].rel_attr)->relation_name;
      (yyval.normal_func)->first_func_arg.attribute_name = (yyvsp[-3].rel_attr)->attribute_name;

      (yyval.normal_func)->second_func_arg.is_valid = true;
      (yyval.normal_func)->second_func_arg.is_attr = false;
      (yyval.normal_func)->second_func_arg.value = *(yyvsp[-1].value);

      free((yyvsp[-3].rel_attr));
      free((yyvsp[-1].value));
    }
#line 2277 "yacc_sql.cpp"
    break;

  case 62:
#line 601 "yacc_sql.y"
    {
      (yyval.normal_func) = new RelAttrSqlNode;
      (yyval.normal_func)->is_aggr = false;

      (yyval.normal_func)->is_func = true;
      (yyval.normal_func)->func_type = (yyvsp[-3].func_t);
      (yyval.normal_func)->first_func_arg.is_valid = true;
      (yyval.normal_func)->first_func_arg.is_attr = false;
      (yyval.normal_func)->first_func_arg.value = *(yyvsp[-1].value);

      (yyval.normal_func)->second_func_arg.is_valid = false;
      free((yyvsp[-1].value));

    }
#line 2296 "yacc_sql.cpp"
    break;

  case 63:
#line 617 "yacc_sql.y"
    {
      (yyval.normal_func) = new RelAttrSqlNode;
      (yyval.normal_func)->is_aggr = false;

      (yyval.normal_func)->is_func = true;
      (yyval.normal_func)->func_type = (yyvsp[-5].func_t);
      (yyval.normal_func)->first_func_arg.is_valid = true;
      (yyval.normal_func)->first_func_arg.is_attr = false;
      (yyval.normal_func)->first_func_arg.value = *(yyvsp[-3].value);

      (yyval.normal_func)->second_func_arg.is_valid = true;
      (yyval.normal_func)->second_func_arg.is_attr = false;
      (yyval.normal_func)->second_func_arg.value = *(yyvsp[-1].value);

      free((yyvsp[-3].value));
      free((yyvsp[-1].value));
    }
#line 2318 "yacc_sql.cpp"
    break;

  case 64:
#line 637 "yacc_sql.y"
        { (yyval.aggr_t)=MAX_T; }
#line 2324 "yacc_sql.cpp"
    break;

  case 65:
#line 638 "yacc_sql.y"
          { (yyval.aggr_t)=MIN_T; }
#line 2330 "yacc_sql.cpp"
    break;

  case 66:
#line 639 "yacc_sql.y"
          { (yyval.aggr_t)=AVG_T; }
#line 2336 "yacc_sql.cpp"
    break;

  case 67:
#line 640 "yacc_sql.y"
          { (yyval.aggr_t)=SUM_T; }
#line 2342 "yacc_sql.cpp"
    break;

  case 68:
#line 641 "yacc_sql.y"
            { (yyval.aggr_t)=COUNT_T; }
#line 2348 "yacc_sql.cpp"
    break;

  case 69:
#line 646 "yacc_sql.y"
    {
      (yyval.aggr_func) = new RelAttrSqlNode;
      (yyval.aggr_func)->is_aggr = true;
      (yyval.aggr_func)->aggr_type = (yyvsp[-3].aggr_t);
      (yyval.aggr_func)->attribute_name = (yyvsp[-1].string);
      free((yyvsp[-1].string));
    }
#line 2360 "yacc_sql.cpp"
    break;

  case 70:
#line 653 "yacc_sql.y"
                                        {
      (yyval.aggr_func) = new RelAttrSqlNode;
      (yyval.aggr_func)->is_aggr = true;
      (yyval.aggr_func)->aggr_type = (yyvsp[-5].aggr_t);
      (yyval.aggr_func)->relation_name  = (yyvsp[-3].string);
      (yyval.aggr_func)->attribute_name = (yyvsp[-1].string);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));

		}
#line 2375 "yacc_sql.cpp"
    break;

  case 71:
#line 663 "yacc_sql.y"
                                              {
      (yyval.aggr_func) = new RelAttrSqlNode;
      (yyval.aggr_func)->is_aggr = true;
      (yyval.aggr_func)->aggr_type = (yyvsp[-3].aggr_t);
      (yyval.aggr_func)->attribute_name = "*";
		}
#line 2386 "yacc_sql.cpp"
    break;

  case 72:
#line 669 "yacc_sql.y"
                                   {
      (yyval.aggr_func) = new RelAttrSqlNode;
      (yyval.aggr_func)->is_aggr = true;
      (yyval.aggr_func)->aggr_type = (yyvsp[-3].aggr_t);
      (yyval.aggr_func)->attribute_name = "data";
		}
#line 2397 "yacc_sql.cpp"
    break;

  case 73:
#line 679 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-6].string);
      std::vector<Value> first_value;
      if ((yyvsp[-2].value_list) != nullptr) {
        first_value.swap(*(yyvsp[-2].value_list));
      }
      first_value.emplace_back(*(yyvsp[-3].value));
      std::reverse(first_value.begin(), first_value.end());

      if ((yyvsp[0].insert_list) != nullptr) {
        (yyval.sql_node)->insertion.insert_values.swap(*(yyvsp[0].insert_list));
      }
      (yyval.sql_node)->insertion.insert_values.emplace_back(std::move(first_value));
      std::reverse((yyval.sql_node)->insertion.insert_values.begin(), (yyval.sql_node)->insertion.insert_values.end());

      delete (yyvsp[-3].value);
      free((yyvsp[-6].string));
      delete (yyvsp[0].insert_list);
      delete (yyvsp[-2].value_list);
    }
#line 2423 "yacc_sql.cpp"
    break;

  case 74:
#line 703 "yacc_sql.y"
  {
    (yyval.insert_list) = nullptr;
  }
#line 2431 "yacc_sql.cpp"
    break;

  case 75:
#line 707 "yacc_sql.y"
  {
    std::vector<Value> first_value;
    if ((yyvsp[-2].value_list) != nullptr) {
      first_value.swap(*(yyvsp[-2].value_list));
    }
    first_value.emplace_back(*(yyvsp[-3].value));
    std::reverse(first_value.begin(), first_value.end());

    if ((yyvsp[0].insert_list) != nullptr) {
      (yyval.insert_list) = (yyvsp[0].insert_list);
    } else {
      (yyval.insert_list) = new std::vector<std::vector<Value>>;
    }
    (yyval.insert_list)->emplace_back(std::move(first_value));
    delete (yyvsp[0].insert_list);
  }
#line 2452 "yacc_sql.cpp"
    break;

  case 76:
#line 727 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2460 "yacc_sql.cpp"
    break;

  case 77:
#line 730 "yacc_sql.y"
                                 {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2474 "yacc_sql.cpp"
    break;

  case 78:
#line 743 "yacc_sql.y"
    {
      (yyval.value) = (yyvsp[0].value);
    }
#line 2482 "yacc_sql.cpp"
    break;

  case 79:
#line 748 "yacc_sql.y"
    {
      (yyval.value) = (yyvsp[0].value);
    }
#line 2490 "yacc_sql.cpp"
    break;

  case 80:
#line 752 "yacc_sql.y"
                            {
      (yyval.value) = new Value(0-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2499 "yacc_sql.cpp"
    break;

  case 81:
#line 756 "yacc_sql.y"
               {
      (yyval.value) = new Value(0-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2508 "yacc_sql.cpp"
    break;

  case 82:
#line 762 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2517 "yacc_sql.cpp"
    break;

  case 83:
#line 766 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2526 "yacc_sql.cpp"
    break;

  case 84:
#line 770 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2536 "yacc_sql.cpp"
    break;

  case 85:
#line 775 "yacc_sql.y"
            {
      (yyval.value) = new Value(); // UNDEFINED TYPE HERE
      (yyval.value)->set_null();
    }
#line 2545 "yacc_sql.cpp"
    break;

  case 86:
#line 783 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2559 "yacc_sql.cpp"
    break;

  case 87:
#line 796 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-4].string);

      if ((yyvsp[-1].update_list) != nullptr) {
        (yyval.sql_node)->update.update_list.swap(*(yyvsp[-1].update_list));
        delete (yyvsp[-1].update_list);
      }
      (yyval.sql_node)->update.update_list.emplace_back(*(yyvsp[-2].update_pair));
      delete (yyvsp[-2].update_pair);
      std::reverse((yyval.sql_node)->update.update_list.begin(), (yyval.sql_node)->update.update_list.end());

      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-4].string));
    }
#line 2582 "yacc_sql.cpp"
    break;

  case 88:
#line 817 "yacc_sql.y"
  {
    (yyval.update_pair) = new UpdateListSqlNode{(yyvsp[-2].string), *(yyvsp[0].value), SelectSqlNode{}, false};
    free((yyvsp[0].value));
  }
#line 2591 "yacc_sql.cpp"
    break;

  case 89:
#line 822 "yacc_sql.y"
  {
    (yyval.update_pair) = new UpdateListSqlNode{(yyvsp[-4].string), Value{}, *(yyvsp[-1].select_body), true};
    free((yyvsp[-1].select_body));
  }
#line 2600 "yacc_sql.cpp"
    break;

  case 90:
#line 828 "yacc_sql.y"
    {
      (yyval.update_list) = nullptr;
    }
#line 2608 "yacc_sql.cpp"
    break;

  case 91:
#line 832 "yacc_sql.y"
    {
      if ((yyvsp[0].update_list) != nullptr) {
        (yyval.update_list) = (yyvsp[0].update_list);
      } else {
        (yyval.update_list) = new std::vector<UpdateListSqlNode>;
      }

      (yyval.update_list)->emplace_back(*(yyvsp[-1].update_pair));
      free((yyvsp[-1].update_pair));
    }
#line 2623 "yacc_sql.cpp"
    break;

  case 92:
#line 847 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      (yyval.sql_node)->selection = *(yyvsp[0].select_body);
      delete (yyvsp[0].select_body);
    }
#line 2633 "yacc_sql.cpp"
    break;

  case 93:
#line 857 "yacc_sql.y"
    {
      (yyval.select_body) = new SelectSqlNode;
      if ((yyvsp[-9].rel_attr_list) != nullptr) {
        (yyval.select_body)->attributes.swap(*(yyvsp[-9].rel_attr_list));
        delete (yyvsp[-9].rel_attr_list);
      }

      // relation list
      if ((yyvsp[-5].relation_list) != nullptr) {
        (yyval.select_body)->relations.swap(*(yyvsp[-5].relation_list));
        delete (yyvsp[-5].relation_list);
      }
      (yyval.select_body)->relations.push_back({(yyvsp[-7].string), (yyvsp[-6].string)});
      std::reverse((yyval.select_body)->relations.begin(), (yyval.select_body)->relations.end());

      // inner join
      if ((yyvsp[-4].inner_join_list) != nullptr) {
        (yyval.select_body)->joins.swap(*(yyvsp[-4].inner_join_list));
        std::reverse((yyval.select_body)->joins.begin(), (yyval.select_body)->joins.end());
        delete (yyvsp[-4].inner_join_list);
      }

      // where conditions
      if ((yyvsp[-3].condition_list) != nullptr) {
        (yyval.select_body)->conditions.swap(*(yyvsp[-3].condition_list));
        delete (yyvsp[-3].condition_list);
      }

      // group by
      if ((yyvsp[-2].rel_attr_list) != nullptr) {
        (yyval.select_body)->group_bys.swap(*(yyvsp[-2].rel_attr_list));
        delete (yyvsp[-2].rel_attr_list);
      }

      // having
      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.select_body)->havings.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }

      // order by
      if ((yyvsp[0].order_by_list) != nullptr) {
        (yyval.select_body)->order_bys.swap(*(yyvsp[0].order_by_list));
        delete (yyvsp[0].order_by_list);
      }
      std::reverse((yyval.select_body)->order_bys.begin(), (yyval.select_body)->order_bys.end());
      free((yyvsp[-7].string));
    }
#line 2686 "yacc_sql.cpp"
    break;

  case 94:
#line 906 "yacc_sql.y"
    {
      (yyval.select_body) = new SelectSqlNode;
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.select_body)->attributes.swap(*(yyvsp[0].rel_attr_list));
        delete (yyvsp[0].rel_attr_list);
      }
      (yyval.select_body)->attributes.emplace_back(*(yyvsp[-1].expr_attr));
      free((yyvsp[-1].expr_attr));
    }
#line 2700 "yacc_sql.cpp"
    break;

  case 95:
#line 919 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2711 "yacc_sql.cpp"
    break;

  case 96:
#line 929 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2720 "yacc_sql.cpp"
    break;

  case 97:
#line 934 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2733 "yacc_sql.cpp"
    break;

  case 98:
#line 945 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
      LOG_DEBUG("ADD");
    }
#line 2742 "yacc_sql.cpp"
    break;

  case 99:
#line 949 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
      LOG_DEBUG("SUB");
    }
#line 2751 "yacc_sql.cpp"
    break;

  case 100:
#line 953 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
      LOG_DEBUG("MUL");
    }
#line 2760 "yacc_sql.cpp"
    break;

  case 101:
#line 957 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
      LOG_DEBUG("DIV");
    }
#line 2769 "yacc_sql.cpp"
    break;

  case 102:
#line 961 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      LOG_DEBUG("()");
    }
#line 2779 "yacc_sql.cpp"
    break;

  case 103:
#line 966 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
      LOG_DEBUG("-");
    }
#line 2788 "yacc_sql.cpp"
    break;

  case 104:
#line 970 "yacc_sql.y"
               {
      (yyval.expression) = new FieldExpr(*(yyvsp[0].rel_attr));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2798 "yacc_sql.cpp"
    break;

  case 105:
#line 975 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2808 "yacc_sql.cpp"
    break;

  case 106:
#line 980 "yacc_sql.y"
                {
      (yyval.expression) = new AggregateExpr(*(yyvsp[0].aggr_func));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].aggr_func);
    }
#line 2818 "yacc_sql.cpp"
    break;

  case 107:
#line 985 "yacc_sql.y"
                  {
      (yyval.expression) = new FunctionExpr(*(yyvsp[0].normal_func));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].normal_func);
    }
#line 2828 "yacc_sql.cpp"
    break;

  case 108:
#line 994 "yacc_sql.y"
        {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      attr.expr = new FieldExpr("*");
      attr.is_expr = true;
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 2842 "yacc_sql.cpp"
    break;

  case 109:
#line 1003 "yacc_sql.y"
           {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "data";
      attr.expr = new FieldExpr("data");
      attr.is_expr = true;
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 2856 "yacc_sql.cpp"
    break;

  case 110:
#line 1012 "yacc_sql.y"
                          {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].expr_attr));
      delete (yyvsp[-1].expr_attr);
    }
#line 2870 "yacc_sql.cpp"
    break;

  case 111:
#line 1024 "yacc_sql.y"
    {
      (yyval.string) = strdup("");
    }
#line 2878 "yacc_sql.cpp"
    break;

  case 112:
#line 1028 "yacc_sql.y"
    {
      (yyval.string) = strdup((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2887 "yacc_sql.cpp"
    break;

  case 113:
#line 1032 "yacc_sql.y"
            {
      (yyval.string) = strdup((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2896 "yacc_sql.cpp"
    break;

  case 114:
#line 1036 "yacc_sql.y"
             {
      (yyval.string) = strdup("sum");
    }
#line 2904 "yacc_sql.cpp"
    break;

  case 115:
#line 1039 "yacc_sql.y"
              {
      (yyval.string) = strdup("data");
    }
#line 2912 "yacc_sql.cpp"
    break;

  case 116:
#line 1045 "yacc_sql.y"
              {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->is_aggr = false;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      (yyval.rel_attr)->alias = "";
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2926 "yacc_sql.cpp"
    break;

  case 117:
#line 1054 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->is_aggr = false;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = '*';
      free((yyvsp[-2].string));
    }
#line 2938 "yacc_sql.cpp"
    break;

  case 118:
#line 1061 "yacc_sql.y"
         {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->is_aggr = false;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      (yyval.rel_attr)->alias = "";
      free((yyvsp[0].string));
    }
#line 2950 "yacc_sql.cpp"
    break;

  case 119:
#line 1072 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2958 "yacc_sql.cpp"
    break;

  case 120:
#line 1075 "yacc_sql.y"
                                {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }

      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].expr_attr));
      delete (yyvsp[-1].expr_attr);
    }
#line 2973 "yacc_sql.cpp"
    break;

  case 121:
#line 1089 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2981 "yacc_sql.cpp"
    break;

  case 122:
#line 1092 "yacc_sql.y"
                                       {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<std::pair<std::string, std::string>>;
      }

      (yyval.relation_list)->push_back({(yyvsp[-2].string), (yyvsp[-1].string)});
      free((yyvsp[-2].string));
      free((yyvsp[-1].string));
    }
#line 2997 "yacc_sql.cpp"
    break;

  case 123:
#line 1106 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 3005 "yacc_sql.cpp"
    break;

  case 124:
#line 1110 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 3013 "yacc_sql.cpp"
    break;

  case 125:
#line 1116 "yacc_sql.y"
    {
      (yyval.order_t) = ASC_T;
    }
#line 3021 "yacc_sql.cpp"
    break;

  case 126:
#line 1121 "yacc_sql.y"
    {
      (yyval.order_t) = ASC_T;
    }
#line 3029 "yacc_sql.cpp"
    break;

  case 127:
#line 1126 "yacc_sql.y"
    {
      (yyval.order_t) = DESC_T;
    }
#line 3037 "yacc_sql.cpp"
    break;

  case 128:
#line 1133 "yacc_sql.y"
    {
        (yyval.order_by_attr) = new OrderBySqlNode;
        (yyval.order_by_attr)->attr = *(yyvsp[-1].rel_attr);
        (yyval.order_by_attr)->order_type = (yyvsp[0].order_t);
        delete (yyvsp[-1].rel_attr);
    }
#line 3048 "yacc_sql.cpp"
    break;

  case 129:
#line 1143 "yacc_sql.y"
    {
      (yyval.order_by_list) = new std::vector<OrderBySqlNode>;
      (yyval.order_by_list)->emplace_back(*(yyvsp[0].order_by_attr));
      delete (yyvsp[0].order_by_attr);
    }
#line 3058 "yacc_sql.cpp"
    break;

  case 130:
#line 1148 "yacc_sql.y"
                                        {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
      (yyval.order_by_list)->emplace_back(*(yyvsp[-2].order_by_attr));
      delete (yyvsp[-2].order_by_attr);
    }
#line 3068 "yacc_sql.cpp"
    break;

  case 131:
#line 1157 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3076 "yacc_sql.cpp"
    break;

  case 132:
#line 1160 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3084 "yacc_sql.cpp"
    break;

  case 133:
#line 1168 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3092 "yacc_sql.cpp"
    break;

  case 134:
#line 1171 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3100 "yacc_sql.cpp"
    break;

  case 135:
#line 1177 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 3108 "yacc_sql.cpp"
    break;

  case 136:
#line 1180 "yacc_sql.y"
                                   {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].expr_attr));
      delete (yyvsp[-1].expr_attr);
    }
#line 3122 "yacc_sql.cpp"
    break;

  case 137:
#line 1192 "yacc_sql.y"
    {
      (yyval.inner_join_list) = nullptr;
    }
#line 3130 "yacc_sql.cpp"
    break;

  case 138:
#line 1195 "yacc_sql.y"
                                 {
      if ((yyvsp[0].inner_join_list) != nullptr) {
        (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
      } else {
        (yyval.inner_join_list) = new std::vector<InnerJoinSqlNode>;
      }
      (yyval.inner_join_list)->emplace_back(*(yyvsp[-1].inner_join));
      delete (yyvsp[-1].inner_join);
    }
#line 3144 "yacc_sql.cpp"
    break;

  case 139:
#line 1207 "yacc_sql.y"
                                         {
      (yyval.inner_join) = new InnerJoinSqlNode;
      (yyval.inner_join)->relation_name = (yyvsp[-2].string);
      (yyval.inner_join)->join_conditions.swap(*(yyvsp[0].condition_list));
      delete (yyvsp[0].condition_list);
    }
#line 3155 "yacc_sql.cpp"
    break;

  case 140:
#line 1217 "yacc_sql.y"
    {
      (yyval.condition) = (yyvsp[0].condition);
    }
#line 3163 "yacc_sql.cpp"
    break;

  case 141:
#line 1223 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3171 "yacc_sql.cpp"
    break;

  case 142:
#line 1227 "yacc_sql.y"
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3181 "yacc_sql.cpp"
    break;

  case 143:
#line 1232 "yacc_sql.y"
                                             {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3191 "yacc_sql.cpp"
    break;

  case 144:
#line 1241 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3199 "yacc_sql.cpp"
    break;

  case 145:
#line 1245 "yacc_sql.y"
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3209 "yacc_sql.cpp"
    break;

  case 146:
#line 1250 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3219 "yacc_sql.cpp"
    break;

  case 147:
#line 1255 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->is_and = false;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3230 "yacc_sql.cpp"
    break;

  case 148:
#line 1265 "yacc_sql.y"
                      {
      (yyval.value_list) = new std::vector<Value>;
      (yyval.value_list)->emplace_back(*(yyvsp[-2].value));
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
    }
#line 3242 "yacc_sql.cpp"
    break;

  case 149:
#line 1272 "yacc_sql.y"
                                   {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-2].value));
      delete (yyvsp[-2].value);
    }
#line 3256 "yacc_sql.cpp"
    break;

  case 150:
#line 1284 "yacc_sql.y"
                                {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].expr_attr);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].expr_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].expr_attr);
      delete (yyvsp[0].expr_attr);
    }
#line 3272 "yacc_sql.cpp"
    break;

  case 151:
#line 1296 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].expr_attr);
      (yyval.condition)->right_is_select = 1;
      (yyval.condition)->right_select = (yyvsp[-1].select_body);
      (yyval.condition)->comp = (yyvsp[-3].comp);
      delete (yyvsp[-4].expr_attr);
    }
#line 3286 "yacc_sql.cpp"
    break;

  case 152:
#line 1306 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_select = 1;
      (yyval.condition)->left_select = (yyvsp[-3].select_body);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].expr_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      delete (yyvsp[0].expr_attr);
    }
#line 3300 "yacc_sql.cpp"
    break;

  case 153:
#line 1316 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_select = 1;
      (yyval.condition)->left_select = (yyvsp[-5].select_body);
      (yyval.condition)->right_is_select = 1;
      (yyval.condition)->right_select = (yyvsp[-1].select_body);
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 3313 "yacc_sql.cpp"
    break;

  case 154:
#line 1325 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_select = 0;
      (yyval.condition)->right_is_select = 1;
      (yyval.condition)->right_select = (yyvsp[-1].select_body);
      (yyval.condition)->comp = (yyvsp[-3].comp);
      (yyval.condition)->unary_op = 1;
    }
#line 3326 "yacc_sql.cpp"
    break;

  case 155:
#line 1334 "yacc_sql.y"
    {
      // HERE
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].expr_attr);
      (yyval.condition)->right_is_select = 1;
      (yyval.condition)->comp = (yyvsp[-3].comp);
      (yyval.condition)->values.swap(*(yyvsp[-1].value_list));
      std::reverse((yyval.condition)->values.begin(), (yyval.condition)->values.end());
    }
#line 3341 "yacc_sql.cpp"
    break;

  case 156:
#line 1347 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3347 "yacc_sql.cpp"
    break;

  case 157:
#line 1348 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3353 "yacc_sql.cpp"
    break;

  case 158:
#line 1349 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3359 "yacc_sql.cpp"
    break;

  case 159:
#line 1350 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3365 "yacc_sql.cpp"
    break;

  case 160:
#line 1351 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3371 "yacc_sql.cpp"
    break;

  case 161:
#line 1352 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3377 "yacc_sql.cpp"
    break;

  case 162:
#line 1353 "yacc_sql.y"
           { (yyval.comp) = STR_LIKE; }
#line 3383 "yacc_sql.cpp"
    break;

  case 163:
#line 1354 "yacc_sql.y"
               { (yyval.comp) = STR_NOT_LIKE; }
#line 3389 "yacc_sql.cpp"
    break;

  case 164:
#line 1355 "yacc_sql.y"
           { (yyval.comp) = IS; }
#line 3395 "yacc_sql.cpp"
    break;

  case 165:
#line 1356 "yacc_sql.y"
               { (yyval.comp) = IS_NOT; }
#line 3401 "yacc_sql.cpp"
    break;

  case 166:
#line 1357 "yacc_sql.y"
           { (yyval.comp) = IN; }
#line 3407 "yacc_sql.cpp"
    break;

  case 167:
#line 1358 "yacc_sql.y"
               { (yyval.comp) = IN_NOT; }
#line 3413 "yacc_sql.cpp"
    break;

  case 168:
#line 1359 "yacc_sql.y"
              { (yyval.comp) = EXIST; }
#line 3419 "yacc_sql.cpp"
    break;

  case 169:
#line 1360 "yacc_sql.y"
                  { (yyval.comp) = EXIST_NOT; }
#line 3425 "yacc_sql.cpp"
    break;

  case 170:
#line 1365 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);

      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3439 "yacc_sql.cpp"
    break;

  case 171:
#line 1378 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3448 "yacc_sql.cpp"
    break;

  case 172:
#line 1386 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3460 "yacc_sql.cpp"
    break;


#line 3464 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1398 "yacc_sql.y"

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
