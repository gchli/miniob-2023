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
    NUMBER = 327,
    FLOAT = 328,
    ID = 329,
    SSS = 330,
    UMINUS = 331
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 128 "yacc_sql.y"

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
  RelAttrSqlNode *                  rel_attr;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  Expression *                      expression;
  std::vector<Expression *> *       expression_list;
  std::vector<Value> *              value_list;
  std::vector<std::vector<Value>> * insert_list;
  std::vector<ConditionSqlNode> *   condition_list;
  std::vector<RelAttrSqlNode> *     rel_attr_list;
  // std::vector<std::string> *        relation_list;
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

#line 279 "yacc_sql.cpp"

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
#define YYFINAL  80
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   373

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  172
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  331

#define YYUNDEFTOK  2
#define YYMAXUTOK   331


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
       2,     2,    78,    76,     2,    77,     2,    79,     2,     2,
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
      75,    80
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   239,   239,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   270,   276,   281,   287,   293,   299,   305,
     312,   318,   326,   347,   371,   374,   388,   398,   417,   420,
     433,   442,   451,   463,   466,   470,   477,   482,   483,   484,
     485,   490,   491,   492,   496,   515,   537,   556,   579,   580,
     581,   582,   583,   587,   597,   608,   619,   644,   647,   668,
     671,   683,   687,   691,   696,   703,   715,   736,   741,   748,
     751,   766,   776,   826,   837,   847,   852,   864,   867,   870,
     873,   876,   880,   883,   891,   900,   909,   918,   930,   933,
     938,   946,   954,   968,   971,   981,   991,  1005,  1008,  1022,
    1025,  1032,  1036,  1041,  1048,  1058,  1064,  1073,  1076,  1084,
    1087,  1093,  1096,  1105,  1114,  1126,  1129,  1141,  1150,  1157,
    1160,  1166,  1175,  1178,  1184,  1189,  1198,  1210,  1222,  1234,
    1246,  1258,  1270,  1282,  1294,  1306,  1318,  1330,  1340,  1350,
    1360,  1370,  1379,  1388,  1404,  1405,  1406,  1407,  1408,  1409,
    1410,  1411,  1412,  1413,  1414,  1415,  1416,  1417,  1421,  1434,
    1442,  1452,  1453
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
  "DATE_FORMAT", "ROUND", "AS", "NUMBER", "FLOAT", "ID", "SSS", "'+'",
  "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "id_list", "drop_index_stmt",
  "create_table_stmt", "attr_def_list", "attr_def", "attr_null", "number",
  "type", "func_type", "normal_func", "aggr_type", "aggr_func",
  "insert_stmt", "insert_list", "value_list", "value", "delete_stmt",
  "update_stmt", "update_pair", "update_list", "select_stmt",
  "select_body", "calc_stmt", "expression_list", "expression",
  "select_attr", "alias_optional", "rel_attr", "attr_list", "rel_list",
  "order_by", "order_type", "order_by_attr", "order_by_list", "where",
  "having", "group_by", "inner_join_list", "inner_join", "join_condition",
  "join_condition_list", "condition_list", "condition", "comp_op",
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
     325,   326,   327,   328,   329,   330,    43,    45,    42,    47,
     331
};
# endif

#define YYPACT_NINF (-274)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     263,    16,    45,     8,    73,   -48,    30,  -274,    27,    33,
      40,  -274,  -274,  -274,  -274,  -274,    57,    93,   263,   136,
     154,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,    84,    85,   165,   103,   106,     8,  -274,  -274,
    -274,  -274,     8,  -274,  -274,    14,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,  -274,   105,  -274,   180,   169,   181,   169,
     162,   169,  -274,  -274,   125,   135,   174,   158,   179,  -274,
    -274,  -274,  -274,   202,   184,   150,  -274,   187,    -8,  -274,
       8,     8,     8,     8,     8,   161,   166,  -274,  -274,   -25,
     178,  -274,   -39,  -274,   167,  -274,   213,   215,   176,   -30,
     183,   177,   185,   222,   195,  -274,  -274,    51,    51,  -274,
    -274,    35,  -274,    89,   127,   169,   169,   169,    10,   243,
      35,   253,   117,  -274,   228,   261,  -274,   250,   230,   267,
     265,   214,  -274,  -274,    35,   -30,    35,   -30,  -274,  -274,
    -274,    35,   216,    35,   268,   -30,   279,  -274,  -274,  -274,
    -274,  -274,  -274,  -274,    61,   239,  -274,  -274,   264,   264,
     264,   264,  -274,   104,   278,   121,   176,   215,   292,  -274,
    -274,  -274,  -274,    22,    -3,   177,   281,   227,   286,  -274,
     288,  -274,   295,  -274,   297,  -274,   242,   245,   298,   302,
    -274,  -274,  -274,  -274,   266,   -30,   164,    80,   117,   117,
     279,   279,  -274,   261,  -274,   247,   269,  -274,  -274,   255,
    -274,   267,  -274,   306,   254,    35,    35,    35,    35,   272,
     215,   245,   -30,   311,   264,  -274,  -274,  -274,  -274,   279,
    -274,  -274,  -274,  -274,     3,  -274,  -274,  -274,  -274,  -274,
     315,   319,  -274,  -274,  -274,  -274,   324,  -274,   270,   325,
     306,  -274,  -274,  -274,   268,   271,   282,  -274,   298,   327,
      29,   330,   298,   331,  -274,  -274,    22,   306,  -274,   332,
    -274,   313,   290,   289,  -274,   337,  -274,   279,  -274,  -274,
    -274,   338,  -274,  -274,  -274,  -274,   117,   178,   117,   294,
     -30,   339,  -274,   323,  -274,  -274,   169,   169,   169,  -274,
     299,  -274,   298,  -274,   117,  -274,  -274,  -274,   285,   342,
    -274,     1,   343,  -274,   327,  -274,  -274,  -274,   285,  -274,
    -274
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     171,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,    81,     3,    18,
      19,    20,     0,     0,     0,     0,     0,     0,    74,    71,
      72,    73,     0,    93,    84,    85,    58,    59,    60,    61,
      62,    51,    52,    53,    98,    94,     0,   103,     0,   103,
      83,   103,    31,    30,     0,     0,     0,     0,     0,   169,
       1,   172,     2,     0,     0,     0,    29,     0,     0,    92,
       0,     0,     0,     0,     0,     0,     0,    99,   101,     0,
       0,    97,     0,    96,     0,    95,     0,   117,     0,     0,
       0,     0,     0,     0,     0,    91,    86,    87,    88,    89,
      90,    98,   100,     0,     0,   103,   103,   103,     0,     0,
      98,     0,   132,    75,     0,    79,   170,     0,     0,    38,
       0,     0,    36,   102,    98,     0,    98,     0,   106,   105,
     104,    98,     0,    98,   107,     0,     0,   154,   155,   156,
     157,   158,   159,   160,     0,   162,   164,   166,     0,     0,
       0,     0,   118,   133,     0,     0,     0,   117,     0,    47,
      48,    49,    50,    43,    43,     0,     0,     0,     0,    56,
       0,    54,     0,    63,     0,    65,     0,   125,    69,     0,
     161,   165,   167,   163,     0,     0,     0,     0,   132,   132,
       0,     0,    77,    79,    76,     0,     0,    45,    41,     0,
      42,    38,    37,    34,     0,    98,    98,    98,    98,     0,
     117,   125,     0,     0,     0,   144,   143,   140,   146,     0,
     142,   145,   137,   139,     0,   141,   136,   138,   134,   135,
       0,     0,    80,   168,    44,    46,     0,    39,     0,     0,
      34,    57,    55,    64,   107,     0,   121,   126,    69,    67,
       0,     0,    69,     0,   152,    78,    43,    34,    32,     0,
     108,     0,     0,   119,    70,     0,    66,     0,   150,   149,
     147,     0,   148,    40,    35,    33,   129,     0,   132,   109,
       0,     0,   153,   130,   127,   128,   103,   103,   103,   120,
       0,    82,    69,   151,   129,   124,   123,   122,     0,     0,
     131,   111,   115,   110,    67,   113,   112,   114,     0,    68,
     116
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -274,  -274,   345,  -274,  -274,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,  -172,  -274,  -274,   143,   182,  -182,  -274,
    -274,  -274,     0,  -274,    -1,  -274,    41,  -238,   -88,  -274,
    -274,   190,   155,  -274,  -155,  -274,   280,   171,  -274,  -115,
      -4,   -64,   107,  -274,  -274,  -274,    44,  -157,  -274,  -274,
     138,  -274,  -274,    59,  -200,  -273,  -152,  -274,  -274,  -274,
    -274
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   259,    31,    32,   186,   139,   218,   256,
     184,    66,   168,    68,   169,    33,   286,   233,    53,    34,
      35,   135,   177,    36,    37,    38,    54,    55,    70,    98,
     171,   101,   197,   311,   327,   322,   323,   133,   299,   283,
     230,   231,   303,   304,   172,   173,   174,    39,    40,    41,
      82
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      71,   199,   220,    69,    67,   103,   143,   105,   248,   249,
     115,   123,   325,     4,   219,   154,   204,   205,   206,   207,
     214,   136,    42,   305,    43,    47,    72,    48,   151,   189,
     284,   191,    48,    90,   291,   128,   193,    73,   195,   129,
     152,   305,    49,    50,   170,    51,   287,    49,    50,    64,
      51,    45,   216,    46,   217,   250,   251,   190,    74,   192,
      48,   148,   149,   150,   326,    48,    75,   198,    91,    92,
      93,    94,    44,   266,   319,    49,    50,   216,    51,   217,
      49,    50,   270,    51,   271,    52,    48,   212,   279,   273,
      91,    92,    93,    94,   293,   124,   127,   244,   309,   126,
     125,    49,    50,    64,    51,   294,    96,   144,   145,    97,
     261,   262,   263,   264,    76,   200,   236,   238,   242,   246,
     170,   170,    56,    57,    58,    59,    60,   201,   202,    93,
      94,    77,   301,    78,   156,    95,    80,    48,   211,   208,
     209,    61,    62,    63,   268,   146,   147,    64,    61,    62,
      63,    65,    49,    50,    64,    51,   272,    81,    83,    84,
     157,   158,   159,   160,   161,   162,    56,    57,    58,    59,
      60,   163,   164,    85,    48,   165,    96,    86,    48,    97,
      87,   239,   288,   166,   167,    61,    62,    63,   100,    49,
      50,    64,    51,    49,    50,   104,    51,    99,   102,   106,
     237,   109,   243,   247,   235,   241,   240,   245,   170,   107,
     170,   108,   312,    56,    57,    58,    59,    60,    88,   111,
     110,    48,   112,    89,   113,   114,   170,    56,    57,    58,
      59,    60,    61,    62,    63,   121,    49,    50,    64,    51,
     122,   130,   315,   316,   317,   131,    61,    62,    63,   132,
     134,   138,    64,   179,   180,   181,   182,   183,   137,   140,
     141,   153,   117,   118,   119,   120,   289,     1,     2,   142,
     155,   175,     3,     4,     5,     6,     7,     8,     9,    10,
     176,   178,   187,    11,    12,    13,   185,   196,   188,     4,
     194,    14,    15,   308,   203,   210,   307,   306,   215,   222,
      16,   223,    17,   224,   229,    18,   225,   157,   158,   159,
     160,   161,   162,   226,   321,   227,   228,   232,   163,   164,
     234,   253,   165,    48,   321,   258,   254,   255,   260,   269,
     166,   167,   265,   274,    61,    62,    63,   275,    49,    50,
      64,    51,   276,   278,   277,   281,   285,   282,   290,   292,
     295,   296,   297,   298,   300,   310,   302,   313,   314,    64,
     324,   318,   328,    79,   257,   329,   213,   221,   252,   267,
     116,   280,   330,   320
};

static const yytype_int16 yycheck[] =
{
       4,   156,   184,     4,     4,    69,   121,    71,   208,   209,
      18,    99,    11,    10,    17,   130,   168,   169,   170,   171,
     177,   109,     6,   296,     8,    17,    74,    57,    18,   144,
     268,   146,    57,    19,   272,    74,   151,     7,   153,    78,
      30,   314,    72,    73,   132,    75,    17,    72,    73,    74,
      75,     6,    55,     8,    57,   210,   211,   145,    31,   147,
      57,   125,   126,   127,    63,    57,    33,   155,    76,    77,
      78,    79,    56,   230,   312,    72,    73,    55,    75,    57,
      72,    73,   234,    75,   239,    77,    57,   175,   260,   244,
      76,    77,    78,    79,   276,    99,   100,    17,   298,   100,
     100,    72,    73,    74,    75,   277,    71,    18,    19,    74,
     225,   226,   227,   228,    74,    54,   204,   205,   206,   207,
     208,   209,    49,    50,    51,    52,    53,    66,    67,    78,
      79,    74,   287,    40,    17,    30,     0,    57,    17,    35,
      36,    68,    69,    70,   232,    18,    19,    74,    68,    69,
      70,    78,    72,    73,    74,    75,   244,     3,    74,    74,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,     8,    57,    58,    71,    74,    57,    74,
      74,    17,   270,    66,    67,    68,    69,    70,    19,    72,
      73,    74,    75,    72,    73,    33,    75,    17,    17,    74,
     204,    43,   206,   207,   204,   206,   206,   207,   296,    74,
     298,    37,   300,    49,    50,    51,    52,    53,    47,    17,
      41,    57,    38,    52,    74,    38,   314,    49,    50,    51,
      52,    53,    68,    69,    70,    74,    72,    73,    74,    75,
      74,    74,   306,   307,   308,    32,    68,    69,    70,    34,
      74,    74,    74,    23,    24,    25,    26,    27,    75,    74,
      38,    18,    91,    92,    93,    94,   270,     4,     5,    74,
      17,    43,     9,    10,    11,    12,    13,    14,    15,    16,
      19,    31,    17,    20,    21,    22,    19,    19,    74,    10,
      74,    28,    29,   297,    55,    17,   297,   297,     6,    18,
      37,    74,    39,    17,    59,    42,    18,    43,    44,    45,
      46,    47,    48,    18,   318,    18,    74,    19,    54,    55,
      18,    74,    58,    57,   328,    19,    57,    72,    74,    18,
      66,    67,    60,    18,    68,    69,    70,    18,    72,    73,
      74,    75,    18,    18,    74,    74,    19,    65,    18,    18,
      18,    38,    62,    64,    17,    61,    18,    18,    35,    74,
      18,    62,    19,    18,   221,   324,   176,   185,   213,   231,
      90,   264,   328,   314
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    14,    15,
      16,    20,    21,    22,    28,    29,    37,    39,    42,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    95,    96,   106,   110,   111,   114,   115,   116,   138,
     139,   140,     6,     8,    56,     6,     8,    17,    57,    72,
      73,    75,    77,   109,   117,   118,    49,    50,    51,    52,
      53,    68,    69,    70,    74,    78,   102,   103,   104,   105,
     119,   121,    74,     7,    31,    33,    74,    74,    40,    83,
       0,     3,   141,    74,    74,     8,    74,    74,   118,   118,
      19,    76,    77,    78,    79,    30,    71,    74,   120,    17,
      19,   122,    17,   122,    33,   122,    74,    74,    37,    43,
      41,    17,    38,    74,    38,    18,   117,   118,   118,   118,
     118,    74,    74,   109,   121,   103,   105,   121,    74,    78,
      74,    32,    34,   128,    74,   112,   109,    75,    74,    98,
      74,    38,    74,   120,    18,    19,    18,    19,   122,   122,
     122,    18,    30,    18,   120,    17,    17,    43,    44,    45,
      46,    47,    48,    54,    55,    58,    66,    67,   103,   105,
     109,   121,   135,   136,   137,    43,    19,   113,    31,    23,
      24,    25,    26,    27,   101,    19,    97,    17,    74,   120,
     109,   120,   109,   120,    74,   120,    19,   123,   109,   115,
      54,    66,    67,    55,   137,   137,   137,   137,    35,    36,
      17,    17,   109,   112,   128,     6,    55,    57,    99,    17,
      99,    98,    18,    74,    17,    18,    18,    18,    74,    59,
     131,   132,    19,   108,    18,   103,   109,   121,   109,    17,
     103,   105,   109,   121,    17,   103,   109,   121,   135,   135,
     115,   115,   113,    74,    57,    72,   100,    97,    19,    94,
      74,   120,   120,   120,   120,    60,   128,   131,   109,    18,
     137,   115,   109,   115,    18,    18,    18,    74,    18,    94,
     123,    74,    65,   130,   108,    19,   107,    17,   109,   121,
      18,   108,    18,    99,    94,    18,    38,    62,    64,   129,
      17,   115,    18,   133,   134,   136,   103,   105,   121,   135,
      61,   124,   109,    18,    35,   122,   122,   122,    62,   108,
     134,   121,   126,   127,    18,    11,    63,   125,    19,   107,
     127
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    93,    94,    94,    95,    96,    97,    97,
      98,    98,    98,    99,    99,    99,   100,   101,   101,   101,
     101,   102,   102,   102,   103,   103,   103,   103,   104,   104,
     104,   104,   104,   105,   105,   105,   106,   107,   107,   108,
     108,   109,   109,   109,   109,   110,   111,   112,   112,   113,
     113,   114,   115,   115,   116,   117,   117,   118,   118,   118,
     118,   118,   118,   118,   119,   119,   119,   119,   120,   120,
     120,   121,   121,   122,   122,   122,   122,   123,   123,   124,
     124,   125,   125,   125,   126,   127,   127,   128,   128,   129,
     129,   130,   130,   130,   130,   131,   131,   132,   133,   134,
     134,   134,   135,   135,   135,   135,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   138,   139,
     140,   141,   141
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     9,    10,     0,     3,     5,     7,     0,     3,
       6,     3,     3,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     7,     5,     7,     1,     1,
       1,     1,     1,     5,     7,     5,     9,     0,     6,     0,
       3,     1,     1,     1,     1,     4,     6,     3,     5,     0,
       3,     1,    11,     2,     2,     1,     3,     3,     3,     3,
       3,     3,     2,     1,     1,     2,     2,     2,     0,     1,
       2,     2,     4,     0,     3,     3,     3,     0,     4,     0,
       3,     0,     1,     1,     2,     1,     3,     0,     2,     0,
       2,     0,     4,     4,     4,     0,     2,     5,     1,     0,
       1,     3,     0,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     5,     5,     5,
       5,     7,     4,     6,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     1,     2,     1,     2,     7,     2,
       4,     0,     1
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
#line 240 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1841 "yacc_sql.cpp"
    break;

  case 23:
#line 270 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1850 "yacc_sql.cpp"
    break;

  case 24:
#line 276 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1858 "yacc_sql.cpp"
    break;

  case 25:
#line 281 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1866 "yacc_sql.cpp"
    break;

  case 26:
#line 287 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1874 "yacc_sql.cpp"
    break;

  case 27:
#line 293 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1882 "yacc_sql.cpp"
    break;

  case 28:
#line 299 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1890 "yacc_sql.cpp"
    break;

  case 29:
#line 305 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1900 "yacc_sql.cpp"
    break;

  case 30:
#line 312 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1908 "yacc_sql.cpp"
    break;

  case 31:
#line 318 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1918 "yacc_sql.cpp"
    break;

  case 32:
#line 327 "yacc_sql.y"
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
#line 1943 "yacc_sql.cpp"
    break;

  case 33:
#line 348 "yacc_sql.y"
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
#line 1968 "yacc_sql.cpp"
    break;

  case 34:
#line 371 "yacc_sql.y"
  {
    (yyval.attribute_list) = nullptr;
  }
#line 1976 "yacc_sql.cpp"
    break;

  case 35:
#line 375 "yacc_sql.y"
  {
    if ((yyvsp[0].attribute_list) != nullptr) {
      (yyval.attribute_list) = (yyvsp[0].attribute_list);
    } else {
      (yyval.attribute_list) = new std::vector<std::string>;
    }

    (yyval.attribute_list)->emplace_back((yyvsp[-1].string));
    free((yyvsp[-1].string));
  }
#line 1991 "yacc_sql.cpp"
    break;

  case 36:
#line 389 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2003 "yacc_sql.cpp"
    break;

  case 37:
#line 399 "yacc_sql.y"
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
#line 2023 "yacc_sql.cpp"
    break;

  case 38:
#line 417 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2031 "yacc_sql.cpp"
    break;

  case 39:
#line 421 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2045 "yacc_sql.cpp"
    break;

  case 40:
#line 434 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].is_null);
      free((yyvsp[-5].string));
    }
#line 2058 "yacc_sql.cpp"
    break;

  case 41:
#line 443 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = TEXTS;
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 8;
      (yyval.attr_info)->nullable = (yyvsp[0].is_null);
      free((yyvsp[-2].string));
    }
#line 2071 "yacc_sql.cpp"
    break;

  case 42:
#line 452 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].is_null);
      free((yyvsp[-2].string));
    }
#line 2084 "yacc_sql.cpp"
    break;

  case 43:
#line 463 "yacc_sql.y"
  {
    (yyval.is_null) = true;
  }
#line 2092 "yacc_sql.cpp"
    break;

  case 44:
#line 467 "yacc_sql.y"
  {
    (yyval.is_null) = false;
  }
#line 2100 "yacc_sql.cpp"
    break;

  case 45:
#line 471 "yacc_sql.y"
  {
    (yyval.is_null) = true;
  }
#line 2108 "yacc_sql.cpp"
    break;

  case 46:
#line 477 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2114 "yacc_sql.cpp"
    break;

  case 47:
#line 482 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2120 "yacc_sql.cpp"
    break;

  case 48:
#line 483 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2126 "yacc_sql.cpp"
    break;

  case 49:
#line 484 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2132 "yacc_sql.cpp"
    break;

  case 50:
#line 485 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2138 "yacc_sql.cpp"
    break;

  case 51:
#line 490 "yacc_sql.y"
           { (yyval.func_t)=LENGTH_T; }
#line 2144 "yacc_sql.cpp"
    break;

  case 52:
#line 491 "yacc_sql.y"
                  { (yyval.func_t)=DATE_FORMAT_T; }
#line 2150 "yacc_sql.cpp"
    break;

  case 53:
#line 492 "yacc_sql.y"
            { (yyval.func_t)=ROUND_T; }
#line 2156 "yacc_sql.cpp"
    break;

  case 54:
#line 497 "yacc_sql.y"
    {
      (yyval.normal_func) = new RelAttrSqlNode;
      (yyval.normal_func)->is_aggr = false;

      (yyval.normal_func)->is_func = true;
      (yyval.normal_func)->func_type = (yyvsp[-4].func_t);
      (yyval.normal_func)->first_func_arg.is_valid = true;
      (yyval.normal_func)->first_func_arg.is_attr = true;
      (yyval.normal_func)->first_func_arg.relation_name = (yyvsp[-2].rel_attr)->relation_name;
      (yyval.normal_func)->first_func_arg.attribute_name = (yyvsp[-2].rel_attr)->attribute_name;

      (yyval.normal_func)->second_func_arg.is_valid = false;

      (yyval.normal_func)->alias = (yyvsp[0].string);

      free((yyvsp[-2].rel_attr));
    }
#line 2178 "yacc_sql.cpp"
    break;

  case 55:
#line 516 "yacc_sql.y"
    {
      (yyval.normal_func) = new RelAttrSqlNode;
      (yyval.normal_func)->is_aggr = false;

      (yyval.normal_func)->is_func = true;
      (yyval.normal_func)->func_type = (yyvsp[-6].func_t);
      (yyval.normal_func)->first_func_arg.is_valid = true;
      (yyval.normal_func)->first_func_arg.is_attr = true;
      (yyval.normal_func)->first_func_arg.relation_name = (yyvsp[-4].rel_attr)->relation_name;
      (yyval.normal_func)->first_func_arg.attribute_name = (yyvsp[-4].rel_attr)->attribute_name;

      (yyval.normal_func)->second_func_arg.is_valid = true;
      (yyval.normal_func)->second_func_arg.is_attr = false;
      (yyval.normal_func)->second_func_arg.value = *(yyvsp[-2].value);
      (yyval.normal_func)->alias = (yyvsp[0].string);

      free((yyvsp[-4].rel_attr));
      free((yyvsp[-2].value));

    }
#line 2203 "yacc_sql.cpp"
    break;

  case 56:
#line 538 "yacc_sql.y"
    {
      (yyval.normal_func) = new RelAttrSqlNode;
      (yyval.normal_func)->is_aggr = false;

      (yyval.normal_func)->is_func = true;
      (yyval.normal_func)->func_type = (yyvsp[-4].func_t);
      (yyval.normal_func)->first_func_arg.is_valid = true;
      (yyval.normal_func)->first_func_arg.is_attr = false;
      (yyval.normal_func)->first_func_arg.value = *(yyvsp[-2].value);

      (yyval.normal_func)->second_func_arg.is_valid = false;

      (yyval.normal_func)->alias = (yyvsp[0].string);

      free((yyvsp[-2].value));

    }
#line 2225 "yacc_sql.cpp"
    break;

  case 57:
#line 557 "yacc_sql.y"
    {
      (yyval.normal_func) = new RelAttrSqlNode;
      (yyval.normal_func)->is_aggr = false;

      (yyval.normal_func)->is_func = true;
      (yyval.normal_func)->func_type = (yyvsp[-6].func_t);
      (yyval.normal_func)->first_func_arg.is_valid = true;
      (yyval.normal_func)->first_func_arg.is_attr = false;
      (yyval.normal_func)->first_func_arg.value = *(yyvsp[-4].value);

      (yyval.normal_func)->second_func_arg.is_valid = true;
      (yyval.normal_func)->second_func_arg.is_attr = false;
      (yyval.normal_func)->second_func_arg.value = *(yyvsp[-2].value);
      (yyval.normal_func)->alias = (yyvsp[0].string);

      free((yyvsp[-4].value));
      free((yyvsp[-2].value));

    }
#line 2249 "yacc_sql.cpp"
    break;

  case 58:
#line 579 "yacc_sql.y"
        { (yyval.aggr_t)=MAX_T; }
#line 2255 "yacc_sql.cpp"
    break;

  case 59:
#line 580 "yacc_sql.y"
          { (yyval.aggr_t)=MIN_T; }
#line 2261 "yacc_sql.cpp"
    break;

  case 60:
#line 581 "yacc_sql.y"
          { (yyval.aggr_t)=AVG_T; }
#line 2267 "yacc_sql.cpp"
    break;

  case 61:
#line 582 "yacc_sql.y"
          { (yyval.aggr_t)=SUM_T; }
#line 2273 "yacc_sql.cpp"
    break;

  case 62:
#line 583 "yacc_sql.y"
            { (yyval.aggr_t)=COUNT_T; }
#line 2279 "yacc_sql.cpp"
    break;

  case 63:
#line 588 "yacc_sql.y"
    {
      (yyval.aggr_func) = new RelAttrSqlNode;
      (yyval.aggr_func)->is_aggr = true;
      (yyval.aggr_func)->aggr_type = (yyvsp[-4].aggr_t);
      (yyval.aggr_func)->attribute_name = (yyvsp[-2].string);
      (yyval.aggr_func)->alias = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2293 "yacc_sql.cpp"
    break;

  case 64:
#line 597 "yacc_sql.y"
                                                       {
      (yyval.aggr_func) = new RelAttrSqlNode;
      (yyval.aggr_func)->is_aggr = true;
      (yyval.aggr_func)->aggr_type = (yyvsp[-6].aggr_t);
      (yyval.aggr_func)->relation_name  = (yyvsp[-4].string);
      (yyval.aggr_func)->attribute_name = (yyvsp[-2].string);
      (yyval.aggr_func)->alias = (yyvsp[0].string);
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
		}
#line 2309 "yacc_sql.cpp"
    break;

  case 65:
#line 608 "yacc_sql.y"
                                                             {
      (yyval.aggr_func) = new RelAttrSqlNode;
      (yyval.aggr_func)->is_aggr = true;
      (yyval.aggr_func)->aggr_type = (yyvsp[-4].aggr_t);
      (yyval.aggr_func)->attribute_name = "*";
      (yyval.aggr_func)->alias = (yyvsp[0].string);
      free((yyvsp[0].string));
		}
#line 2322 "yacc_sql.cpp"
    break;

  case 66:
#line 620 "yacc_sql.y"
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
#line 2348 "yacc_sql.cpp"
    break;

  case 67:
#line 644 "yacc_sql.y"
  {
    (yyval.insert_list) = nullptr;
  }
#line 2356 "yacc_sql.cpp"
    break;

  case 68:
#line 648 "yacc_sql.y"
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
#line 2377 "yacc_sql.cpp"
    break;

  case 69:
#line 668 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2385 "yacc_sql.cpp"
    break;

  case 70:
#line 671 "yacc_sql.y"
                              {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2399 "yacc_sql.cpp"
    break;

  case 71:
#line 683 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2408 "yacc_sql.cpp"
    break;

  case 72:
#line 687 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2417 "yacc_sql.cpp"
    break;

  case 73:
#line 691 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2427 "yacc_sql.cpp"
    break;

  case 74:
#line 696 "yacc_sql.y"
            {
      (yyval.value) = new Value(); // UNDEFINED TYPE HERE
      (yyval.value)->set_null();
    }
#line 2436 "yacc_sql.cpp"
    break;

  case 75:
#line 704 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2450 "yacc_sql.cpp"
    break;

  case 76:
#line 716 "yacc_sql.y"
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
#line 2473 "yacc_sql.cpp"
    break;

  case 77:
#line 737 "yacc_sql.y"
  {
    (yyval.update_pair) = new UpdateListSqlNode{(yyvsp[-2].string), *(yyvsp[0].value), SelectSqlNode{}, false};
    free((yyvsp[0].value));
  }
#line 2482 "yacc_sql.cpp"
    break;

  case 78:
#line 742 "yacc_sql.y"
  {
    (yyval.update_pair) = new UpdateListSqlNode{(yyvsp[-4].string), Value{}, *(yyvsp[-1].select_body), true};
    free((yyvsp[-1].select_body));
  }
#line 2491 "yacc_sql.cpp"
    break;

  case 79:
#line 748 "yacc_sql.y"
    {
      (yyval.update_list) = nullptr;
    }
#line 2499 "yacc_sql.cpp"
    break;

  case 80:
#line 752 "yacc_sql.y"
    {
      if ((yyvsp[0].update_list) != nullptr) {
        (yyval.update_list) = (yyvsp[0].update_list);
      } else {
        (yyval.update_list) = new std::vector<UpdateListSqlNode>;
      }

      (yyval.update_list)->emplace_back(*(yyvsp[-1].update_pair));
      free((yyvsp[-1].update_pair));
    }
#line 2514 "yacc_sql.cpp"
    break;

  case 81:
#line 767 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      (yyval.sql_node)->selection = *(yyvsp[0].select_body);
      delete (yyvsp[0].select_body);
    }
#line 2524 "yacc_sql.cpp"
    break;

  case 82:
#line 777 "yacc_sql.y"
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
        delete(yyvsp[-3].condition_list);
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
#line 2577 "yacc_sql.cpp"
    break;

  case 83:
#line 827 "yacc_sql.y"
    {
      (yyval.select_body) = new SelectSqlNode;
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.select_body)->attributes.swap(*(yyvsp[0].rel_attr_list));
        delete (yyvsp[0].rel_attr_list);
      }
    }
#line 2589 "yacc_sql.cpp"
    break;

  case 84:
#line 838 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2600 "yacc_sql.cpp"
    break;

  case 85:
#line 848 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2609 "yacc_sql.cpp"
    break;

  case 86:
#line 853 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2622 "yacc_sql.cpp"
    break;

  case 87:
#line 864 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2630 "yacc_sql.cpp"
    break;

  case 88:
#line 867 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2638 "yacc_sql.cpp"
    break;

  case 89:
#line 870 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2646 "yacc_sql.cpp"
    break;

  case 90:
#line 873 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2654 "yacc_sql.cpp"
    break;

  case 91:
#line 876 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2663 "yacc_sql.cpp"
    break;

  case 92:
#line 880 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2671 "yacc_sql.cpp"
    break;

  case 93:
#line 883 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2681 "yacc_sql.cpp"
    break;

  case 94:
#line 891 "yacc_sql.y"
        {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.is_aggr = false;
      attr.is_func = false;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 2695 "yacc_sql.cpp"
    break;

  case 95:
#line 900 "yacc_sql.y"
                         {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2709 "yacc_sql.cpp"
    break;

  case 96:
#line 909 "yacc_sql.y"
                          {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].aggr_func));
      delete (yyvsp[-1].aggr_func);
      }
#line 2723 "yacc_sql.cpp"
    break;

  case 97:
#line 918 "yacc_sql.y"
                            {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].normal_func));
      delete (yyvsp[-1].normal_func);
    }
#line 2737 "yacc_sql.cpp"
    break;

  case 98:
#line 930 "yacc_sql.y"
    {
      (yyval.string) = strdup("");
    }
#line 2745 "yacc_sql.cpp"
    break;

  case 99:
#line 934 "yacc_sql.y"
    {
      (yyval.string) = strdup((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2754 "yacc_sql.cpp"
    break;

  case 100:
#line 938 "yacc_sql.y"
            {
      (yyval.string) = strdup((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2763 "yacc_sql.cpp"
    break;

  case 101:
#line 946 "yacc_sql.y"
                      {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->is_aggr = false;
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 2776 "yacc_sql.cpp"
    break;

  case 102:
#line 954 "yacc_sql.y"
                               {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->is_aggr = false;
      (yyval.rel_attr)->relation_name  = (yyvsp[-3].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 2791 "yacc_sql.cpp"
    break;

  case 103:
#line 968 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2799 "yacc_sql.cpp"
    break;

  case 104:
#line 971 "yacc_sql.y"
                               {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }

      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2814 "yacc_sql.cpp"
    break;

  case 105:
#line 981 "yacc_sql.y"
                                {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }

      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].aggr_func));
      delete (yyvsp[-1].aggr_func);
    }
#line 2829 "yacc_sql.cpp"
    break;

  case 106:
#line 991 "yacc_sql.y"
                                  {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }

      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].normal_func));
      delete (yyvsp[-1].normal_func);
    }
#line 2844 "yacc_sql.cpp"
    break;

  case 107:
#line 1005 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2852 "yacc_sql.cpp"
    break;

  case 108:
#line 1008 "yacc_sql.y"
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
#line 2868 "yacc_sql.cpp"
    break;

  case 109:
#line 1022 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2876 "yacc_sql.cpp"
    break;

  case 110:
#line 1026 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 2884 "yacc_sql.cpp"
    break;

  case 111:
#line 1032 "yacc_sql.y"
    {
      (yyval.order_t) = ASC_T;
    }
#line 2892 "yacc_sql.cpp"
    break;

  case 112:
#line 1037 "yacc_sql.y"
    {
      (yyval.order_t) = ASC_T;
    }
#line 2900 "yacc_sql.cpp"
    break;

  case 113:
#line 1042 "yacc_sql.y"
    {
      (yyval.order_t) = DESC_T;
    }
#line 2908 "yacc_sql.cpp"
    break;

  case 114:
#line 1049 "yacc_sql.y"
    {
        (yyval.order_by_attr) = new OrderBySqlNode;
        (yyval.order_by_attr)->attr = *(yyvsp[-1].rel_attr);
        (yyval.order_by_attr)->order_type = (yyvsp[0].order_t);
        delete (yyvsp[-1].rel_attr);
    }
#line 2919 "yacc_sql.cpp"
    break;

  case 115:
#line 1059 "yacc_sql.y"
    {
      (yyval.order_by_list) = new std::vector<OrderBySqlNode>;
      (yyval.order_by_list)->emplace_back(*(yyvsp[0].order_by_attr));
      delete (yyvsp[0].order_by_attr);
    }
#line 2929 "yacc_sql.cpp"
    break;

  case 116:
#line 1064 "yacc_sql.y"
                                        {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
      (yyval.order_by_list)->emplace_back(*(yyvsp[-2].order_by_attr));
      delete (yyvsp[-2].order_by_attr);
    }
#line 2939 "yacc_sql.cpp"
    break;

  case 117:
#line 1073 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2947 "yacc_sql.cpp"
    break;

  case 118:
#line 1076 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2955 "yacc_sql.cpp"
    break;

  case 119:
#line 1084 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2963 "yacc_sql.cpp"
    break;

  case 120:
#line 1087 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2971 "yacc_sql.cpp"
    break;

  case 121:
#line 1093 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2979 "yacc_sql.cpp"
    break;

  case 122:
#line 1096 "yacc_sql.y"
                                  {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2993 "yacc_sql.cpp"
    break;

  case 123:
#line 1105 "yacc_sql.y"
                                   {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].aggr_func));
      delete (yyvsp[-1].aggr_func);
      }
#line 3007 "yacc_sql.cpp"
    break;

  case 124:
#line 1114 "yacc_sql.y"
                                     {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].normal_func));
      delete (yyvsp[-1].normal_func);
      }
#line 3021 "yacc_sql.cpp"
    break;

  case 125:
#line 1126 "yacc_sql.y"
    {
      (yyval.inner_join_list) = nullptr;
    }
#line 3029 "yacc_sql.cpp"
    break;

  case 126:
#line 1129 "yacc_sql.y"
                                 {
      if ((yyvsp[0].inner_join_list) != nullptr) {
        (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
      } else {
        (yyval.inner_join_list) = new std::vector<InnerJoinSqlNode>;
      }
      (yyval.inner_join_list)->emplace_back(*(yyvsp[-1].inner_join));
      delete (yyvsp[-1].inner_join);
    }
#line 3043 "yacc_sql.cpp"
    break;

  case 127:
#line 1141 "yacc_sql.y"
                                         {
      (yyval.inner_join) = new InnerJoinSqlNode;
      (yyval.inner_join)->relation_name = (yyvsp[-2].string);
      (yyval.inner_join)->join_conditions.swap(*(yyvsp[0].condition_list));
      delete (yyvsp[0].condition_list);
    }
#line 3054 "yacc_sql.cpp"
    break;

  case 128:
#line 1151 "yacc_sql.y"
    {
      (yyval.condition) = (yyvsp[0].condition);
    }
#line 3062 "yacc_sql.cpp"
    break;

  case 129:
#line 1157 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3070 "yacc_sql.cpp"
    break;

  case 130:
#line 1161 "yacc_sql.y"
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3080 "yacc_sql.cpp"
    break;

  case 131:
#line 1166 "yacc_sql.y"
                                             {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3090 "yacc_sql.cpp"
    break;

  case 132:
#line 1175 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3098 "yacc_sql.cpp"
    break;

  case 133:
#line 1179 "yacc_sql.y"
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3108 "yacc_sql.cpp"
    break;

  case 134:
#line 1184 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3118 "yacc_sql.cpp"
    break;

  case 135:
#line 1189 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->is_and = false;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);     
    }
#line 3129 "yacc_sql.cpp"
    break;

  case 136:
#line 1199 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 3145 "yacc_sql.cpp"
    break;

  case 137:
#line 1211 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
    }
#line 3161 "yacc_sql.cpp"
    break;

  case 138:
#line 1223 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
    }
#line 3177 "yacc_sql.cpp"
    break;

  case 139:
#line 1235 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].rel_attr);
    }
#line 3193 "yacc_sql.cpp"
    break;

  case 140:
#line 1247 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].normal_func);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].normal_func);
      delete (yyvsp[0].rel_attr);
    }
#line 3209 "yacc_sql.cpp"
    break;

  case 141:
#line 1259 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].normal_func);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].normal_func);
    }
#line 3225 "yacc_sql.cpp"
    break;

  case 142:
#line 1271 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].normal_func);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].normal_func);
    }
#line 3241 "yacc_sql.cpp"
    break;

  case 143:
#line 1283 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].normal_func);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].normal_func);
      delete (yyvsp[0].value);
    }
#line 3257 "yacc_sql.cpp"
    break;

  case 144:
#line 1295 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].normal_func);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].normal_func);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].normal_func);
      delete (yyvsp[0].normal_func);
    }
#line 3273 "yacc_sql.cpp"
    break;

  case 145:
#line 1307 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].aggr_func);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].aggr_func);
    }
#line 3289 "yacc_sql.cpp"
    break;

  case 146:
#line 1319 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].aggr_func);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].aggr_func);
      delete (yyvsp[0].value);
    }
#line 3305 "yacc_sql.cpp"
    break;

  case 147:
#line 1331 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-4].value);
      (yyval.condition)->right_is_select = 1;
      (yyval.condition)->right_select = (yyvsp[-1].select_body);
      (yyval.condition)->comp = (yyvsp[-3].comp);
      delete (yyvsp[-4].value);
    }
#line 3319 "yacc_sql.cpp"
    break;

  case 148:
#line 1341 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->right_is_select = 1;
      (yyval.condition)->right_select = (yyvsp[-1].select_body);
      (yyval.condition)->comp = (yyvsp[-3].comp);
      delete (yyvsp[-4].rel_attr);
    }
#line 3333 "yacc_sql.cpp"
    break;

  case 149:
#line 1351 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_select = 1;
      (yyval.condition)->left_select = (yyvsp[-3].select_body);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      delete (yyvsp[0].rel_attr);
    }
#line 3347 "yacc_sql.cpp"
    break;

  case 150:
#line 1361 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_select = 1;
      (yyval.condition)->left_select = (yyvsp[-3].select_body);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      delete (yyvsp[0].value);
    }
#line 3361 "yacc_sql.cpp"
    break;

  case 151:
#line 1371 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_select = 1;
      (yyval.condition)->left_select = (yyvsp[-5].select_body);
      (yyval.condition)->right_is_select = 1;
      (yyval.condition)->right_select = (yyvsp[-1].select_body);
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 3374 "yacc_sql.cpp"
    break;

  case 152:
#line 1380 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_select = 0;
      (yyval.condition)->right_is_select = 1;
      (yyval.condition)->right_select = (yyvsp[-1].select_body);
      (yyval.condition)->comp = (yyvsp[-3].comp);
      (yyval.condition)->unary_op = 1;
    }
#line 3387 "yacc_sql.cpp"
    break;

  case 153:
#line 1389 "yacc_sql.y"
    {
      // HERE
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-5].rel_attr);
      (yyval.condition)->right_is_select = 1;
      (yyval.condition)->comp = (yyvsp[-4].comp);
      (yyval.condition)->values.swap(*(yyvsp[-1].value_list));
      (yyval.condition)->values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.condition)->values.begin(), (yyval.condition)->values.end());
      delete (yyvsp[-1].value_list);
    }
#line 3404 "yacc_sql.cpp"
    break;

  case 154:
#line 1404 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3410 "yacc_sql.cpp"
    break;

  case 155:
#line 1405 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3416 "yacc_sql.cpp"
    break;

  case 156:
#line 1406 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3422 "yacc_sql.cpp"
    break;

  case 157:
#line 1407 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3428 "yacc_sql.cpp"
    break;

  case 158:
#line 1408 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3434 "yacc_sql.cpp"
    break;

  case 159:
#line 1409 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3440 "yacc_sql.cpp"
    break;

  case 160:
#line 1410 "yacc_sql.y"
           { (yyval.comp) = STR_LIKE; }
#line 3446 "yacc_sql.cpp"
    break;

  case 161:
#line 1411 "yacc_sql.y"
               { (yyval.comp) = STR_NOT_LIKE; }
#line 3452 "yacc_sql.cpp"
    break;

  case 162:
#line 1412 "yacc_sql.y"
           { (yyval.comp) = IS; }
#line 3458 "yacc_sql.cpp"
    break;

  case 163:
#line 1413 "yacc_sql.y"
               { (yyval.comp) = IS_NOT; }
#line 3464 "yacc_sql.cpp"
    break;

  case 164:
#line 1414 "yacc_sql.y"
           { (yyval.comp) = IN; }
#line 3470 "yacc_sql.cpp"
    break;

  case 165:
#line 1415 "yacc_sql.y"
               { (yyval.comp) = IN_NOT; }
#line 3476 "yacc_sql.cpp"
    break;

  case 166:
#line 1416 "yacc_sql.y"
              { (yyval.comp) = EXIST; }
#line 3482 "yacc_sql.cpp"
    break;

  case 167:
#line 1417 "yacc_sql.y"
                  { (yyval.comp) = EXIST_NOT; }
#line 3488 "yacc_sql.cpp"
    break;

  case 168:
#line 1422 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);

      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3502 "yacc_sql.cpp"
    break;

  case 169:
#line 1435 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3511 "yacc_sql.cpp"
    break;

  case 170:
#line 1443 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3523 "yacc_sql.cpp"
    break;


#line 3527 "yacc_sql.cpp"

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
#line 1455 "yacc_sql.y"

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
