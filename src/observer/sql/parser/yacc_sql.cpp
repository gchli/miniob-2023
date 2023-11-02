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
#define YYFINAL  84
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   377

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  170
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  313

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
     315,   322,   328,   336,   345,   366,   390,   393,   407,   417,
     433,   442,   463,   466,   479,   488,   497,   509,   512,   516,
     523,   528,   529,   530,   531,   536,   537,   538,   542,   550,
     567,   587,   603,   624,   625,   626,   627,   628,   632,   640,
     650,   660,   685,   688,   709,   712,   724,   729,   734,   738,
     744,   748,   752,   757,   764,   777,   798,   803,   810,   813,
     828,   838,   887,   900,   910,   915,   927,   931,   935,   939,
     943,   948,   952,   957,   962,   967,   976,   985,   997,  1000,
    1005,  1009,  1015,  1024,  1031,  1042,  1045,  1059,  1062,  1076,
    1079,  1086,  1090,  1095,  1102,  1112,  1118,  1127,  1130,  1138,
    1141,  1147,  1150,  1162,  1165,  1177,  1186,  1193,  1196,  1202,
    1211,  1214,  1220,  1225,  1235,  1242,  1254,  1265,  1275,  1285,
    1294,  1303,  1317,  1318,  1319,  1320,  1321,  1322,  1323,  1324,
    1325,  1326,  1327,  1328,  1329,  1330,  1334,  1347,  1355,  1365,
    1366
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

#define YYPACT_NINF (-262)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-108)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     331,    17,    21,   212,   119,   -47,    42,  -262,    51,    35,
      16,  -262,  -262,  -262,  -262,  -262,    48,    56,   331,   117,
     126,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,
    -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,
    -262,  -262,  -262,    59,    77,   151,    88,   100,   104,   212,
    -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,
    -262,   150,  -262,   212,   165,  -262,   166,  -262,  -262,  -262,
      28,  -262,  -262,   167,    41,   152,  -262,  -262,   109,   121,
     162,   157,   160,  -262,  -262,  -262,  -262,     7,   168,   129,
     132,  -262,   169,    -3,   -27,  -262,   -17,    11,   212,   212,
     212,   212,   212,   212,   175,   -30,  -262,  -262,   134,   178,
     177,   137,    57,   138,   158,   203,   159,   194,   203,   163,
    -262,  -262,  -262,    68,   128,  -262,  -262,   147,    65,   217,
    -262,    94,    94,  -262,  -262,   167,  -262,  -262,    64,   220,
     173,  -262,   201,   226,  -262,   219,   131,   234,  -262,   237,
     180,  -262,  -262,  -262,  -262,  -262,    37,  -262,    37,  -262,
     181,  -262,  -262,   238,    37,    75,  -262,  -262,  -262,  -262,
    -262,  -262,  -262,   -28,   205,  -262,  -262,   -12,  -262,   142,
     241,    -7,   137,   177,   260,  -262,  -262,  -262,  -262,   105,
      24,   158,   249,   193,   253,   254,   258,   259,   196,   215,
     264,   261,  -262,  -262,  -262,  -262,   242,   173,   173,   203,
     203,  -262,   226,  -262,   209,   232,  -262,  -262,   223,  -262,
     234,   203,   278,   225,  -262,  -262,  -262,    64,   243,   177,
     215,    37,   280,   -12,    75,  -262,  -262,  -262,   283,   284,
    -262,  -262,  -262,  -262,   286,  -262,  -262,   239,   301,   278,
     238,   246,   257,  -262,   264,   304,   256,   308,   310,   315,
    -262,  -262,   105,   278,  -262,   319,  -262,   300,   277,   285,
    -262,   333,  -262,    75,  -262,    57,  -262,  -262,  -262,  -262,
    -262,   173,   212,   173,   287,    37,   336,   308,  -262,   320,
    -262,  -262,   167,  -262,   294,  -262,   264,  -262,   173,  -262,
     282,   340,  -262,     8,   342,  -262,   304,  -262,  -262,  -262,
     282,  -262,  -262
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     169,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      23,    12,    13,     8,     5,     7,     6,     4,    90,     3,
      18,    19,    20,     0,     0,     0,     0,     0,     0,     0,
      63,    64,    65,    66,    67,    83,    55,    56,    57,    80,
      81,   114,    82,     0,     0,   105,     0,   104,   103,    93,
      94,   102,   106,   115,   108,     0,    32,    31,     0,     0,
       0,     0,     0,   167,     1,   170,     2,     0,     0,     0,
       0,    30,     0,     0,     0,   101,     0,     0,     0,     0,
       0,     0,     0,     0,    92,     0,   109,    58,     0,     0,
     127,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     100,   112,   113,     0,     0,    76,    77,     0,     0,     0,
      95,    96,    97,    98,    99,   115,   111,   110,   108,     0,
     140,    84,     0,    88,   168,     0,     0,    42,    40,     0,
       0,    33,    38,    78,    79,    61,     0,    59,     0,    68,
       0,    70,   116,   117,     0,     0,   152,   153,   154,   155,
     156,   157,   158,     0,   160,   162,   164,     0,   128,   141,
       0,     0,     0,   127,     0,    51,    52,    53,    54,    47,
      47,     0,     0,     0,     0,     0,     0,     0,     0,   133,
      74,     0,   159,   163,   165,   161,     0,   140,   140,     0,
       0,    86,    88,    85,     0,     0,    49,    45,     0,    46,
      42,    39,    36,     0,    62,    60,    69,   108,     0,   127,
     133,     0,     0,     0,     0,   146,   142,   143,     0,     0,
      89,   166,    48,    50,     0,    43,    41,     0,     0,    36,
     117,     0,   131,   134,    74,    72,     0,   103,     0,     0,
     150,    87,    47,    36,    34,     0,   118,     0,     0,   129,
      75,     0,    71,     0,   148,     0,   147,   151,    44,    37,
      35,   137,     0,   140,   119,     0,     0,   144,   145,   138,
     135,   136,   115,   130,     0,    91,    74,   149,   137,   132,
       0,     0,   139,   121,   125,   120,    72,   123,   122,   124,
       0,    73,   126
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -262,  -262,   344,  -262,  -262,  -262,  -262,  -262,  -262,  -262,
    -262,  -262,  -262,  -262,  -219,  -262,  -262,   143,   174,  -182,
    -262,  -262,  -262,    -4,  -262,  -262,  -262,  -262,    58,  -233,
    -147,  -262,   -94,  -262,  -262,   184,   155,  -262,  -112,  -262,
     271,     2,  -262,  -134,   -95,  -128,   122,  -262,  -262,  -262,
      61,  -169,  -262,  -262,   144,  -262,  -262,    78,  -195,   102,
    -261,  -161,  -262,  -262,  -262,  -262
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,   248,    32,    33,   192,   147,   217,
     244,   190,    64,   177,    65,    66,    67,    34,   272,   232,
     124,   125,    68,    35,    36,   143,   183,    37,    38,    39,
      69,    74,    75,   107,    71,   104,   199,   295,   309,   304,
     305,   141,   284,   269,   229,   230,   289,   290,   178,   259,
     179,   180,    40,    41,    42,    86
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      73,   127,   126,   148,   163,    70,   151,   162,   219,   195,
     210,   196,   236,   237,   213,   120,   206,   200,   144,   307,
     291,   270,   136,    43,   114,    44,   202,    47,    76,    48,
     265,   166,   167,   168,   169,   170,   171,   291,   203,   204,
      55,   218,   172,   173,   279,   137,   174,    98,   121,    77,
      55,    93,   122,   201,   175,   176,    59,    60,    61,    62,
     252,   123,   126,   301,   126,    95,    59,    60,    79,    62,
     126,   308,   256,    45,    99,   100,   101,   102,   115,   215,
     278,   216,    78,   159,   254,     4,   128,   211,   293,    46,
     129,    80,    49,   250,    55,   160,    82,   238,   239,   135,
      70,   131,   132,   133,   134,    99,   100,   101,   102,   246,
      59,    60,   105,    62,    55,   123,   106,    84,    99,   100,
     101,   102,   258,    81,    50,    51,    52,    53,    54,    85,
      59,    60,    55,    62,    87,   105,    49,   126,   296,   106,
     257,   153,   154,    56,    57,    58,   155,   156,    59,    60,
      61,    62,    88,    63,   185,   186,   187,   188,   189,    89,
     215,   286,   216,    90,   299,   157,   158,    93,    50,    51,
      52,    53,    54,   101,   102,    91,    55,   207,   208,    92,
      94,   287,    96,    97,   109,   108,   103,    56,    57,    58,
     165,   126,    59,    60,    61,    62,   110,    63,    72,   111,
     112,   113,   235,   118,   117,   303,   116,   119,  -107,   138,
     139,   140,   142,     4,   145,   303,   166,   167,   168,   169,
     170,   171,    50,    51,    52,    53,    54,   172,   173,    49,
      55,   174,   150,   146,   149,   161,    93,   164,   152,   175,
     176,    56,    57,    58,   181,   182,    59,    60,    61,    62,
     184,    63,   274,   191,   193,   194,   197,   198,   209,   234,
     205,    50,    51,    52,    53,    54,   214,   221,   222,    55,
     223,   227,   224,   273,   228,    93,   225,   226,   292,   233,
      56,    57,    58,   231,   241,    59,    60,    61,    62,   242,
      63,    50,    51,    52,    53,    54,   243,   247,   255,    55,
     249,   260,   261,   251,   262,    50,    51,    52,    53,    54,
      56,    57,    58,    55,   263,    59,    60,    61,    62,   264,
      63,   267,   268,   271,    56,    57,    58,   275,   276,    59,
      60,    61,    62,   277,    63,     1,     2,   280,   281,   282,
       3,     4,     5,     6,     7,     8,     9,    10,   294,   283,
     285,    11,    12,    13,   297,   298,   300,    61,   306,    14,
      15,   310,    83,   245,   311,   220,   212,   240,    16,   130,
      17,   312,   266,    18,   253,     0,   302,   288
};

static const yytype_int16 yycheck[] =
{
       4,    96,    96,   115,   138,     3,   118,   135,   190,   156,
      17,   158,   207,   208,   183,    18,   177,   164,   112,    11,
     281,   254,    52,     6,    17,     8,    54,     6,    75,     8,
     249,    43,    44,    45,    46,    47,    48,   298,    66,    67,
      57,    17,    54,    55,   263,    75,    58,    19,    75,     7,
      57,    49,    79,   165,    66,    67,    73,    74,    75,    76,
     229,    78,   156,   296,   158,    63,    73,    74,    33,    76,
     164,    63,   233,    56,    77,    78,    79,    80,    71,    55,
     262,    57,    31,    18,   231,    10,    75,   181,   283,    72,
      79,    75,    17,   227,    57,    30,    40,   209,   210,   103,
      98,    99,   100,   101,   102,    77,    78,    79,    80,   221,
      73,    74,    71,    76,    57,    78,    75,     0,    77,    78,
      79,    80,   234,    75,    49,    50,    51,    52,    53,     3,
      73,    74,    57,    76,    75,    71,    17,   231,   285,    75,
     234,    73,    74,    68,    69,    70,    18,    19,    73,    74,
      75,    76,    75,    78,    23,    24,    25,    26,    27,     8,
      55,   273,    57,    75,   292,    18,    19,   165,    49,    50,
      51,    52,    53,    79,    80,    75,    57,    35,    36,    75,
      30,   275,    17,    17,    75,    33,    19,    68,    69,    70,
      17,   285,    73,    74,    75,    76,    75,    78,    79,    37,
      43,    41,   206,    71,    75,   300,    38,    38,    33,    75,
      32,    34,    75,    10,    76,   310,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    17,
      57,    58,    38,    75,    75,    18,   234,    17,    75,    66,
      67,    68,    69,    70,    43,    19,    73,    74,    75,    76,
      31,    78,   256,    19,    17,    75,    75,    19,    17,    17,
      55,    49,    50,    51,    52,    53,     6,    18,    75,    57,
      17,    75,    18,    17,    59,   273,    18,    18,   282,    18,
      68,    69,    70,    19,    75,    73,    74,    75,    76,    57,
      78,    49,    50,    51,    52,    53,    73,    19,    18,    57,
      75,    18,    18,    60,    18,    49,    50,    51,    52,    53,
      68,    69,    70,    57,    75,    73,    74,    75,    76,    18,
      78,    75,    65,    19,    68,    69,    70,    19,    18,    73,
      74,    75,    76,    18,    78,     4,     5,    18,    38,    62,
       9,    10,    11,    12,    13,    14,    15,    16,    61,    64,
      17,    20,    21,    22,    18,    35,    62,    75,    18,    28,
      29,    19,    18,   220,   306,   191,   182,   212,    37,    98,
      39,   310,   250,    42,   230,    -1,   298,   275
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
     123,   126,    79,   105,   123,   124,    75,     7,    31,    33,
      75,    75,    40,    84,     0,     3,   147,    75,    75,     8,
      75,    75,    75,   123,    30,   123,    17,    17,    19,    77,
      78,    79,    80,    19,   127,    71,    75,   125,    33,    75,
      75,    37,    43,    41,    17,    71,    38,    75,    71,    38,
      18,    75,    79,    78,   112,   113,   114,   126,    75,    79,
     122,   123,   123,   123,   123,   105,    52,    75,    75,    32,
      34,   133,    75,   117,   114,    76,    75,   100,   120,    75,
      38,   120,    75,    73,    74,    18,    19,    18,    19,    18,
      30,    18,   127,   125,    17,    17,    43,    44,    45,    46,
      47,    48,    54,    55,    58,    66,    67,   105,   140,   142,
     143,    43,    19,   118,    31,    23,    24,    25,    26,    27,
     103,    19,    99,    17,    75,   112,   112,    75,    19,   128,
     112,   120,    54,    66,    67,    55,   143,    35,    36,    17,
      17,   114,   117,   133,     6,    55,    57,   101,    17,   101,
     100,    18,    75,    17,    18,    18,    18,    75,    59,   136,
     137,    19,   111,    18,    17,   105,   140,   140,   120,   120,
     118,    75,    57,    73,   102,    99,   120,    19,    96,    75,
     125,    60,   133,   136,   112,    18,   143,   114,   120,   141,
      18,    18,    18,    75,    18,    96,   128,    75,    65,   135,
     111,    19,   110,    17,   105,    19,    18,    18,   101,    96,
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
      91,    92,    93,    94,    95,    95,    96,    96,    97,    98,
      98,    98,    99,    99,   100,   100,   100,   101,   101,   101,
     102,   103,   103,   103,   103,   104,   104,   104,   105,   106,
     106,   106,   106,   107,   107,   107,   107,   107,   108,   108,
     108,   109,   110,   110,   111,   111,   112,   112,   113,   113,
     114,   114,   114,   114,   115,   116,   117,   117,   118,   118,
     119,   120,   120,   121,   122,   122,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   124,   124,   125,   125,
     125,   125,   126,   126,   126,   127,   127,   128,   128,   129,
     129,   130,   130,   130,   131,   132,   132,   133,   133,   134,
     134,   135,   135,   136,   136,   137,   138,   139,   139,   139,
     140,   140,   140,   140,   141,   141,   142,   142,   142,   142,
     142,   142,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   144,   145,   146,   147,
     147
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     5,     9,    10,     0,     3,     5,     7,
       5,     8,     0,     3,     6,     3,     3,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     4,
       6,     4,     6,     1,     1,     1,     1,     1,     4,     6,
       4,     9,     0,     6,     0,     3,     1,     1,     2,     2,
       1,     1,     1,     1,     4,     6,     3,     5,     0,     3,
       1,    11,     3,     2,     1,     3,     3,     3,     3,     3,
       3,     2,     1,     1,     1,     1,     1,     2,     0,     1,
       2,     2,     3,     3,     1,     0,     3,     0,     4,     0,
       3,     0,     1,     1,     2,     1,     3,     0,     2,     0,
       2,     0,     4,     0,     2,     5,     1,     0,     1,     3,
       0,     1,     3,     3,     3,     3,     3,     5,     5,     7,
       4,     5,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     1,     2,     1,     2,     7,     2,     4,     0,
       1
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
#line 1837 "yacc_sql.cpp"
    break;

  case 24:
#line 280 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1846 "yacc_sql.cpp"
    break;

  case 25:
#line 286 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1854 "yacc_sql.cpp"
    break;

  case 26:
#line 291 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1862 "yacc_sql.cpp"
    break;

  case 27:
#line 297 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1870 "yacc_sql.cpp"
    break;

  case 28:
#line 303 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1878 "yacc_sql.cpp"
    break;

  case 29:
#line 309 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1886 "yacc_sql.cpp"
    break;

  case 30:
#line 315 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1896 "yacc_sql.cpp"
    break;

  case 31:
#line 322 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1904 "yacc_sql.cpp"
    break;

  case 32:
#line 328 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1914 "yacc_sql.cpp"
    break;

  case 33:
#line 336 "yacc_sql.y"
                                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
      (yyval.sql_node)->create_view.view_name = (yyvsp[-2].string);
      (yyval.sql_node)->create_view.select = (yyvsp[0].select_body);
      free((yyvsp[-2].string));
    }
#line 1925 "yacc_sql.cpp"
    break;

  case 34:
#line 346 "yacc_sql.y"
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
#line 1950 "yacc_sql.cpp"
    break;

  case 35:
#line 367 "yacc_sql.y"
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
#line 1975 "yacc_sql.cpp"
    break;

  case 36:
#line 390 "yacc_sql.y"
  {
    (yyval.attribute_list) = nullptr;
  }
#line 1983 "yacc_sql.cpp"
    break;

  case 37:
#line 394 "yacc_sql.y"
  {
    if ((yyvsp[0].attribute_list) != nullptr) {
      (yyval.attribute_list) = (yyvsp[0].attribute_list);
    } else {
      (yyval.attribute_list) = new std::vector<std::string>;
    }

    (yyval.attribute_list)->emplace_back((yyvsp[-1].string));
    free((yyvsp[-1].string));
  }
#line 1998 "yacc_sql.cpp"
    break;

  case 38:
#line 408 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2010 "yacc_sql.cpp"
    break;

  case 39:
#line 418 "yacc_sql.y"
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
#line 2030 "yacc_sql.cpp"
    break;

  case 40:
#line 434 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-2].string);
      free((yyvsp[-2].string));

      create_table.select = (yyvsp[0].select_body);
    }
#line 2043 "yacc_sql.cpp"
    break;

  case 41:
#line 443 "yacc_sql.y"
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
#line 2065 "yacc_sql.cpp"
    break;

  case 42:
#line 463 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2073 "yacc_sql.cpp"
    break;

  case 43:
#line 467 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2087 "yacc_sql.cpp"
    break;

  case 44:
#line 480 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->nullable = (yyvsp[0].is_null);
      free((yyvsp[-5].string));
    }
#line 2100 "yacc_sql.cpp"
    break;

  case 45:
#line 489 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = TEXTS;
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 8;
      (yyval.attr_info)->nullable = (yyvsp[0].is_null);
      free((yyvsp[-2].string));
    }
#line 2113 "yacc_sql.cpp"
    break;

  case 46:
#line 498 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->nullable = (yyvsp[0].is_null);
      free((yyvsp[-2].string));
    }
#line 2126 "yacc_sql.cpp"
    break;

  case 47:
#line 509 "yacc_sql.y"
  {
    (yyval.is_null) = true;
  }
#line 2134 "yacc_sql.cpp"
    break;

  case 48:
#line 513 "yacc_sql.y"
  {
    (yyval.is_null) = false;
  }
#line 2142 "yacc_sql.cpp"
    break;

  case 49:
#line 517 "yacc_sql.y"
  {
    (yyval.is_null) = true;
  }
#line 2150 "yacc_sql.cpp"
    break;

  case 50:
#line 523 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2156 "yacc_sql.cpp"
    break;

  case 51:
#line 528 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2162 "yacc_sql.cpp"
    break;

  case 52:
#line 529 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2168 "yacc_sql.cpp"
    break;

  case 53:
#line 530 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2174 "yacc_sql.cpp"
    break;

  case 54:
#line 531 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2180 "yacc_sql.cpp"
    break;

  case 55:
#line 536 "yacc_sql.y"
           { (yyval.func_t)=LENGTH_T; }
#line 2186 "yacc_sql.cpp"
    break;

  case 56:
#line 537 "yacc_sql.y"
                  { (yyval.func_t)=DATE_FORMAT_T; }
#line 2192 "yacc_sql.cpp"
    break;

  case 57:
#line 538 "yacc_sql.y"
            { (yyval.func_t)=ROUND_T; }
#line 2198 "yacc_sql.cpp"
    break;

  case 58:
#line 542 "yacc_sql.y"
                              {
      (yyval.expr_attr) = new RelAttrSqlNode;
      (yyval.expr_attr)->is_expr = true;
      (yyval.expr_attr)->expr = (yyvsp[-1].expression);
      (yyval.expr_attr)->alias = (yyvsp[0].string);
    }
#line 2209 "yacc_sql.cpp"
    break;

  case 59:
#line 551 "yacc_sql.y"
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
#line 2229 "yacc_sql.cpp"
    break;

  case 60:
#line 568 "yacc_sql.y"
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
#line 2252 "yacc_sql.cpp"
    break;

  case 61:
#line 588 "yacc_sql.y"
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
#line 2271 "yacc_sql.cpp"
    break;

  case 62:
#line 604 "yacc_sql.y"
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
#line 2293 "yacc_sql.cpp"
    break;

  case 63:
#line 624 "yacc_sql.y"
        { (yyval.aggr_t)=MAX_T; }
#line 2299 "yacc_sql.cpp"
    break;

  case 64:
#line 625 "yacc_sql.y"
          { (yyval.aggr_t)=MIN_T; }
#line 2305 "yacc_sql.cpp"
    break;

  case 65:
#line 626 "yacc_sql.y"
          { (yyval.aggr_t)=AVG_T; }
#line 2311 "yacc_sql.cpp"
    break;

  case 66:
#line 627 "yacc_sql.y"
          { (yyval.aggr_t)=SUM_T; }
#line 2317 "yacc_sql.cpp"
    break;

  case 67:
#line 628 "yacc_sql.y"
            { (yyval.aggr_t)=COUNT_T; }
#line 2323 "yacc_sql.cpp"
    break;

  case 68:
#line 633 "yacc_sql.y"
    {
      (yyval.aggr_func) = new RelAttrSqlNode;
      (yyval.aggr_func)->is_aggr = true;
      (yyval.aggr_func)->aggr_type = (yyvsp[-3].aggr_t);
      (yyval.aggr_func)->attribute_name = (yyvsp[-1].string);
      free((yyvsp[-1].string));
    }
#line 2335 "yacc_sql.cpp"
    break;

  case 69:
#line 640 "yacc_sql.y"
                                        {
      (yyval.aggr_func) = new RelAttrSqlNode;
      (yyval.aggr_func)->is_aggr = true;
      (yyval.aggr_func)->aggr_type = (yyvsp[-5].aggr_t);
      (yyval.aggr_func)->relation_name  = (yyvsp[-3].string);
      (yyval.aggr_func)->attribute_name = (yyvsp[-1].string);
      free((yyvsp[-3].string));
      free((yyvsp[-1].string));

		}
#line 2350 "yacc_sql.cpp"
    break;

  case 70:
#line 650 "yacc_sql.y"
                                              {
      (yyval.aggr_func) = new RelAttrSqlNode;
      (yyval.aggr_func)->is_aggr = true;
      (yyval.aggr_func)->aggr_type = (yyvsp[-3].aggr_t);
      (yyval.aggr_func)->attribute_name = "*";

		}
#line 2362 "yacc_sql.cpp"
    break;

  case 71:
#line 661 "yacc_sql.y"
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
#line 2388 "yacc_sql.cpp"
    break;

  case 72:
#line 685 "yacc_sql.y"
  {
    (yyval.insert_list) = nullptr;
  }
#line 2396 "yacc_sql.cpp"
    break;

  case 73:
#line 689 "yacc_sql.y"
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
#line 2417 "yacc_sql.cpp"
    break;

  case 74:
#line 709 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2425 "yacc_sql.cpp"
    break;

  case 75:
#line 712 "yacc_sql.y"
                                 {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2439 "yacc_sql.cpp"
    break;

  case 76:
#line 725 "yacc_sql.y"
    {
      (yyval.value) = (yyvsp[0].value);
    }
#line 2447 "yacc_sql.cpp"
    break;

  case 77:
#line 730 "yacc_sql.y"
    {
      (yyval.value) = (yyvsp[0].value);
    }
#line 2455 "yacc_sql.cpp"
    break;

  case 78:
#line 734 "yacc_sql.y"
                            {
      (yyval.value) = new Value(0-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2464 "yacc_sql.cpp"
    break;

  case 79:
#line 738 "yacc_sql.y"
               {
      (yyval.value) = new Value(0-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2473 "yacc_sql.cpp"
    break;

  case 80:
#line 744 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2482 "yacc_sql.cpp"
    break;

  case 81:
#line 748 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2491 "yacc_sql.cpp"
    break;

  case 82:
#line 752 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2501 "yacc_sql.cpp"
    break;

  case 83:
#line 757 "yacc_sql.y"
            {
      (yyval.value) = new Value(); // UNDEFINED TYPE HERE
      (yyval.value)->set_null();
    }
#line 2510 "yacc_sql.cpp"
    break;

  case 84:
#line 765 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2524 "yacc_sql.cpp"
    break;

  case 85:
#line 778 "yacc_sql.y"
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
#line 2547 "yacc_sql.cpp"
    break;

  case 86:
#line 799 "yacc_sql.y"
  {
    (yyval.update_pair) = new UpdateListSqlNode{(yyvsp[-2].string), *(yyvsp[0].value), SelectSqlNode{}, false};
    free((yyvsp[0].value));
  }
#line 2556 "yacc_sql.cpp"
    break;

  case 87:
#line 804 "yacc_sql.y"
  {
    (yyval.update_pair) = new UpdateListSqlNode{(yyvsp[-4].string), Value{}, *(yyvsp[-1].select_body), true};
    free((yyvsp[-1].select_body));
  }
#line 2565 "yacc_sql.cpp"
    break;

  case 88:
#line 810 "yacc_sql.y"
    {
      (yyval.update_list) = nullptr;
    }
#line 2573 "yacc_sql.cpp"
    break;

  case 89:
#line 814 "yacc_sql.y"
    {
      if ((yyvsp[0].update_list) != nullptr) {
        (yyval.update_list) = (yyvsp[0].update_list);
      } else {
        (yyval.update_list) = new std::vector<UpdateListSqlNode>;
      }

      (yyval.update_list)->emplace_back(*(yyvsp[-1].update_pair));
      free((yyvsp[-1].update_pair));
    }
#line 2588 "yacc_sql.cpp"
    break;

  case 90:
#line 829 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      (yyval.sql_node)->selection = *(yyvsp[0].select_body);
      delete (yyvsp[0].select_body);
    }
#line 2598 "yacc_sql.cpp"
    break;

  case 91:
#line 839 "yacc_sql.y"
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
#line 2651 "yacc_sql.cpp"
    break;

  case 92:
#line 888 "yacc_sql.y"
    {
      (yyval.select_body) = new SelectSqlNode;
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.select_body)->attributes.swap(*(yyvsp[0].rel_attr_list));
        delete (yyvsp[0].rel_attr_list);
      }
      (yyval.select_body)->attributes.emplace_back(*(yyvsp[-1].expr_attr));
      free((yyvsp[-1].expr_attr));
    }
#line 2665 "yacc_sql.cpp"
    break;

  case 93:
#line 901 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2676 "yacc_sql.cpp"
    break;

  case 94:
#line 911 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2685 "yacc_sql.cpp"
    break;

  case 95:
#line 916 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2698 "yacc_sql.cpp"
    break;

  case 96:
#line 927 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
      LOG_DEBUG("ADD");
    }
#line 2707 "yacc_sql.cpp"
    break;

  case 97:
#line 931 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
      LOG_DEBUG("SUB");
    }
#line 2716 "yacc_sql.cpp"
    break;

  case 98:
#line 935 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
      LOG_DEBUG("MUL");
    }
#line 2725 "yacc_sql.cpp"
    break;

  case 99:
#line 939 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
      LOG_DEBUG("DIV");
    }
#line 2734 "yacc_sql.cpp"
    break;

  case 100:
#line 943 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      LOG_DEBUG("()");
    }
#line 2744 "yacc_sql.cpp"
    break;

  case 101:
#line 948 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
      LOG_DEBUG("-");
    }
#line 2753 "yacc_sql.cpp"
    break;

  case 102:
#line 952 "yacc_sql.y"
               {
      (yyval.expression) = new FieldExpr(*(yyvsp[0].rel_attr));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2763 "yacc_sql.cpp"
    break;

  case 103:
#line 957 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2773 "yacc_sql.cpp"
    break;

  case 104:
#line 962 "yacc_sql.y"
                {
      (yyval.expression) = new AggregateExpr(*(yyvsp[0].aggr_func));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].aggr_func);
    }
#line 2783 "yacc_sql.cpp"
    break;

  case 105:
#line 967 "yacc_sql.y"
                  {
      (yyval.expression) = new FunctionExpr(*(yyvsp[0].normal_func));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].normal_func);
    }
#line 2793 "yacc_sql.cpp"
    break;

  case 106:
#line 976 "yacc_sql.y"
        {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      attr.expr = new FieldExpr("*");
      attr.is_expr = true;
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 2807 "yacc_sql.cpp"
    break;

  case 107:
#line 985 "yacc_sql.y"
                          {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].expr_attr));
      delete (yyvsp[-1].expr_attr);
    }
#line 2821 "yacc_sql.cpp"
    break;

  case 108:
#line 997 "yacc_sql.y"
    {
      (yyval.string) = strdup("");
    }
#line 2829 "yacc_sql.cpp"
    break;

  case 109:
#line 1001 "yacc_sql.y"
    {
      (yyval.string) = strdup((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2838 "yacc_sql.cpp"
    break;

  case 110:
#line 1005 "yacc_sql.y"
            {
      (yyval.string) = strdup((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2847 "yacc_sql.cpp"
    break;

  case 111:
#line 1009 "yacc_sql.y"
             {
      (yyval.string) = strdup("sum");
    }
#line 2855 "yacc_sql.cpp"
    break;

  case 112:
#line 1015 "yacc_sql.y"
              {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->is_aggr = false;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      (yyval.rel_attr)->alias = "";
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2869 "yacc_sql.cpp"
    break;

  case 113:
#line 1024 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->is_aggr = false;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = '*';
      free((yyvsp[-2].string));
    }
#line 2881 "yacc_sql.cpp"
    break;

  case 114:
#line 1031 "yacc_sql.y"
         {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->is_aggr = false;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      (yyval.rel_attr)->alias = "";
      free((yyvsp[0].string));
    }
#line 2893 "yacc_sql.cpp"
    break;

  case 115:
#line 1042 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2901 "yacc_sql.cpp"
    break;

  case 116:
#line 1045 "yacc_sql.y"
                                {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }

      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].expr_attr));
      delete (yyvsp[-1].expr_attr);
    }
#line 2916 "yacc_sql.cpp"
    break;

  case 117:
#line 1059 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2924 "yacc_sql.cpp"
    break;

  case 118:
#line 1062 "yacc_sql.y"
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
#line 2940 "yacc_sql.cpp"
    break;

  case 119:
#line 1076 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2948 "yacc_sql.cpp"
    break;

  case 120:
#line 1080 "yacc_sql.y"
    {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 2956 "yacc_sql.cpp"
    break;

  case 121:
#line 1086 "yacc_sql.y"
    {
      (yyval.order_t) = ASC_T;
    }
#line 2964 "yacc_sql.cpp"
    break;

  case 122:
#line 1091 "yacc_sql.y"
    {
      (yyval.order_t) = ASC_T;
    }
#line 2972 "yacc_sql.cpp"
    break;

  case 123:
#line 1096 "yacc_sql.y"
    {
      (yyval.order_t) = DESC_T;
    }
#line 2980 "yacc_sql.cpp"
    break;

  case 124:
#line 1103 "yacc_sql.y"
    {
        (yyval.order_by_attr) = new OrderBySqlNode;
        (yyval.order_by_attr)->attr = *(yyvsp[-1].rel_attr);
        (yyval.order_by_attr)->order_type = (yyvsp[0].order_t);
        delete (yyvsp[-1].rel_attr);
    }
#line 2991 "yacc_sql.cpp"
    break;

  case 125:
#line 1113 "yacc_sql.y"
    {
      (yyval.order_by_list) = new std::vector<OrderBySqlNode>;
      (yyval.order_by_list)->emplace_back(*(yyvsp[0].order_by_attr));
      delete (yyvsp[0].order_by_attr);
    }
#line 3001 "yacc_sql.cpp"
    break;

  case 126:
#line 1118 "yacc_sql.y"
                                        {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
      (yyval.order_by_list)->emplace_back(*(yyvsp[-2].order_by_attr));
      delete (yyvsp[-2].order_by_attr);
    }
#line 3011 "yacc_sql.cpp"
    break;

  case 127:
#line 1127 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3019 "yacc_sql.cpp"
    break;

  case 128:
#line 1130 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3027 "yacc_sql.cpp"
    break;

  case 129:
#line 1138 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3035 "yacc_sql.cpp"
    break;

  case 130:
#line 1141 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3043 "yacc_sql.cpp"
    break;

  case 131:
#line 1147 "yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 3051 "yacc_sql.cpp"
    break;

  case 132:
#line 1150 "yacc_sql.y"
                                   {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].expr_attr));
      delete (yyvsp[-1].expr_attr);
    }
#line 3065 "yacc_sql.cpp"
    break;

  case 133:
#line 1162 "yacc_sql.y"
    {
      (yyval.inner_join_list) = nullptr;
    }
#line 3073 "yacc_sql.cpp"
    break;

  case 134:
#line 1165 "yacc_sql.y"
                                 {
      if ((yyvsp[0].inner_join_list) != nullptr) {
        (yyval.inner_join_list) = (yyvsp[0].inner_join_list);
      } else {
        (yyval.inner_join_list) = new std::vector<InnerJoinSqlNode>;
      }
      (yyval.inner_join_list)->emplace_back(*(yyvsp[-1].inner_join));
      delete (yyvsp[-1].inner_join);
    }
#line 3087 "yacc_sql.cpp"
    break;

  case 135:
#line 1177 "yacc_sql.y"
                                         {
      (yyval.inner_join) = new InnerJoinSqlNode;
      (yyval.inner_join)->relation_name = (yyvsp[-2].string);
      (yyval.inner_join)->join_conditions.swap(*(yyvsp[0].condition_list));
      delete (yyvsp[0].condition_list);
    }
#line 3098 "yacc_sql.cpp"
    break;

  case 136:
#line 1187 "yacc_sql.y"
    {
      (yyval.condition) = (yyvsp[0].condition);
    }
#line 3106 "yacc_sql.cpp"
    break;

  case 137:
#line 1193 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3114 "yacc_sql.cpp"
    break;

  case 138:
#line 1197 "yacc_sql.y"
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3124 "yacc_sql.cpp"
    break;

  case 139:
#line 1202 "yacc_sql.y"
                                             {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3134 "yacc_sql.cpp"
    break;

  case 140:
#line 1211 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3142 "yacc_sql.cpp"
    break;

  case 141:
#line 1215 "yacc_sql.y"
    {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3152 "yacc_sql.cpp"
    break;

  case 142:
#line 1220 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3162 "yacc_sql.cpp"
    break;

  case 143:
#line 1225 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyvsp[-2].condition)->is_and = false;
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3173 "yacc_sql.cpp"
    break;

  case 144:
#line 1235 "yacc_sql.y"
                      {
      (yyval.value_list) = new std::vector<Value>;
      (yyval.value_list)->emplace_back(*(yyvsp[-2].value));
      (yyval.value_list)->emplace_back(*(yyvsp[0].value));
      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
    }
#line 3185 "yacc_sql.cpp"
    break;

  case 145:
#line 1242 "yacc_sql.y"
                                   {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-2].value));
      delete (yyvsp[-2].value);
    }
#line 3199 "yacc_sql.cpp"
    break;

  case 146:
#line 1254 "yacc_sql.y"
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
#line 3215 "yacc_sql.cpp"
    break;

  case 147:
#line 1266 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-4].expr_attr);
      (yyval.condition)->right_is_select = 1;
      (yyval.condition)->right_select = (yyvsp[-1].select_body);
      (yyval.condition)->comp = (yyvsp[-3].comp);
      delete (yyvsp[-4].expr_attr);
    }
#line 3229 "yacc_sql.cpp"
    break;

  case 148:
#line 1276 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_select = 1;
      (yyval.condition)->left_select = (yyvsp[-3].select_body);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].expr_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      delete (yyvsp[0].expr_attr);
    }
#line 3243 "yacc_sql.cpp"
    break;

  case 149:
#line 1286 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_select = 1;
      (yyval.condition)->left_select = (yyvsp[-5].select_body);
      (yyval.condition)->right_is_select = 1;
      (yyval.condition)->right_select = (yyvsp[-1].select_body);
      (yyval.condition)->comp = (yyvsp[-3].comp);
    }
#line 3256 "yacc_sql.cpp"
    break;

  case 150:
#line 1295 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_select = 0;
      (yyval.condition)->right_is_select = 1;
      (yyval.condition)->right_select = (yyvsp[-1].select_body);
      (yyval.condition)->comp = (yyvsp[-3].comp);
      (yyval.condition)->unary_op = 1;
    }
#line 3269 "yacc_sql.cpp"
    break;

  case 151:
#line 1304 "yacc_sql.y"
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
#line 3284 "yacc_sql.cpp"
    break;

  case 152:
#line 1317 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3290 "yacc_sql.cpp"
    break;

  case 153:
#line 1318 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3296 "yacc_sql.cpp"
    break;

  case 154:
#line 1319 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3302 "yacc_sql.cpp"
    break;

  case 155:
#line 1320 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3308 "yacc_sql.cpp"
    break;

  case 156:
#line 1321 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3314 "yacc_sql.cpp"
    break;

  case 157:
#line 1322 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3320 "yacc_sql.cpp"
    break;

  case 158:
#line 1323 "yacc_sql.y"
           { (yyval.comp) = STR_LIKE; }
#line 3326 "yacc_sql.cpp"
    break;

  case 159:
#line 1324 "yacc_sql.y"
               { (yyval.comp) = STR_NOT_LIKE; }
#line 3332 "yacc_sql.cpp"
    break;

  case 160:
#line 1325 "yacc_sql.y"
           { (yyval.comp) = IS; }
#line 3338 "yacc_sql.cpp"
    break;

  case 161:
#line 1326 "yacc_sql.y"
               { (yyval.comp) = IS_NOT; }
#line 3344 "yacc_sql.cpp"
    break;

  case 162:
#line 1327 "yacc_sql.y"
           { (yyval.comp) = IN; }
#line 3350 "yacc_sql.cpp"
    break;

  case 163:
#line 1328 "yacc_sql.y"
               { (yyval.comp) = IN_NOT; }
#line 3356 "yacc_sql.cpp"
    break;

  case 164:
#line 1329 "yacc_sql.y"
              { (yyval.comp) = EXIST; }
#line 3362 "yacc_sql.cpp"
    break;

  case 165:
#line 1330 "yacc_sql.y"
                  { (yyval.comp) = EXIST_NOT; }
#line 3368 "yacc_sql.cpp"
    break;

  case 166:
#line 1335 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);

      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3382 "yacc_sql.cpp"
    break;

  case 167:
#line 1348 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3391 "yacc_sql.cpp"
    break;

  case 168:
#line 1356 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3403 "yacc_sql.cpp"
    break;


#line 3407 "yacc_sql.cpp"

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
#line 1368 "yacc_sql.y"

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
