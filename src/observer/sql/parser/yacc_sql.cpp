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
#define YYFINAL  84
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   406

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  182
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  346

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
       0,   247,   247,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   278,   284,   289,   295,   301,   307,   313,
     320,   326,   334,   355,   379,   382,   396,   406,   425,   428,
     441,   450,   459,   471,   474,   478,   485,   490,   491,   492,
     493,   498,   499,   500,   504,   512,   531,   553,   572,   595,
     596,   597,   598,   599,   603,   613,   624,   635,   658,   683,
     686,   703,   724,   727,   736,   747,   751,   757,   761,   765,
     770,   777,   790,   811,   816,   823,   826,   841,   851,   901,
     911,   924,   934,   939,   951,   955,   959,   963,   967,   972,
     976,   981,   990,  1008,  1017,  1026,  1038,  1041,  1046,  1053,
    1063,  1073,  1081,  1091,  1100,  1107,  1117,  1120,  1126,  1129,
    1139,  1148,  1162,  1165,  1179,  1182,  1189,  1193,  1198,  1205,
    1215,  1221,  1230,  1233,  1241,  1244,  1250,  1253,  1262,  1271,
    1283,  1286,  1298,  1307,  1314,  1317,  1323,  1332,  1335,  1341,
    1346,  1356,  1363,  1375,  1387,  1399,  1411,  1423,  1436,  1447,
    1460,  1470,  1479,  1488,  1504,  1505,  1506,  1507,  1508,  1509,
    1510,  1511,  1512,  1513,  1514,  1515,  1516,  1517,  1521,  1534,
    1542,  1552,  1553
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
  "type", "func_type", "expr_attr", "normal_func", "aggr_type",
  "aggr_func", "insert_stmt", "insert_list", "value_list", "minus_value",
  "value", "delete_stmt", "update_stmt", "update_pair", "update_list",
  "select_stmt", "select_body", "calc_stmt", "expression_list",
  "expression", "select_attr", "alias_optional", "rel_attr_with_alias",
  "rel_attr_no_alias", "rel_attr", "attr_list", "rel_list", "order_by",
  "order_type", "order_by_attr", "order_by_list", "where", "having",
  "group_by", "inner_join_list", "inner_join", "join_condition",
  "join_condition_list", "condition_list", "cond_value_list", "condition",
  "comp_op", "load_data_stmt", "explain_stmt", "set_variable_stmt",
  "opt_semicolon", YY_NULLPTR
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

#define YYPACT_NINF (-281)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-106)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     326,    16,    31,   205,    78,   -30,    48,  -281,    28,    50,
      41,  -281,  -281,  -281,  -281,  -281,    52,    65,   326,   133,
     138,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,  -281,    69,    71,   146,    93,    96,   205,  -281,  -281,
    -281,    95,  -281,   205,  -281,  -281,    14,  -281,  -281,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,  -281,   147,
     152,   152,   155,   152,   117,   140,  -281,  -281,   118,   123,
     173,   175,   189,  -281,  -281,  -281,  -281,   214,   195,   160,
    -281,   202,    10,   -21,   168,  -281,  -281,   205,   205,   205,
     205,   205,   -23,   186,   211,   212,     4,  -281,   172,  -281,
    -281,   177,   220,   213,   179,   224,   196,   199,   200,   232,
     217,  -281,   -44,  -281,  -281,  -281,    19,    19,  -281,  -281,
     119,   139,   152,   152,   152,   102,   258,  -281,     6,   269,
     132,  -281,   250,   275,  -281,   264,   287,   279,   283,   227,
    -281,   228,  -281,     6,   224,     6,   224,  -281,  -281,  -281,
       6,   230,     6,   286,   -32,    44,  -281,  -281,  -281,  -281,
    -281,  -281,  -281,   -19,   260,  -281,  -281,   327,   327,   327,
    -281,   124,   299,    67,   179,   213,   311,  -281,  -281,  -281,
    -281,    79,     3,   199,   300,   245,   303,  -281,  -281,   304,
    -281,   305,  -281,   310,  -281,   247,   273,    90,   314,   314,
     316,  -281,  -281,  -281,  -281,   215,   151,   205,   132,   132,
     333,   333,  -281,   275,  -281,   270,   288,  -281,  -281,   277,
    -281,   279,  -281,   331,   278,     6,     6,     6,     6,   291,
     213,   273,  -281,  -281,   -32,   335,   338,   327,    44,  -281,
    -281,  -281,  -281,  -281,  -281,  -281,  -281,   339,   340,  -281,
    -281,  -281,  -281,   341,  -281,   290,   342,   331,  -281,  -281,
    -281,   286,   292,   296,  -281,   314,   314,   343,   343,   252,
     348,   351,   358,  -281,  -281,    79,   331,  -281,   359,  -281,
     345,   317,   320,  -281,  -281,   361,  -281,  -281,    44,  -281,
     224,  -281,  -281,  -281,  -281,  -281,   132,   186,   132,   319,
     -32,   368,   348,  -281,   352,  -281,  -281,   152,   152,   152,
    -281,   328,  -281,   314,   314,  -281,   132,  -281,  -281,  -281,
     315,   370,   373,  -281,     7,   376,  -281,   343,   343,  -281,
    -281,  -281,   315,  -281,  -281,  -281
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     181,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,    87,     3,    18,
      19,    20,     0,     0,     0,     0,     0,     0,    80,    77,
      78,   115,    79,     0,   101,    91,    92,   117,   116,   100,
      59,    60,    61,    62,    63,    51,    52,    53,   102,     0,
     118,   118,     0,   118,   106,     0,    31,    30,     0,     0,
       0,     0,     0,   179,     1,   182,     2,     0,     0,     0,
      29,     0,     0,     0,     0,   111,    99,     0,     0,     0,
       0,     0,     0,     0,    90,    89,     0,   103,     0,   107,
      54,     0,     0,   132,     0,     0,     0,     0,     0,     0,
       0,    98,   113,   114,   112,    93,    94,    95,    96,    97,
       0,     0,   118,   118,   118,     0,     0,   108,   106,     0,
     147,    81,     0,    85,   180,     0,     0,    38,     0,     0,
      36,     0,   109,   106,     0,   106,     0,   121,   120,   119,
     106,     0,   106,   122,     0,     0,   164,   165,   166,   167,
     168,   169,   170,     0,   172,   174,   176,     0,     0,     0,
     133,   148,     0,     0,     0,   132,     0,    47,    48,    49,
      50,    43,    43,     0,     0,     0,     0,   110,    57,     0,
      55,     0,    64,     0,    66,     0,   140,     0,    72,    72,
       0,   171,   175,   177,   173,     0,     0,     0,   147,   147,
       0,     0,    83,    85,    82,     0,     0,    45,    41,     0,
      42,    38,    37,    34,     0,   106,   106,   106,   106,     0,
     132,   140,    75,    76,     0,     0,     0,     0,     0,   158,
     154,   156,   153,   155,   157,   149,   150,     0,     0,    86,
     178,    44,    46,     0,    39,     0,     0,    34,    58,    56,
      65,   122,     0,   136,   141,    72,    72,    69,    69,     0,
     101,     0,     0,   162,    84,    43,    34,    32,     0,   123,
       0,     0,   134,    73,    74,     0,    68,    67,     0,   160,
       0,   159,   163,    40,    35,    33,   144,     0,   147,   124,
       0,     0,   151,   152,   145,   142,   143,   118,   118,   118,
     135,     0,    88,    72,    72,   161,   144,   137,   139,   138,
       0,     0,     0,   146,   126,   130,   125,    69,    69,   128,
     127,   129,     0,    70,    71,   131
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -281,  -281,   374,  -281,  -281,  -281,  -281,  -281,  -281,  -281,
    -281,  -281,  -281,  -244,  -281,  -281,   165,   204,  -182,  -281,
    -281,  -281,    -4,    -1,  -281,     1,  -281,  -269,  -201,  -231,
     -83,  -281,  -281,   216,   176,  -281,  -154,  -281,   301,     9,
    -281,  -124,  -281,  -281,  -101,   -69,   130,  -281,  -281,  -281,
      60,  -164,  -281,  -281,   162,  -281,  -281,    80,  -212,   104,
    -280,  -162,  -281,  -281,  -281,  -281
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   266,    31,    32,   194,   147,   228,   263,
     192,    69,   177,   178,    72,   179,    33,   296,   245,   208,
      54,    34,    35,   143,   185,    36,    37,    38,    55,    74,
      75,   110,    57,    58,    59,   104,   206,   322,   341,   335,
     336,   141,   309,   292,   240,   241,   314,   315,   180,   282,
     181,   182,    39,    40,    41,    86
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,   131,   105,    71,   107,    73,   255,   256,   246,   297,
     230,   210,    56,   275,   163,   215,   216,   217,   339,   130,
     229,   224,    42,   288,    43,    48,   316,   151,   121,   198,
     152,   200,   144,    97,    48,   211,   202,    45,   204,    46,
      49,    50,   304,    52,    76,   207,   316,   212,   213,    49,
      50,    51,    52,   122,     4,    77,    92,   123,   226,    78,
     227,    47,    96,   157,   158,   159,   257,   258,   343,   344,
     340,   199,    44,   201,   293,   294,   273,   108,   135,   323,
     109,   209,   136,    79,   221,   279,    98,    99,   100,   101,
      98,    99,   100,   101,   281,    47,   320,   100,   101,   132,
     222,    48,   133,   303,   134,    82,    56,   126,   127,   128,
     129,   268,   269,   270,   271,    80,    49,    50,    51,    52,
     160,    53,   331,   332,    48,    93,    81,    60,    61,    62,
      63,    64,   161,    84,   226,    48,   227,   153,   154,    49,
      50,    85,    52,    87,   311,    88,    65,    66,    67,   165,
      49,    50,    51,    52,    89,    53,    68,   155,   156,   218,
     219,   276,   242,   243,   102,   280,    94,    90,    47,    95,
      91,   103,   106,   111,    92,   166,   167,   168,   169,   170,
     171,    60,    61,    62,    63,    64,   172,   173,   108,    48,
     174,   109,   112,    98,    99,   100,   101,   113,   175,   176,
      65,    66,    67,    47,    49,    50,    51,    52,    48,    53,
     114,   249,   252,   254,   250,   253,   251,   312,   115,    65,
      66,    67,    47,    49,    50,    51,    52,   324,    53,   334,
     116,   117,   248,   118,   119,    60,    61,    62,    63,    64,
     120,   334,   124,    48,  -105,  -104,   137,   140,   327,   328,
     329,   138,   139,   142,    65,    66,    67,    92,    49,    50,
      51,    52,    48,    53,    60,    61,    62,    63,    64,   298,
     149,   145,    48,   146,   148,   299,   162,    49,    50,    51,
      52,    48,    53,    65,    66,    67,   164,    49,    50,    51,
      52,   150,    53,   183,   184,   186,    49,    50,   193,    52,
     195,   196,   197,   317,   203,   205,   318,    92,   319,    48,
     187,   188,   189,   190,   191,   214,   220,   225,   232,   233,
     234,   238,   235,   236,    49,    50,    51,    52,   237,    53,
       1,     2,   239,   244,   247,     3,     4,     5,     6,     7,
       8,     9,    10,     4,   260,   261,    11,    12,    13,   262,
     265,   272,   267,   277,    14,    15,   278,   283,   284,   285,
     287,   291,   295,    16,   286,    17,   290,   300,    18,   301,
     166,   167,   168,   169,   170,   171,   302,   305,   310,   307,
     321,   172,   173,   306,   308,   174,   325,   326,   337,    51,
     330,   338,    83,   175,   176,   342,   264,   231,   125,   259,
     223,   289,   345,   274,   313,     0,   333
};

static const yytype_int16 yycheck[] =
{
       4,   102,    71,     4,    73,     4,   218,   219,   209,   278,
     192,   165,     3,   244,   138,   177,   178,   179,    11,   102,
      17,   185,     6,   267,     8,    57,   306,    71,    18,   153,
      74,   155,   115,    19,    57,    54,   160,     6,   162,     8,
      72,    73,   286,    75,    74,    77,   326,    66,    67,    72,
      73,    74,    75,    74,    10,     7,    47,    78,    55,    31,
      57,    17,    53,   132,   133,   134,   220,   221,   337,   338,
      63,   154,    56,   156,   275,   276,   240,    71,    74,   310,
      74,   164,    78,    33,    17,   247,    76,    77,    78,    79,
      76,    77,    78,    79,   248,    17,   308,    78,    79,   103,
     183,    57,   103,   285,   103,    40,    97,    98,    99,   100,
     101,   235,   236,   237,   238,    74,    72,    73,    74,    75,
      18,    77,   323,   324,    57,    30,    74,    49,    50,    51,
      52,    53,    30,     0,    55,    57,    57,    18,    19,    72,
      73,     3,    75,    74,   298,    74,    68,    69,    70,    17,
      72,    73,    74,    75,     8,    77,    78,    18,    19,    35,
      36,   244,    72,    73,    17,   248,    71,    74,    17,    74,
      74,    19,    17,    33,   165,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    71,    57,
      58,    74,    74,    76,    77,    78,    79,    74,    66,    67,
      68,    69,    70,    17,    72,    73,    74,    75,    57,    77,
      37,   215,   216,   217,   215,   216,   215,   300,    43,    68,
      69,    70,    17,    72,    73,    74,    75,   310,    77,   330,
      41,    17,    17,    38,    74,    49,    50,    51,    52,    53,
      38,   342,    74,    57,    33,    33,    74,    34,   317,   318,
     319,    74,    32,    74,    68,    69,    70,   248,    72,    73,
      74,    75,    57,    77,    49,    50,    51,    52,    53,    17,
      38,    75,    57,    74,    74,   279,    18,    72,    73,    74,
      75,    57,    77,    68,    69,    70,    17,    72,    73,    74,
      75,    74,    77,    43,    19,    31,    72,    73,    19,    75,
      17,    74,    74,   307,    74,    19,   307,   298,   307,    57,
      23,    24,    25,    26,    27,    55,    17,     6,    18,    74,
      17,    74,    18,    18,    72,    73,    74,    75,    18,    77,
       4,     5,    59,    19,    18,     9,    10,    11,    12,    13,
      14,    15,    16,    10,    74,    57,    20,    21,    22,    72,
      19,    60,    74,    18,    28,    29,    18,    18,    18,    18,
      18,    65,    19,    37,    74,    39,    74,    19,    42,    18,
      43,    44,    45,    46,    47,    48,    18,    18,    17,    62,
      61,    54,    55,    38,    64,    58,    18,    35,    18,    74,
      62,    18,    18,    66,    67,    19,   231,   193,    97,   223,
     184,   271,   342,   241,   300,    -1,   326
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    12,    13,    14,    15,
      16,    20,    21,    22,    28,    29,    37,    39,    42,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    95,    96,   107,   112,   113,   116,   117,   118,   143,
     144,   145,     6,     8,    56,     6,     8,    17,    57,    72,
      73,    74,    75,    77,   111,   119,   120,   123,   124,   125,
      49,    50,    51,    52,    53,    68,    69,    70,    78,   102,
     103,   104,   105,   106,   120,   121,    74,     7,    31,    33,
      74,    74,    40,    83,     0,     3,   146,    74,    74,     8,
      74,    74,   120,    30,    71,    74,   120,    19,    76,    77,
      78,    79,    17,    19,   126,   126,    17,   126,    71,    74,
     122,    33,    74,    74,    37,    43,    41,    17,    38,    74,
      38,    18,    74,    78,    74,   119,   120,   120,   120,   120,
     111,   125,   103,   104,   106,    74,    78,    74,    74,    32,
      34,   132,    74,   114,   111,    75,    74,    98,    74,    38,
      74,    71,    74,    18,    19,    18,    19,   126,   126,   126,
      18,    30,    18,   122,    17,    17,    43,    44,    45,    46,
      47,    48,    54,    55,    58,    66,    67,   103,   104,   106,
     139,   141,   142,    43,    19,   115,    31,    23,    24,    25,
      26,    27,   101,    19,    97,    17,    74,    74,   122,   111,
     122,   111,   122,    74,   122,    19,   127,    77,   110,   111,
     117,    54,    66,    67,    55,   142,   142,   142,    35,    36,
      17,    17,   111,   114,   132,     6,    55,    57,    99,    17,
      99,    98,    18,    74,    17,    18,    18,    18,    74,    59,
     135,   136,    72,    73,    19,   109,   109,    18,    17,   103,
     104,   106,   103,   104,   103,   139,   139,   117,   117,   115,
      74,    57,    72,   100,    97,    19,    94,    74,   122,   122,
     122,   122,    60,   132,   135,   110,   111,    18,    18,   142,
     111,   117,   140,    18,    18,    18,    74,    18,    94,   127,
      74,    65,   134,   109,   109,    19,   108,   108,    17,   103,
      19,    18,    18,    99,    94,    18,    38,    62,    64,   133,
      17,   117,   111,   140,   137,   138,   141,   103,   104,   106,
     139,    61,   128,   110,   111,    18,    35,   126,   126,   126,
      62,   109,   109,   138,   125,   130,   131,    18,    18,    11,
      63,   129,    19,   108,   108,   131
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    93,    94,    94,    95,    96,    97,    97,
      98,    98,    98,    99,    99,    99,   100,   101,   101,   101,
     101,   102,   102,   102,   103,   104,   104,   104,   104,   105,
     105,   105,   105,   105,   106,   106,   106,   107,   107,   108,
     108,   108,   109,   109,   109,   110,   110,   111,   111,   111,
     111,   112,   113,   114,   114,   115,   115,   116,   117,   117,
     117,   118,   119,   119,   120,   120,   120,   120,   120,   120,
     120,   120,   121,   121,   121,   121,   122,   122,   122,   123,
     123,   123,   123,   124,   124,   124,   125,   125,   126,   126,
     126,   126,   127,   127,   128,   128,   129,   129,   129,   130,
     131,   131,   132,   132,   133,   133,   134,   134,   134,   134,
     135,   135,   136,   137,   138,   138,   138,   139,   139,   139,
     139,   140,   140,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   143,   144,
     145,   146,   146
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     9,    10,     0,     3,     5,     7,     0,     3,
       6,     3,     3,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     5,     7,     5,     7,     1,
       1,     1,     1,     1,     5,     7,     5,     9,     9,     0,
       6,     6,     0,     3,     3,     2,     2,     1,     1,     1,
       1,     4,     6,     3,     5,     0,     3,     1,    11,     3,
       3,     2,     1,     3,     3,     3,     3,     3,     3,     2,
       1,     1,     1,     2,     2,     2,     0,     1,     2,     4,
       5,     2,     3,     3,     3,     1,     1,     1,     0,     3,
       3,     3,     0,     4,     0,     3,     0,     1,     1,     2,
       1,     3,     0,     2,     0,     2,     0,     4,     4,     4,
       0,     2,     5,     1,     0,     1,     3,     0,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     5,
       5,     7,     4,     5,     1,     1,     1,     1,     1,     1,
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
#line 248 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1855 "yacc_sql.cpp"
    break;

  case 23:
#line 278 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1864 "yacc_sql.cpp"
    break;

  case 24:
#line 284 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1872 "yacc_sql.cpp"
    break;

  case 25:
#line 289 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1880 "yacc_sql.cpp"
    break;

  case 26:
#line 295 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1888 "yacc_sql.cpp"
    break;

  case 27:
#line 301 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1896 "yacc_sql.cpp"
    break;

  case 28:
#line 307 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1904 "yacc_sql.cpp"
    break;

  case 29:
#line 313 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1914 "yacc_sql.cpp"
    break;

  case 30:
#line 320 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1922 "yacc_sql.cpp"
    break;

  case 31:
#line 326 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1932 "yacc_sql.cpp"
    break;

  case 32:
#line 335 "yacc_sql.y"
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
#line 1957 "yacc_sql.cpp"
    break;

  case 33:
#line 356 "yacc_sql.y"
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
#line 1982 "yacc_sql.cpp"
    break;

  case 34:
#line 379 "yacc_sql.y"
  {
    (yyval.attribute_list) = nullptr;
  }
#line 1990 "yacc_sql.cpp"
    break;

  case 35:
#line 383 "yacc_sql.y"
  {
    if ((yyvsp[0].attribute_list) != nullptr) {
      (yyval.attribute_list) = (yyvsp[0].attribute_list);
    } else {
      (yyval.attribute_list) = new std::vector<std::string>;
    }

    (yyval.attribute_list)->emplace_back((yyvsp[-1].string));
    free((yyvsp[-1].string));
  }
#line 2005 "yacc_sql.cpp"
    break;

  case 36:
#line 397 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2017 "yacc_sql.cpp"
    break;

  case 37:
#line 407 "yacc_sql.y"
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
#line 2037 "yacc_sql.cpp"
    break;

  case 38:
#line 425 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2045 "yacc_sql.cpp"
    break;

  case 39:
#line 429 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2059 "yacc_sql.cpp"
    break;

  case 40:
#line 442 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].is_null);
      free((yyvsp[-5].string));
    }
#line 2072 "yacc_sql.cpp"
    break;

  case 41:
#line 451 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = TEXTS;
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 8;
      (yyval.attr_info)->nullable = (yyvsp[0].is_null);
      free((yyvsp[-2].string));
    }
#line 2085 "yacc_sql.cpp"
    break;

  case 42:
#line 460 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].is_null);
      free((yyvsp[-2].string));
    }
#line 2098 "yacc_sql.cpp"
    break;

  case 43:
#line 471 "yacc_sql.y"
  {
    (yyval.is_null) = true;
  }
#line 2106 "yacc_sql.cpp"
    break;

  case 44:
#line 475 "yacc_sql.y"
  {
    (yyval.is_null) = false;
  }
#line 2114 "yacc_sql.cpp"
    break;

  case 45:
#line 479 "yacc_sql.y"
  {
    (yyval.is_null) = true;
  }
#line 2122 "yacc_sql.cpp"
    break;

  case 46:
#line 485 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2128 "yacc_sql.cpp"
    break;

  case 47:
#line 490 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2134 "yacc_sql.cpp"
    break;

  case 48:
#line 491 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2140 "yacc_sql.cpp"
    break;

  case 49:
#line 492 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2146 "yacc_sql.cpp"
    break;

  case 50:
#line 493 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2152 "yacc_sql.cpp"
    break;

  case 51:
#line 498 "yacc_sql.y"
           { (yyval.func_t)=LENGTH_T; }
#line 2158 "yacc_sql.cpp"
    break;

  case 52:
#line 499 "yacc_sql.y"
                  { (yyval.func_t)=DATE_FORMAT_T; }
#line 2164 "yacc_sql.cpp"
    break;

  case 53:
#line 500 "yacc_sql.y"
            { (yyval.func_t)=ROUND_T; }
#line 2170 "yacc_sql.cpp"
    break;

  case 54:
#line 504 "yacc_sql.y"
                              {
      (yyval.expr_attr) = new RelAttrSqlNode;
      (yyval.expr_attr)->is_expr = true;
      (yyval.expr_attr)->expr = (yyvsp[-1].expression);
      (yyval.expr_attr)->alias = (yyvsp[0].string);
    }
#line 2181 "yacc_sql.cpp"
    break;

  case 55:
#line 513 "yacc_sql.y"
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
#line 2203 "yacc_sql.cpp"
    break;

  case 56:
#line 532 "yacc_sql.y"
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
#line 2228 "yacc_sql.cpp"
    break;

  case 57:
#line 554 "yacc_sql.y"
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
#line 2250 "yacc_sql.cpp"
    break;

  case 58:
#line 573 "yacc_sql.y"
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
#line 2274 "yacc_sql.cpp"
    break;

  case 59:
#line 595 "yacc_sql.y"
        { (yyval.aggr_t)=MAX_T; }
#line 2280 "yacc_sql.cpp"
    break;

  case 60:
#line 596 "yacc_sql.y"
          { (yyval.aggr_t)=MIN_T; }
#line 2286 "yacc_sql.cpp"
    break;

  case 61:
#line 597 "yacc_sql.y"
          { (yyval.aggr_t)=AVG_T; }
#line 2292 "yacc_sql.cpp"
    break;

  case 62:
#line 598 "yacc_sql.y"
          { (yyval.aggr_t)=SUM_T; }
#line 2298 "yacc_sql.cpp"
    break;

  case 63:
#line 599 "yacc_sql.y"
            { (yyval.aggr_t)=COUNT_T; }
#line 2304 "yacc_sql.cpp"
    break;

  case 64:
#line 604 "yacc_sql.y"
    {
      (yyval.aggr_func) = new RelAttrSqlNode;
      (yyval.aggr_func)->is_aggr = true;
      (yyval.aggr_func)->aggr_type = (yyvsp[-4].aggr_t);
      (yyval.aggr_func)->attribute_name = (yyvsp[-2].string);
      (yyval.aggr_func)->alias = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2318 "yacc_sql.cpp"
    break;

  case 65:
#line 613 "yacc_sql.y"
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
#line 2334 "yacc_sql.cpp"
    break;

  case 66:
#line 624 "yacc_sql.y"
                                                             {
      (yyval.aggr_func) = new RelAttrSqlNode;
      (yyval.aggr_func)->is_aggr = true;
      (yyval.aggr_func)->aggr_type = (yyvsp[-4].aggr_t);
      (yyval.aggr_func)->attribute_name = "*";
      (yyval.aggr_func)->alias = (yyvsp[0].string);
      free((yyvsp[0].string));
		}
#line 2347 "yacc_sql.cpp"
    break;

  case 67:
#line 636 "yacc_sql.y"
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
#line 2373 "yacc_sql.cpp"
    break;

  case 68:
#line 659 "yacc_sql.y"
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
#line 2399 "yacc_sql.cpp"
    break;

  case 69:
#line 683 "yacc_sql.y"
  {
    (yyval.insert_list) = nullptr;
  }
#line 2407 "yacc_sql.cpp"
    break;

  case 70:
#line 687 "yacc_sql.y"
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
#line 2428 "yacc_sql.cpp"
    break;

  case 71:
#line 704 "yacc_sql.y"
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
#line 2449 "yacc_sql.cpp"
    break;

  case 72:
#line 724 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2457 "yacc_sql.cpp"
    break;

  case 73:
#line 727 "yacc_sql.y"
                                   {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2471 "yacc_sql.cpp"
    break;

  case 74:
#line 736 "yacc_sql.y"
                              {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2485 "yacc_sql.cpp"
    break;

  case 75:
#line 747 "yacc_sql.y"
                            {
      (yyval.value) = new Value(0-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2494 "yacc_sql.cpp"
    break;

  case 76:
#line 751 "yacc_sql.y"
               {
      (yyval.value) = new Value(0-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2503 "yacc_sql.cpp"
    break;

  case 77:
#line 757 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2512 "yacc_sql.cpp"
    break;

  case 78:
#line 761 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2521 "yacc_sql.cpp"
    break;

  case 79:
#line 765 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2531 "yacc_sql.cpp"
    break;

  case 80:
#line 770 "yacc_sql.y"
            {
      (yyval.value) = new Value(); // UNDEFINED TYPE HERE
      (yyval.value)->set_null();
    }
#line 2540 "yacc_sql.cpp"
    break;

  case 81:
#line 778 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2554 "yacc_sql.cpp"
    break;

  case 82:
#line 791 "yacc_sql.y"
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
#line 2577 "yacc_sql.cpp"
    break;

  case 83:
#line 812 "yacc_sql.y"
  {
    (yyval.update_pair) = new UpdateListSqlNode{(yyvsp[-2].string), *(yyvsp[0].value), SelectSqlNode{}, false};
    free((yyvsp[0].value));
  }
#line 2586 "yacc_sql.cpp"
    break;

  case 84:
#line 817 "yacc_sql.y"
  {
    (yyval.update_pair) = new UpdateListSqlNode{(yyvsp[-4].string), Value{}, *(yyvsp[-1].select_body), true};
    free((yyvsp[-1].select_body));
  }
#line 2595 "yacc_sql.cpp"
    break;

  case 85:
#line 823 "yacc_sql.y"
    {
      (yyval.update_list) = nullptr;
    }
#line 2603 "yacc_sql.cpp"
    break;

  case 86:
#line 827 "yacc_sql.y"
    {
      if ((yyvsp[0].update_list) != nullptr) {
        (yyval.update_list) = (yyvsp[0].update_list);
      } else {
        (yyval.update_list) = new std::vector<UpdateListSqlNode>;
      }

      (yyval.update_list)->emplace_back(*(yyvsp[-1].update_pair));
      free((yyvsp[-1].update_pair));
    }
#line 2618 "yacc_sql.cpp"
    break;

  case 87:
#line 842 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      (yyval.sql_node)->selection = *(yyvsp[0].select_body);
      delete (yyvsp[0].select_body);
    }
#line 2628 "yacc_sql.cpp"
    break;

  case 88:
#line 852 "yacc_sql.y"
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
#line 2681 "yacc_sql.cpp"
    break;

  case 89:
#line 902 "yacc_sql.y"
    {
      (yyval.select_body) = new SelectSqlNode;
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.select_body)->attributes.swap(*(yyvsp[0].rel_attr_list));
        delete (yyvsp[0].rel_attr_list);
      }
      (yyval.select_body)->attributes.emplace_back(*(yyvsp[-1].normal_func));
      free((yyvsp[-1].normal_func));
    }
#line 2695 "yacc_sql.cpp"
    break;

  case 90:
#line 912 "yacc_sql.y"
    {
      (yyval.select_body) = new SelectSqlNode;
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.select_body)->attributes.swap(*(yyvsp[0].rel_attr_list));
        delete (yyvsp[0].rel_attr_list);
      }
      (yyval.select_body)->attributes.emplace_back(*(yyvsp[-1].expr_attr));
      free((yyvsp[-1].expr_attr));
    }
#line 2709 "yacc_sql.cpp"
    break;

  case 91:
#line 925 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2720 "yacc_sql.cpp"
    break;

  case 92:
#line 935 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2729 "yacc_sql.cpp"
    break;

  case 93:
#line 940 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2742 "yacc_sql.cpp"
    break;

  case 94:
#line 951 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
      LOG_DEBUG("ADD");
    }
#line 2751 "yacc_sql.cpp"
    break;

  case 95:
#line 955 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
      LOG_DEBUG("SUB");
    }
#line 2760 "yacc_sql.cpp"
    break;

  case 96:
#line 959 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
      LOG_DEBUG("MUL");
    }
#line 2769 "yacc_sql.cpp"
    break;

  case 97:
#line 963 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
      LOG_DEBUG("DIV");
    }
#line 2778 "yacc_sql.cpp"
    break;

  case 98:
#line 967 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      LOG_DEBUG("()");
    }
#line 2788 "yacc_sql.cpp"
    break;

  case 99:
#line 972 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
      LOG_DEBUG("-");
    }
#line 2797 "yacc_sql.cpp"
    break;

  case 100:
#line 976 "yacc_sql.y"
               {
      (yyval.expression) = new FieldExpr(*(yyvsp[0].rel_attr));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2807 "yacc_sql.cpp"
    break;

  case 101:
#line 981 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2817 "yacc_sql.cpp"
    break;

  case 102:
#line 990 "yacc_sql.y"
        {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      attr.expr = new FieldExpr("*");
      attr.is_expr = true;
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 2831 "yacc_sql.cpp"
    break;

  case 103:
#line 1008 "yacc_sql.y"
                          {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].aggr_func));
      delete (yyvsp[-1].aggr_func);
      }
#line 2845 "yacc_sql.cpp"
    break;

  case 104:
#line 1017 "yacc_sql.y"
                            {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].normal_func));
      delete (yyvsp[-1].normal_func);
    }
#line 2859 "yacc_sql.cpp"
    break;

  case 105:
#line 1026 "yacc_sql.y"
                          {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].expr_attr));
      delete (yyvsp[-1].expr_attr);
    }
#line 2873 "yacc_sql.cpp"
    break;

  case 106:
#line 1038 "yacc_sql.y"
    {
      (yyval.string) = strdup("");
    }
#line 2881 "yacc_sql.cpp"
    break;

  case 107:
#line 1042 "yacc_sql.y"
    {
      (yyval.string) = strdup((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2890 "yacc_sql.cpp"
    break;

  case 108:
#line 1046 "yacc_sql.y"
            {
      (yyval.string) = strdup((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2899 "yacc_sql.cpp"
    break;

  case 109:
#line 1053 "yacc_sql.y"
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
#line 2914 "yacc_sql.cpp"
    break;

  case 110:
#line 1063 "yacc_sql.y"
                      {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->is_aggr = false;
      (yyval.rel_attr)->relation_name  = (yyvsp[-4].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2929 "yacc_sql.cpp"
    break;

  case 111:
#line 1073 "yacc_sql.y"
            {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->is_aggr = false;
      (yyval.rel_attr)->attribute_name = (yyvsp[-1].string);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 2942 "yacc_sql.cpp"
    break;

  case 112:
#line 1081 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->is_aggr = false;
      (yyval.rel_attr)->attribute_name = (yyvsp[-2].string);
      (yyval.rel_attr)->alias = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2955 "yacc_sql.cpp"
    break;

  case 113:
#line 1091 "yacc_sql.y"
              {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->is_aggr = false;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      (yyval.rel_attr)->alias = "";
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2969 "yacc_sql.cpp"
    break;

  case 114:
#line 1100 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->is_aggr = false;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = '*';
      free((yyvsp[-2].string));
    }
#line 2981 "yacc_sql.cpp"
    break;

  case 115:
#line 1107 "yacc_sql.y"
         {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->is_aggr = false;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      (yyval.rel_attr)->alias = "";
      free((yyvsp[0].string));
    }
#line 2993 "yacc_sql.cpp"
    break;

  case 116:
#line 1117 "yacc_sql.y"
                    {
    (yyval.rel_attr) = (yyvsp[0].rel_attr);
  }
#line 3001 "yacc_sql.cpp"
    break;

  case 117:
#line 1120 "yacc_sql.y"
                        {
    (yyval.rel_attr) = (yyvsp[0].rel_attr);
  }
#line 3009 "yacc_sql.cpp"
    break;

  case 118:
#line 1126 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 3017 "yacc_sql.cpp"
    break;

  case 119:
#line 1129 "yacc_sql.y"
                                {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }

      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].aggr_func));
      delete (yyvsp[-1].aggr_func);
    }
#line 3032 "yacc_sql.cpp"
    break;

  case 120:
#line 1139 "yacc_sql.y"
                                  {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].normal_func));
      delete (yyvsp[-1].normal_func);
    }
#line 3046 "yacc_sql.cpp"
    break;

  case 121:
#line 1148 "yacc_sql.y"
                                {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }

      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].expr_attr));
      delete (yyvsp[-1].expr_attr);
    }
#line 3061 "yacc_sql.cpp"
    break;

  case 122:
#line 1162 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 3069 "yacc_sql.cpp"
    break;

  case 123:
#line 1165 "yacc_sql.y"
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
#line 3085 "yacc_sql.cpp"
    break;

  case 124:
#line 1179 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 3093 "yacc_sql.cpp"
    break;

  case 125:
#line 1183 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 3101 "yacc_sql.cpp"
    break;

  case 126:
#line 1189 "yacc_sql.y"
    {
      (yyval.order_t) = ASC_T;
    }
#line 3109 "yacc_sql.cpp"
    break;

  case 127:
#line 1194 "yacc_sql.y"
    {
      (yyval.order_t) = ASC_T;
    }
#line 3117 "yacc_sql.cpp"
    break;

  case 128:
#line 1199 "yacc_sql.y"
    {
      (yyval.order_t) = DESC_T;
    }
#line 3125 "yacc_sql.cpp"
    break;

  case 129:
#line 1206 "yacc_sql.y"
    {
        (yyval.order_by_attr) = new OrderBySqlNode;
        (yyval.order_by_attr)->attr = *(yyvsp[-1].rel_attr);
        (yyval.order_by_attr)->order_type = (yyvsp[0].order_t);
        delete (yyvsp[-1].rel_attr);
    }
#line 3136 "yacc_sql.cpp"
    break;

  case 130:
#line 1216 "yacc_sql.y"
    {
      (yyval.order_by_list) = new std::vector<OrderBySqlNode>;
      (yyval.order_by_list)->emplace_back(*(yyvsp[0].order_by_attr));
      delete (yyvsp[0].order_by_attr);
    }
#line 3146 "yacc_sql.cpp"
    break;

  case 131:
#line 1221 "yacc_sql.y"
                                        {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
      (yyval.order_by_list)->emplace_back(*(yyvsp[-2].order_by_attr));
      delete (yyvsp[-2].order_by_attr);
    }
#line 3156 "yacc_sql.cpp"
    break;

  case 132:
#line 1230 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3164 "yacc_sql.cpp"
    break;

  case 133:
#line 1233 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3172 "yacc_sql.cpp"
    break;

  case 134:
#line 1241 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3180 "yacc_sql.cpp"
    break;

  case 135:
#line 1244 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3188 "yacc_sql.cpp"
    break;

  case 136:
#line 1250 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 3196 "yacc_sql.cpp"
    break;

  case 137:
#line 1253 "yacc_sql.y"
                                   {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].expr_attr));
      delete (yyvsp[-1].expr_attr);
    }
#line 3210 "yacc_sql.cpp"
    break;

  case 138:
#line 1262 "yacc_sql.y"
                                   {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].aggr_func));
      delete (yyvsp[-1].aggr_func);
      }
#line 3224 "yacc_sql.cpp"
    break;

  case 139:
#line 1271 "yacc_sql.y"
                                     {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].normal_func));
      delete (yyvsp[-1].normal_func);
      }
#line 3238 "yacc_sql.cpp"
    break;

  case 140:
#line 1283 "yacc_sql.y"
    {
      (yyval.inner_join_list) = nullptr;
    }
#line 3246 "yacc_sql.cpp"
    break;

  case 141:
#line 1286 "yacc_sql.y"
                                 {
      if ((yyvsp[0].inner_join_list) != nullptr) {
        (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
      } else {
        (yyval.inner_join_list) = new std::vector<InnerJoinSqlNode>;
      }
      (yyval.inner_join_list)->emplace_back(*(yyvsp[-1].inner_join));
      delete (yyvsp[-1].inner_join);
    }
#line 3260 "yacc_sql.cpp"
    break;

  case 142:
#line 1298 "yacc_sql.y"
                                         {
      (yyval.inner_join) = new InnerJoinSqlNode;
      (yyval.inner_join)->relation_name = (yyvsp[-2].string);
      (yyval.inner_join)->join_conditions.swap(*(yyvsp[0].condition_list));
      delete (yyvsp[0].condition_list);
    }
#line 3271 "yacc_sql.cpp"
    break;

  case 143:
#line 1308 "yacc_sql.y"
    {
      (yyval.condition) = (yyvsp[0].condition);
    }
#line 3279 "yacc_sql.cpp"
    break;

  case 144:
#line 1314 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3287 "yacc_sql.cpp"
    break;

  case 145:
#line 1318 "yacc_sql.y"
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3297 "yacc_sql.cpp"
    break;

  case 146:
#line 1323 "yacc_sql.y"
                                             {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3307 "yacc_sql.cpp"
    break;

  case 147:
#line 1332 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3315 "yacc_sql.cpp"
    break;

  case 148:
#line 1336 "yacc_sql.y"
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3325 "yacc_sql.cpp"
    break;

  case 149:
#line 1341 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3335 "yacc_sql.cpp"
    break;

  case 150:
#line 1346 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->is_and = false;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3346 "yacc_sql.cpp"
    break;

  case 151:
#line 1356 "yacc_sql.y"
                      {
      (yyval.value_list) = new std::vector<Value>;
      (yyval.value_list)->emplace_back(*(yyvsp[-2].value));
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
    }
#line 3358 "yacc_sql.cpp"
    break;

  case 152:
#line 1363 "yacc_sql.y"
                                   {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-2].value));
      delete (yyvsp[-2].value);
    }
#line 3372 "yacc_sql.cpp"
    break;

  case 153:
#line 1376 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].normal_func);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].expr_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].normal_func);
      delete (yyvsp[0].expr_attr);
    }
#line 3388 "yacc_sql.cpp"
    break;

  case 154:
#line 1388 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].expr_attr);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].normal_func);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].expr_attr);
      delete (yyvsp[0].normal_func);
    }
#line 3404 "yacc_sql.cpp"
    break;

  case 155:
#line 1400 "yacc_sql.y"
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
#line 3420 "yacc_sql.cpp"
    break;

  case 156:
#line 1412 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].expr_attr);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].aggr_func);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].expr_attr);
      delete (yyvsp[0].aggr_func);
    }
#line 3436 "yacc_sql.cpp"
    break;

  case 157:
#line 1424 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].aggr_func);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].expr_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].aggr_func);
      delete (yyvsp[0].expr_attr);
    }
#line 3452 "yacc_sql.cpp"
    break;

  case 158:
#line 1436 "yacc_sql.y"
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
#line 3468 "yacc_sql.cpp"
    break;

  case 159:
#line 1449 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      // $$->left_is_attr = 0;
      // $$->left_value = *$1;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].expr_attr);
      (yyval.condition)->right_is_select = 1;
      (yyval.condition)->right_select = (yyvsp[-1].select_body);
      (yyval.condition)->comp = (yyvsp[-3].comp);
      delete (yyvsp[-4].expr_attr);
    }
#line 3484 "yacc_sql.cpp"
    break;

  case 160:
#line 1461 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_select = 1;
      (yyval.condition)->left_select = (yyvsp[-3].select_body);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].expr_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      delete (yyvsp[0].expr_attr);
    }
#line 3498 "yacc_sql.cpp"
    break;

  case 161:
#line 1471 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_select = 1;
      (yyval.condition)->left_select = (yyvsp[-5].select_body);
      (yyval.condition)->right_is_select = 1;
      (yyval.condition)->right_select = (yyvsp[-1].select_body);
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 3511 "yacc_sql.cpp"
    break;

  case 162:
#line 1480 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_select = 0;
      (yyval.condition)->right_is_select = 1;
      (yyval.condition)->right_select = (yyvsp[-1].select_body);
      (yyval.condition)->comp = (yyvsp[-3].comp);
      (yyval.condition)->unary_op = 1;
    }
#line 3524 "yacc_sql.cpp"
    break;

  case 163:
#line 1489 "yacc_sql.y"
    {
      // HERE
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].expr_attr);
      (yyval.condition)->right_is_select = 1;
      (yyval.condition)->comp = (yyvsp[-3].comp);
      (yyval.condition)->values.swap(*(yyvsp[-1].value_list));
      // $$->values.emplace_back(*$4);
      std::reverse((yyval.condition)->values.begin(), (yyval.condition)->values.end());
      // delete $5;
    }
#line 3541 "yacc_sql.cpp"
    break;

  case 164:
#line 1504 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3547 "yacc_sql.cpp"
    break;

  case 165:
#line 1505 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3553 "yacc_sql.cpp"
    break;

  case 166:
#line 1506 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3559 "yacc_sql.cpp"
    break;

  case 167:
#line 1507 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3565 "yacc_sql.cpp"
    break;

  case 168:
#line 1508 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3571 "yacc_sql.cpp"
    break;

  case 169:
#line 1509 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3577 "yacc_sql.cpp"
    break;

  case 170:
#line 1510 "yacc_sql.y"
           { (yyval.comp) = STR_LIKE; }
#line 3583 "yacc_sql.cpp"
    break;

  case 171:
#line 1511 "yacc_sql.y"
               { (yyval.comp) = STR_NOT_LIKE; }
#line 3589 "yacc_sql.cpp"
    break;

  case 172:
#line 1512 "yacc_sql.y"
           { (yyval.comp) = IS; }
#line 3595 "yacc_sql.cpp"
    break;

  case 173:
#line 1513 "yacc_sql.y"
               { (yyval.comp) = IS_NOT; }
#line 3601 "yacc_sql.cpp"
    break;

  case 174:
#line 1514 "yacc_sql.y"
           { (yyval.comp) = IN; }
#line 3607 "yacc_sql.cpp"
    break;

  case 175:
#line 1515 "yacc_sql.y"
               { (yyval.comp) = IN_NOT; }
#line 3613 "yacc_sql.cpp"
    break;

  case 176:
#line 1516 "yacc_sql.y"
              { (yyval.comp) = EXIST; }
#line 3619 "yacc_sql.cpp"
    break;

  case 177:
#line 1517 "yacc_sql.y"
                  { (yyval.comp) = EXIST_NOT; }
#line 3625 "yacc_sql.cpp"
    break;

  case 178:
#line 1522 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);

      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3639 "yacc_sql.cpp"
    break;

  case 179:
#line 1535 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3648 "yacc_sql.cpp"
    break;

  case 180:
#line 1543 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3660 "yacc_sql.cpp"
    break;


#line 3664 "yacc_sql.cpp"

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
#line 1555 "yacc_sql.y"

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
