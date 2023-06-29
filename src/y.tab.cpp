/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "src\\parser.y"

#include <string.h>
#include "symtab.hpp"
#include <stdio.h>
int yylex(void);
void yyerror(const char* s);
#define ZERO(s) memset(&s, 0, sizeof(s))

// states of the parser
bool declare;

#line 83 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUM = 258,                     /* NUM  */
    DEC = 259,                     /* DEC  */
    ID = 260,                      /* ID  */
    STR = 261,                     /* STR  */
    SIZEOF = 262,                  /* SIZEOF  */
    PTR_OP = 263,                  /* PTR_OP  */
    INC_OP = 264,                  /* INC_OP  */
    DEC_OP = 265,                  /* DEC_OP  */
    SHL_OP = 266,                  /* SHL_OP  */
    SHR_OP = 267,                  /* SHR_OP  */
    LE_OP = 268,                   /* LE_OP  */
    GE_OP = 269,                   /* GE_OP  */
    EQ_OP = 270,                   /* EQ_OP  */
    NE_OP = 271,                   /* NE_OP  */
    LOGAND = 272,                  /* LOGAND  */
    LOGOR = 273,                   /* LOGOR  */
    MULASGN = 274,                 /* MULASGN  */
    DIVASGN = 275,                 /* DIVASGN  */
    MODASGN = 276,                 /* MODASGN  */
    ADDASGN = 277,                 /* ADDASGN  */
    SUBASGN = 278,                 /* SUBASGN  */
    SHLASGN = 279,                 /* SHLASGN  */
    SHRASGN = 280,                 /* SHRASGN  */
    ANDASGN = 281,                 /* ANDASGN  */
    ELLIPSIS = 282,                /* ELLIPSIS  */
    XORASGN = 283,                 /* XORASGN  */
    ORASGN = 284,                  /* ORASGN  */
    TYPEDEF = 285,                 /* TYPEDEF  */
    STATIC = 286,                  /* STATIC  */
    CONST = 287,                   /* CONST  */
    VOID = 288,                    /* VOID  */
    CHAR = 289,                    /* CHAR  */
    SHORT = 290,                   /* SHORT  */
    INT = 291,                     /* INT  */
    LONG = 292,                    /* LONG  */
    FLOAT = 293,                   /* FLOAT  */
    DOUBLE = 294,                  /* DOUBLE  */
    TYPE = 295,                    /* TYPE  */
    IF = 296,                      /* IF  */
    ELSE = 297,                    /* ELSE  */
    FOR = 298,                     /* FOR  */
    WHILE = 299,                   /* WHILE  */
    DO = 300,                      /* DO  */
    CONTINUE = 301,                /* CONTINUE  */
    BREAK = 302,                   /* BREAK  */
    RETURN = 303,                  /* RETURN  */
    GOTO = 304                     /* GOTO  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "src\\parser.y"

	long long ival;
	long double fval;
	const char* sval;

	struct {
		int type; 
		int specif; 
		const char* name; // valid only if type == TYPE_TYPDEF
	} decl_specif;

	initial_t initial;
	init_decl_t init_decl;
	init_decl_t* init_decl_list;

	param_t param;
	param_t* param_list;

#line 201 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_DEC = 4,                        /* DEC  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_STR = 6,                        /* STR  */
  YYSYMBOL_SIZEOF = 7,                     /* SIZEOF  */
  YYSYMBOL_PTR_OP = 8,                     /* PTR_OP  */
  YYSYMBOL_INC_OP = 9,                     /* INC_OP  */
  YYSYMBOL_DEC_OP = 10,                    /* DEC_OP  */
  YYSYMBOL_SHL_OP = 11,                    /* SHL_OP  */
  YYSYMBOL_SHR_OP = 12,                    /* SHR_OP  */
  YYSYMBOL_LE_OP = 13,                     /* LE_OP  */
  YYSYMBOL_GE_OP = 14,                     /* GE_OP  */
  YYSYMBOL_EQ_OP = 15,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 16,                     /* NE_OP  */
  YYSYMBOL_LOGAND = 17,                    /* LOGAND  */
  YYSYMBOL_LOGOR = 18,                     /* LOGOR  */
  YYSYMBOL_MULASGN = 19,                   /* MULASGN  */
  YYSYMBOL_DIVASGN = 20,                   /* DIVASGN  */
  YYSYMBOL_MODASGN = 21,                   /* MODASGN  */
  YYSYMBOL_ADDASGN = 22,                   /* ADDASGN  */
  YYSYMBOL_SUBASGN = 23,                   /* SUBASGN  */
  YYSYMBOL_SHLASGN = 24,                   /* SHLASGN  */
  YYSYMBOL_SHRASGN = 25,                   /* SHRASGN  */
  YYSYMBOL_ANDASGN = 26,                   /* ANDASGN  */
  YYSYMBOL_ELLIPSIS = 27,                  /* ELLIPSIS  */
  YYSYMBOL_XORASGN = 28,                   /* XORASGN  */
  YYSYMBOL_ORASGN = 29,                    /* ORASGN  */
  YYSYMBOL_TYPEDEF = 30,                   /* TYPEDEF  */
  YYSYMBOL_STATIC = 31,                    /* STATIC  */
  YYSYMBOL_CONST = 32,                     /* CONST  */
  YYSYMBOL_VOID = 33,                      /* VOID  */
  YYSYMBOL_CHAR = 34,                      /* CHAR  */
  YYSYMBOL_SHORT = 35,                     /* SHORT  */
  YYSYMBOL_INT = 36,                       /* INT  */
  YYSYMBOL_LONG = 37,                      /* LONG  */
  YYSYMBOL_FLOAT = 38,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 39,                    /* DOUBLE  */
  YYSYMBOL_TYPE = 40,                      /* TYPE  */
  YYSYMBOL_IF = 41,                        /* IF  */
  YYSYMBOL_ELSE = 42,                      /* ELSE  */
  YYSYMBOL_FOR = 43,                       /* FOR  */
  YYSYMBOL_WHILE = 44,                     /* WHILE  */
  YYSYMBOL_DO = 45,                        /* DO  */
  YYSYMBOL_CONTINUE = 46,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 47,                     /* BREAK  */
  YYSYMBOL_RETURN = 48,                    /* RETURN  */
  YYSYMBOL_GOTO = 49,                      /* GOTO  */
  YYSYMBOL_50_ = 50,                       /* '('  */
  YYSYMBOL_51_ = 51,                       /* ')'  */
  YYSYMBOL_52_ = 52,                       /* '['  */
  YYSYMBOL_53_ = 53,                       /* ']'  */
  YYSYMBOL_54_ = 54,                       /* '.'  */
  YYSYMBOL_55_ = 55,                       /* ','  */
  YYSYMBOL_56_ = 56,                       /* '&'  */
  YYSYMBOL_57_ = 57,                       /* '*'  */
  YYSYMBOL_58_ = 58,                       /* '+'  */
  YYSYMBOL_59_ = 59,                       /* '-'  */
  YYSYMBOL_60_ = 60,                       /* '~'  */
  YYSYMBOL_61_ = 61,                       /* '!'  */
  YYSYMBOL_62_ = 62,                       /* '/'  */
  YYSYMBOL_63_ = 63,                       /* '%'  */
  YYSYMBOL_64_ = 64,                       /* '<'  */
  YYSYMBOL_65_ = 65,                       /* '>'  */
  YYSYMBOL_66_ = 66,                       /* '^'  */
  YYSYMBOL_67_ = 67,                       /* '|'  */
  YYSYMBOL_68_ = 68,                       /* '?'  */
  YYSYMBOL_69_ = 69,                       /* ':'  */
  YYSYMBOL_70_ = 70,                       /* '='  */
  YYSYMBOL_71_ = 71,                       /* ';'  */
  YYSYMBOL_72_ = 72,                       /* '{'  */
  YYSYMBOL_73_ = 73,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 74,                  /* $accept  */
  YYSYMBOL_primary_expression = 75,        /* primary_expression  */
  YYSYMBOL_postfix_expression = 76,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 77,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 78,          /* unary_expression  */
  YYSYMBOL_unary_operator = 79,            /* unary_operator  */
  YYSYMBOL_cast_expression = 80,           /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 81, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 82,       /* additive_expression  */
  YYSYMBOL_shift_expression = 83,          /* shift_expression  */
  YYSYMBOL_relational_expression = 84,     /* relational_expression  */
  YYSYMBOL_equality_expression = 85,       /* equality_expression  */
  YYSYMBOL_and_expression = 86,            /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 87,   /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 88,   /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 89,    /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 90,     /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 91,    /* conditional_expression  */
  YYSYMBOL_assignment_expression = 92,     /* assignment_expression  */
  YYSYMBOL_assignment_operator = 93,       /* assignment_operator  */
  YYSYMBOL_expression = 94,                /* expression  */
  YYSYMBOL_declaration = 95,               /* declaration  */
  YYSYMBOL_declaration_specifiers = 96,    /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 97,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 98,           /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 99,   /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 100,           /* type_specifier  */
  YYSYMBOL_type_qualifier = 101,           /* type_qualifier  */
  YYSYMBOL_specifier_qualifier_list = 102, /* specifier_qualifier_list  */
  YYSYMBOL_declarator = 103,               /* declarator  */
  YYSYMBOL_direct_declarator = 104,        /* direct_declarator  */
  YYSYMBOL_pointer = 105,                  /* pointer  */
  YYSYMBOL_parameter_list = 106,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 107,    /* parameter_declaration  */
  YYSYMBOL_type_name = 108,                /* type_name  */
  YYSYMBOL_initializer = 109,              /* initializer  */
  YYSYMBOL_initializer_list = 110,         /* initializer_list  */
  YYSYMBOL_statement = 111,                /* statement  */
  YYSYMBOL_labeled_statement = 112,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 113,       /* compound_statement  */
  YYSYMBOL_block_item_list = 114,          /* block_item_list  */
  YYSYMBOL_block_item = 115,               /* block_item  */
  YYSYMBOL_expression_statement = 116,     /* expression_statement  */
  YYSYMBOL_selection_statement = 117,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 118,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 119,           /* jump_statement  */
  YYSYMBOL_translation_unit = 120,         /* translation_unit  */
  YYSYMBOL_external_declaration = 121,     /* external_declaration  */
  YYSYMBOL_function_definition = 122       /* function_definition  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_uint8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  28
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   723

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  154
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  252

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   304


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    61,     2,     2,     2,    63,    56,     2,
      50,    51,    57,    58,    55,    59,    54,    62,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    69,    71,
      64,    70,    65,    68,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    52,     2,    53,    66,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,    67,    73,    60,     2,     2,     2,
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
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    67,    67,    68,    69,    70,    71,    75,    76,    77,
      78,    79,    80,    81,    82,    86,    87,    91,    92,    93,
      94,    95,    96,   100,   101,   102,   103,   104,   105,   109,
     110,   114,   115,   116,   117,   121,   122,   123,   127,   128,
     129,   133,   134,   135,   136,   137,   141,   142,   143,   147,
     148,   152,   153,   157,   158,   162,   163,   167,   168,   172,
     173,   177,   178,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   196,   197,   201,   288,   289,   299,
     300,   311,   312,   325,   330,   344,   345,   352,   353,   357,
     358,   359,   360,   361,   362,   366,   370,   371,   372,   373,
     376,   377,   381,   382,   383,   384,   393,   403,   417,   418,
     422,   431,   445,   457,   464,   473,   474,   478,   479,   480,
     484,   485,   489,   490,   491,   492,   493,   494,   498,   502,
     503,   507,   508,   512,   513,   517,   518,   522,   523,   527,
     528,   529,   530,   531,   532,   536,   537,   538,   539,   540,
     544,   545,   549,   550,   554
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "DEC", "ID",
  "STR", "SIZEOF", "PTR_OP", "INC_OP", "DEC_OP", "SHL_OP", "SHR_OP",
  "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "LOGAND", "LOGOR", "MULASGN",
  "DIVASGN", "MODASGN", "ADDASGN", "SUBASGN", "SHLASGN", "SHRASGN",
  "ANDASGN", "ELLIPSIS", "XORASGN", "ORASGN", "TYPEDEF", "STATIC", "CONST",
  "VOID", "CHAR", "SHORT", "INT", "LONG", "FLOAT", "DOUBLE", "TYPE", "IF",
  "ELSE", "FOR", "WHILE", "DO", "CONTINUE", "BREAK", "RETURN", "GOTO",
  "'('", "')'", "'['", "']'", "'.'", "','", "'&'", "'*'", "'+'", "'-'",
  "'~'", "'!'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'", "':'",
  "'='", "';'", "'{'", "'}'", "$accept", "primary_expression",
  "postfix_expression", "argument_expression_list", "unary_expression",
  "unary_operator", "cast_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "expression",
  "declaration", "declaration_specifiers", "init_declarator_list",
  "init_declarator", "storage_class_specifier", "type_specifier",
  "type_qualifier", "specifier_qualifier_list", "declarator",
  "direct_declarator", "pointer", "parameter_list",
  "parameter_declaration", "type_name", "initializer", "initializer_list",
  "statement", "labeled_statement", "compound_statement",
  "block_item_list", "block_item", "expression_statement",
  "selection_statement", "iteration_statement", "jump_statement",
  "translation_unit", "external_declaration", "function_definition", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-147)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     446,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,     9,  -147,  -147,  -147,   183,  -147,  -147,  -147,   -41,
      -8,  -147,  -147,  -147,  -147,   -18,    29,     8,  -147,  -147,
    -147,    15,  -147,   338,   202,  -147,   323,   506,    29,  -147,
     -49,  -147,  -147,  -147,  -147,   603,   624,   624,   494,  -147,
    -147,  -147,  -147,  -147,  -147,   338,  -147,   136,     7,   662,
    -147,    -7,    54,   128,     5,   149,    -5,    10,   -19,    72,
      -6,  -147,  -147,  -147,    41,    91,    93,   101,   321,    32,
      85,   413,   161,  -147,  -147,  -147,     3,  -147,     9,  -147,
    -147,  -147,   261,  -147,  -147,  -147,  -147,  -147,  -147,     9,
      27,  -147,  -147,   115,   494,  -147,   662,  -147,  -147,    36,
     485,   485,   -41,   119,  -147,    -2,   170,  -147,  -147,   532,
     662,   180,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,   662,  -147,  -147,   662,   662,   662,   662,
     662,   662,   662,   662,   662,   662,   662,   662,   662,   662,
     662,   662,   662,   662,   662,   321,   662,   397,   662,   145,
    -147,  -147,  -147,    12,   126,   662,  -147,  -147,  -147,  -147,
       8,  -147,   659,  -147,   151,  -147,  -147,  -147,  -147,   662,
     279,  -147,  -147,  -147,    50,  -147,    35,  -147,  -147,  -147,
    -147,  -147,    -7,    -7,    54,    54,   128,   128,   128,   128,
       5,     5,   149,    -5,    10,   -19,    72,     6,  -147,    51,
     435,   435,    53,   153,  -147,  -147,  -147,   159,  -147,  -147,
    -147,  -147,  -147,  -147,   662,  -147,   662,   321,   565,   591,
     321,   662,  -147,  -147,  -147,   179,   321,    87,   321,    99,
    -147,   107,   321,  -147,   321,  -147,   321,   154,  -147,  -147,
    -147,  -147
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    87,    88,    95,    89,    90,    91,    92,    93,    94,
     153,     0,    77,    79,    81,     0,   150,   152,   102,   108,
       0,    83,    78,    80,    82,    85,   101,     0,     1,   151,
     109,     0,    76,     0,     0,   154,     0,     0,   100,    84,
      85,     3,     4,     2,     5,     0,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     7,    17,    29,     0,
      31,    35,    38,    41,    46,    49,    51,    53,    55,    57,
      59,    61,   117,    86,     2,     0,     0,     0,     0,     0,
       0,     0,     0,   135,   129,    74,     0,   133,     0,   134,
     122,   123,     0,   131,   124,   125,   126,   127,   105,   114,
       0,   110,   103,     0,     0,    21,     0,    18,    19,     0,
      96,    98,   115,     0,   120,     0,     0,    13,    14,     0,
       0,     0,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    63,     0,    29,    20,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     146,   147,   148,     0,     0,     0,   136,   130,   132,   112,
     113,   106,     0,   104,     0,     6,    97,    99,   116,     0,
       0,   118,    12,     9,     0,    15,     0,    11,    62,    32,
      33,    34,    36,    37,    39,    40,    44,    45,    42,    43,
      47,    48,    50,    52,    54,    56,    58,     0,   128,     0,
       0,     0,     0,     0,   149,   145,    75,     0,   111,    22,
      30,   119,   121,    10,     0,     8,     0,     0,     0,     0,
       0,     0,   107,    16,    60,   137,     0,     0,     0,     0,
     139,     0,     0,   143,     0,   141,     0,     0,   138,   144,
     142,   140
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -147,  -147,  -147,  -147,   -22,  -147,   -44,    33,    52,    34,
      48,    73,    74,    75,    76,    77,  -147,     1,   -33,  -147,
     -47,   -24,     2,  -147,   198,    -4,    49,    88,    90,    -3,
     -21,   -14,  -147,    59,   137,   -46,  -147,   -75,  -147,   215,
    -147,   152,  -146,  -147,  -147,  -147,  -147,   238,  -147
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    56,    57,   184,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    85,   133,
      86,    10,    88,    20,    21,    12,    13,    14,   112,    40,
      26,    27,   100,   101,   113,    73,   115,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    15,    16,    17
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      72,   109,    11,   159,   103,    30,    38,    22,    25,   114,
      87,   211,   153,    18,    18,   135,    19,    11,   143,   144,
      18,    33,    72,   105,   107,   108,   122,   123,   124,   125,
     126,   127,   128,   129,   163,   130,   131,   134,    99,     1,
       2,     3,     4,     5,     6,     7,     8,    31,   151,     9,
     136,   149,    33,   180,    34,   137,   138,   109,   165,   109,
      23,   165,   154,    32,   228,   229,    19,   165,    87,   145,
     146,   181,    19,   186,   166,   226,   150,   132,   171,    36,
     208,    37,   172,   214,    22,   170,   185,   175,   225,   152,
     165,   165,   189,   190,   191,    22,   169,   110,   178,    24,
     188,   223,   227,   160,   230,   224,   165,   207,   165,   209,
     155,   212,   139,   140,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   216,   210,   222,   220,   111,    23,   244,   141,
     142,   156,   165,   157,   116,   117,   118,    72,    23,    38,
     246,   158,   235,   110,   165,   240,   161,   134,   247,   110,
     110,   243,   165,   245,   147,   148,   164,   248,   173,   249,
     179,   250,   192,   193,    99,   182,    24,   196,   197,   198,
     199,   237,   239,    28,   241,   187,   119,    24,   120,   213,
     121,   233,   111,   194,   195,   200,   201,   215,   111,   111,
     176,   177,   219,   231,   134,    41,    42,    74,    44,    45,
     232,    46,    47,     1,     2,     3,     4,     5,     6,     7,
       8,   242,   202,     9,   203,   251,   204,   234,   205,    39,
     206,   218,     1,     2,     3,     4,     5,     6,     7,     8,
      35,   174,     9,    75,   168,    76,    77,    78,    79,    80,
      81,    82,    48,    29,     0,     0,     0,     0,    49,    50,
      51,    52,    53,    54,    41,    42,    74,    44,    45,     0,
      46,    47,     0,    83,    34,    84,     0,     0,     0,     0,
       0,     0,    41,    42,    43,    44,    45,     0,    46,    47,
       0,     1,     2,     3,     4,     5,     6,     7,     8,     0,
       0,     9,    75,     0,    76,    77,    78,    79,    80,    81,
      82,    48,     0,     0,     0,     0,     0,    49,    50,    51,
      52,    53,    54,     0,    41,    42,    74,    44,    45,    48,
      46,    47,    83,    34,   167,    49,    50,    51,    52,    53,
      54,    41,    42,    43,    44,    45,     0,    46,    47,     0,
       0,    55,   221,     1,     2,     3,     4,     5,     6,     7,
       8,     0,    75,     9,    76,    77,    78,    79,    80,    81,
      82,    48,     0,     0,    98,     0,     0,    49,    50,    51,
      52,    53,    54,     0,     0,     0,     0,     0,    48,     0,
       0,     0,    83,    34,    49,    50,    51,    52,    53,    54,
      41,    42,    43,    44,    45,     0,    46,    47,     0,     0,
      55,     0,     0,     0,     0,     0,    41,    42,    43,    44,
      45,     0,    46,    47,     0,     0,     0,     1,     2,     3,
       4,     5,     6,     7,     8,     0,     0,     9,    41,    42,
      43,    44,    45,     0,    46,    47,     0,    48,     0,     0,
       0,     0,     0,    49,    50,    51,    52,    53,    54,     0,
       0,     0,     0,    48,     0,     0,     0,     0,    83,    49,
      50,    51,    52,    53,    54,     0,     1,     2,     3,     4,
       5,     6,     7,     8,   162,    48,     9,     0,     0,     0,
       0,    49,    50,    51,    52,    53,    54,    41,    42,    43,
      44,    45,     0,    46,    47,     0,    83,     0,     0,    41,
      42,    43,    44,    45,     0,    46,    47,     3,     4,     5,
       6,     7,     8,     0,     0,     9,     3,     4,     5,     6,
       7,     8,     0,     0,     9,    41,    42,    43,    44,    45,
       0,    46,    47,     0,    48,     0,     0,     0,     0,     0,
      49,    50,    51,    52,    53,    54,    48,     0,     0,   102,
       0,     0,    49,    50,    51,    52,    53,    54,    41,    42,
      43,    44,    45,     0,    46,    47,     0,     0,     0,     0,
       0,     0,    48,   183,     0,     0,     0,     0,    49,    50,
      51,    52,    53,    54,    41,    42,    43,    44,    45,     0,
      46,    47,     0,     0,     0,     0,    41,    42,    43,    44,
      45,     0,    46,    47,     0,    48,   236,     0,     0,     0,
       0,    49,    50,    51,    52,    53,    54,    41,    42,    43,
      44,    45,     0,    46,    47,     0,     0,     0,     0,     0,
       0,    48,   238,     0,     0,     0,     0,    49,    50,    51,
      52,    53,    54,   104,     0,     0,     0,     0,     0,    49,
      50,    51,    52,    53,    54,    41,    42,    43,    44,    45,
       0,    46,    47,     0,   106,     0,     0,     0,     0,     0,
      49,    50,    51,    52,    53,    54,   217,     0,     0,     1,
       2,     3,     4,     5,     6,     7,     8,     0,     0,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    48,     0,     0,     0,     0,     0,    49,    50,
      51,    52,    53,    54
};

static const yytype_int16 yycheck[] =
{
      33,    48,     0,    78,    37,    19,    27,    11,    11,    55,
      34,   157,    18,     5,     5,    59,    57,    15,    13,    14,
       5,    70,    55,    45,    46,    47,    19,    20,    21,    22,
      23,    24,    25,    26,    81,    28,    29,    59,    36,    30,
      31,    32,    33,    34,    35,    36,    37,    55,    67,    40,
      57,    56,    70,    55,    72,    62,    63,   104,    55,   106,
      11,    55,    68,    71,   210,   211,    57,    55,    92,    64,
      65,    73,    57,   120,    71,    69,    66,    70,    51,    50,
     155,    52,    55,    71,    88,    99,   119,    51,    53,    17,
      55,    55,   136,   137,   138,    99,    99,    48,   112,    11,
     133,    51,    51,    71,    51,    55,    55,   154,    55,   156,
      69,   158,    58,    59,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   165,   157,   180,   179,    48,    88,    51,    11,
      12,    50,    55,    50,     8,     9,    10,   180,    99,   170,
      51,    50,   227,   104,    55,   230,    71,   179,    51,   110,
     111,   236,    55,   238,    15,    16,     5,   242,    53,   244,
      51,   246,   139,   140,   172,     5,    88,   143,   144,   145,
     146,   228,   229,     0,   231,     5,    50,    99,    52,    44,
      54,   224,   104,   141,   142,   147,   148,    71,   110,   111,
     110,   111,    51,    50,   226,     3,     4,     5,     6,     7,
      51,     9,    10,    30,    31,    32,    33,    34,    35,    36,
      37,    42,   149,    40,   150,    71,   151,   226,   152,    31,
     153,   172,    30,    31,    32,    33,    34,    35,    36,    37,
      25,   104,    40,    41,    92,    43,    44,    45,    46,    47,
      48,    49,    50,    15,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,     3,     4,     5,     6,     7,    -1,
       9,    10,    -1,    71,    72,    73,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,    -1,     9,    10,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      -1,    40,    41,    -1,    43,    44,    45,    46,    47,    48,
      49,    50,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,    -1,     3,     4,     5,     6,     7,    50,
       9,    10,    71,    72,    73,    56,    57,    58,    59,    60,
      61,     3,     4,     5,     6,     7,    -1,     9,    10,    -1,
      -1,    72,    73,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    41,    40,    43,    44,    45,    46,    47,    48,
      49,    50,    -1,    -1,    51,    -1,    -1,    56,    57,    58,
      59,    60,    61,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      -1,    -1,    71,    72,    56,    57,    58,    59,    60,    61,
       3,     4,     5,     6,     7,    -1,     9,    10,    -1,    -1,
      72,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,    -1,     9,    10,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    40,     3,     4,
       5,     6,     7,    -1,     9,    10,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    56,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    71,    56,
      57,    58,    59,    60,    61,    -1,    30,    31,    32,    33,
      34,    35,    36,    37,    71,    50,    40,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    61,     3,     4,     5,
       6,     7,    -1,     9,    10,    -1,    71,    -1,    -1,     3,
       4,     5,     6,     7,    -1,     9,    10,    32,    33,    34,
      35,    36,    37,    -1,    -1,    40,    32,    33,    34,    35,
      36,    37,    -1,    -1,    40,     3,     4,     5,     6,     7,
      -1,     9,    10,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    50,    -1,    -1,    53,
      -1,    -1,    56,    57,    58,    59,    60,    61,     3,     4,
       5,     6,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    51,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,     3,     4,     5,     6,     7,    -1,
       9,    10,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,    -1,     9,    10,    -1,    50,    51,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    61,     3,     4,     5,
       6,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,    50,    -1,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    61,     3,     4,     5,     6,     7,
      -1,     9,    10,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    27,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    30,    31,    32,    33,    34,    35,    36,    37,    40,
      95,    96,    99,   100,   101,   120,   121,   122,     5,    57,
      97,    98,    99,   100,   101,   103,   104,   105,     0,   121,
     105,    55,    71,    70,    72,   113,    50,    52,   104,    98,
     103,     3,     4,     5,     6,     7,     9,    10,    50,    56,
      57,    58,    59,    60,    61,    72,    75,    76,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,   109,     5,    41,    43,    44,    45,    46,
      47,    48,    49,    71,    73,    92,    94,    95,    96,   111,
     112,   113,   114,   115,   116,   117,   118,   119,    51,    96,
     106,   107,    53,    92,    50,    78,    50,    78,    78,    94,
     100,   101,   102,   108,   109,   110,     8,     9,    10,    50,
      52,    54,    19,    20,    21,    22,    23,    24,    25,    26,
      28,    29,    70,    93,    78,    80,    57,    62,    63,    58,
      59,    11,    12,    13,    14,    64,    65,    15,    16,    56,
      66,    67,    17,    18,    68,    69,    50,    50,    50,   111,
      71,    71,    71,    94,     5,    55,    71,    73,   115,   103,
     105,    51,    55,    53,   108,    51,   102,   102,   105,    51,
      55,    73,     5,    51,    77,    92,    94,     5,    92,    80,
      80,    80,    81,    81,    82,    82,    83,    83,    83,    83,
      84,    84,    85,    86,    87,    88,    89,    94,   111,    94,
      95,   116,    94,    44,    71,    71,    92,    27,   107,    51,
      80,    73,   109,    51,    55,    53,    69,    51,   116,   116,
      51,    50,    51,    92,    91,   111,    51,    94,    51,    94,
     111,    94,    42,   111,    51,   111,    51,    51,   111,   111,
     111,    71
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    74,    75,    75,    75,    75,    75,    76,    76,    76,
      76,    76,    76,    76,    76,    77,    77,    78,    78,    78,
      78,    78,    78,    79,    79,    79,    79,    79,    79,    80,
      80,    81,    81,    81,    81,    82,    82,    82,    83,    83,
      83,    84,    84,    84,    84,    84,    85,    85,    85,    86,
      86,    87,    87,    88,    88,    89,    89,    90,    90,    91,
      91,    92,    92,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    94,    94,    95,    96,    96,    96,
      96,    96,    96,    97,    97,    98,    98,    99,    99,   100,
     100,   100,   100,   100,   100,   101,   102,   102,   102,   102,
     103,   103,   104,   104,   104,   104,   104,   104,   105,   105,
     106,   106,   107,   107,   107,   108,   108,   109,   109,   109,
     110,   110,   111,   111,   111,   111,   111,   111,   112,   113,
     113,   114,   114,   115,   115,   116,   116,   117,   117,   118,
     118,   118,   118,   118,   118,   119,   119,   119,   119,   119,
     120,   120,   121,   121,   122
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     3,     1,     4,     3,
       4,     3,     3,     2,     2,     1,     3,     1,     2,     2,
       2,     2,     4,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       5,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     1,     2,     1,
       2,     1,     2,     1,     3,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       2,     1,     1,     3,     4,     3,     4,     6,     1,     2,
       1,     3,     2,     2,     1,     1,     2,     1,     3,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     2,
       3,     1,     2,     1,     1,     1,     2,     5,     7,     5,
       7,     6,     7,     6,     7,     3,     2,     2,     2,     3,
       1,     2,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 76: /* declaration: declaration_specifiers init_declarator_list ';'  */
#line 202 "src\\parser.y"
                { 
			declare = false;

			for(auto idl = (yyvsp[-1].init_decl_list); idl != nullptr; idl = idl->next)
			{
				if ((yyvsp[-2].decl_specif).type == 0)
				{
					yyerror("no type specifier");
				}

				// if it is a typedef declaration
				if ((yyvsp[-2].decl_specif).specif & SPECIF_TYPEDEF)
				{
					if (idl->category == CATEGORY_VAR 
						|| idl->category == CATEGORY_ARRAY)
					{
						sym_t* nt = insert(idl->name);
						nt->category = idl->category;
						nt->type = (yyvsp[-2].decl_specif).type;
						nt->specif = (yyvsp[-2].decl_specif).specif;
						nt->depth = idl->depth;
					}
					else
					{
						yyerror("unsupported typedef declaration");
					}
				}
				else { 
					// else it is a common declaration
					sym_t* var = insert(idl->name);

					// if $1.type is a type defined with typedef
					if ((yyvsp[-2].decl_specif).type == TYPE_TYPEDEF)
					{
						sym_t* t = lookup_type((yyvsp[-2].decl_specif).name);
						if (t == nullptr)
						{
							yyerror("no such type");
						}
						if ((yyvsp[-2].decl_specif).specif & t->specif)
						{
							yyerror("duplicate specifier");
						}

						var->type = t->type;
						// clear SPECIF_TYPEDEF flag and then combine
						var->specif |= t->specif & ~SPECIF_TYPEDEF;
						var->depth = t->depth + idl->depth;
	
						if (t->category == CATEGORY_ARRAY
							&& idl->category == CATEGORY_FUNC)
						{
							yyerror("returning array is not supported");
						}

						// when idl->category == CATEGORY_FUNC
						// t->category can only be CATEGORY_VAR
						var->category ==
							idl->category > t->category
							? idl->category : t->category;

						if (var->category == CATEGORY_ARRAY)
						{
							// combine t->dimens and idl->dimens
						}	
					}
					// else it is a common type
					else
					{
						var->type = (yyvsp[-2].decl_specif).type;
						var->specif = (yyvsp[-2].decl_specif).specif;
						var->category = idl->category;
						var->depth = idl->depth;
						// var->dimens = idl->dimens;
					}
					var->params = idl->params;
					// parse typedef in params
					var->variadic = idl->variadic;
				}
			}

			//print_table();
		}
#line 1671 "y.tab.c"
    break;

  case 77: /* declaration_specifiers: storage_class_specifier  */
#line 288 "src\\parser.y"
                                  { (yyval.decl_specif) = (yyvsp[0].decl_specif); declare = true; }
#line 1677 "y.tab.c"
    break;

  case 78: /* declaration_specifiers: declaration_specifiers storage_class_specifier  */
#line 290 "src\\parser.y"
                {
			if ((yyvsp[-1].decl_specif).specif & (yyvsp[0].decl_specif).specif)
			{
				yyerror("duplicate specifier");
			}
			(yyvsp[-1].decl_specif).specif |= (yyvsp[0].decl_specif).specif;
			(yyval.decl_specif) = (yyvsp[-1].decl_specif);
			declare = true;
		}
#line 1691 "y.tab.c"
    break;

  case 79: /* declaration_specifiers: type_specifier  */
#line 299 "src\\parser.y"
                         { (yyval.decl_specif) = (yyvsp[0].decl_specif); declare = true; }
#line 1697 "y.tab.c"
    break;

  case 80: /* declaration_specifiers: declaration_specifiers type_specifier  */
#line 301 "src\\parser.y"
                {
			if ((yyvsp[-1].decl_specif).type != 0)
			{
				yyerror("multiple type specifier");
			}
			(yyvsp[-1].decl_specif).type = (yyvsp[0].decl_specif).type;
			(yyvsp[-1].decl_specif).name = (yyvsp[0].decl_specif).name;
			(yyval.decl_specif) = (yyvsp[-1].decl_specif);
			declare = true;
		}
#line 1712 "y.tab.c"
    break;

  case 81: /* declaration_specifiers: type_qualifier  */
#line 311 "src\\parser.y"
                         { (yyval.decl_specif) = (yyvsp[0].decl_specif); declare = true; }
#line 1718 "y.tab.c"
    break;

  case 82: /* declaration_specifiers: declaration_specifiers type_qualifier  */
#line 313 "src\\parser.y"
                {
			if ((yyvsp[-1].decl_specif).specif & (yyvsp[0].decl_specif).specif)
			{
				yyerror("duplicate qualifier");
			}
			(yyvsp[-1].decl_specif).specif |= (yyvsp[0].decl_specif).specif;
			(yyval.decl_specif) = (yyvsp[-1].decl_specif);
			declare = true;
		}
#line 1732 "y.tab.c"
    break;

  case 83: /* init_declarator_list: init_declarator  */
#line 326 "src\\parser.y"
                {
			(yyval.init_decl_list) = new init_decl_t;
			*(yyval.init_decl_list) = (yyvsp[0].init_decl);
		}
#line 1741 "y.tab.c"
    break;

  case 84: /* init_declarator_list: init_declarator_list ',' init_declarator  */
#line 331 "src\\parser.y"
                {
			auto idl = new init_decl_t;
			*idl = (yyvsp[0].init_decl);

			auto p = (yyvsp[-2].init_decl_list);
			for(; p->next != nullptr; p = p->next);
			p->next = idl;

			(yyval.init_decl_list) = (yyvsp[-2].init_decl_list);
		}
#line 1756 "y.tab.c"
    break;

  case 85: /* init_declarator: declarator  */
#line 344 "src\\parser.y"
                     { (yyval.init_decl) = (yyvsp[0].init_decl); }
#line 1762 "y.tab.c"
    break;

  case 86: /* init_declarator: declarator '=' initializer  */
#line 346 "src\\parser.y"
                {
			yyerror("initializer is currently not supported");
		}
#line 1770 "y.tab.c"
    break;

  case 87: /* storage_class_specifier: TYPEDEF  */
#line 352 "src\\parser.y"
                  { ZERO((yyval.decl_specif)); (yyval.decl_specif).specif = SPECIF_TYPEDEF; }
#line 1776 "y.tab.c"
    break;

  case 88: /* storage_class_specifier: STATIC  */
#line 353 "src\\parser.y"
                 { ZERO((yyval.decl_specif)); (yyval.decl_specif).specif = SPECIF_STATIC; }
#line 1782 "y.tab.c"
    break;

  case 89: /* type_specifier: VOID  */
#line 357 "src\\parser.y"
               { ZERO((yyval.decl_specif)); (yyval.decl_specif).type = TYPE_VOID; }
#line 1788 "y.tab.c"
    break;

  case 90: /* type_specifier: CHAR  */
#line 358 "src\\parser.y"
               { ZERO((yyval.decl_specif)); (yyval.decl_specif).type = TYPE_CHAR; }
#line 1794 "y.tab.c"
    break;

  case 91: /* type_specifier: SHORT  */
#line 359 "src\\parser.y"
                { ZERO((yyval.decl_specif)); (yyval.decl_specif).type = TYPE_SHORT; }
#line 1800 "y.tab.c"
    break;

  case 92: /* type_specifier: INT  */
#line 360 "src\\parser.y"
              { ZERO((yyval.decl_specif)); (yyval.decl_specif).type = TYPE_INT; }
#line 1806 "y.tab.c"
    break;

  case 93: /* type_specifier: LONG  */
#line 361 "src\\parser.y"
               { ZERO((yyval.decl_specif)); (yyval.decl_specif).type = TYPE_LONG; }
#line 1812 "y.tab.c"
    break;

  case 94: /* type_specifier: TYPE  */
#line 362 "src\\parser.y"
               { ZERO((yyval.decl_specif)); (yyval.decl_specif).type = TYPE_TYPEDEF; (yyval.decl_specif).name = (yyvsp[0].sval); }
#line 1818 "y.tab.c"
    break;

  case 95: /* type_qualifier: CONST  */
#line 366 "src\\parser.y"
                { ZERO((yyval.decl_specif)); (yyval.decl_specif).specif = SPECIF_CONST; }
#line 1824 "y.tab.c"
    break;

  case 100: /* declarator: pointer direct_declarator  */
#line 376 "src\\parser.y"
                                    { (yyvsp[0].init_decl).depth = (yyvsp[-1].ival); (yyval.init_decl) = (yyvsp[0].init_decl); }
#line 1830 "y.tab.c"
    break;

  case 101: /* declarator: direct_declarator  */
#line 377 "src\\parser.y"
                            { (yyval.init_decl) = (yyvsp[0].init_decl); }
#line 1836 "y.tab.c"
    break;

  case 102: /* direct_declarator: ID  */
#line 381 "src\\parser.y"
             { ZERO((yyval.init_decl)); (yyval.init_decl).name = (yyvsp[0].sval); (yyval.init_decl).category = CATEGORY_VAR; }
#line 1842 "y.tab.c"
    break;

  case 103: /* direct_declarator: direct_declarator '[' ']'  */
#line 382 "src\\parser.y"
                                    { yyerror("array is currently not supported"); }
#line 1848 "y.tab.c"
    break;

  case 104: /* direct_declarator: direct_declarator '[' assignment_expression ']'  */
#line 383 "src\\parser.y"
                                                          { yyerror("array is currently not supported"); }
#line 1854 "y.tab.c"
    break;

  case 105: /* direct_declarator: direct_declarator '(' ')'  */
#line 385 "src\\parser.y"
                {
			if ((yyvsp[-2].init_decl).category != CATEGORY_VAR)
			{
				yyerror("illegal function declaration");
			}
			(yyvsp[-2].init_decl).category = CATEGORY_FUNC;
			(yyval.init_decl) = (yyvsp[-2].init_decl);
		}
#line 1867 "y.tab.c"
    break;

  case 106: /* direct_declarator: direct_declarator '(' parameter_list ')'  */
#line 394 "src\\parser.y"
                {
			if ((yyvsp[-3].init_decl).category != CATEGORY_VAR)
			{
				yyerror("illegal function declaration");
			}
			(yyvsp[-3].init_decl).category = CATEGORY_FUNC;
			(yyvsp[-3].init_decl).params = (yyvsp[-1].param_list);
			(yyval.init_decl) = (yyvsp[-3].init_decl);
		}
#line 1881 "y.tab.c"
    break;

  case 107: /* direct_declarator: direct_declarator '(' parameter_list ',' ELLIPSIS ')'  */
#line 404 "src\\parser.y"
                {
			if ((yyvsp[-5].init_decl).category != CATEGORY_VAR)
			{
				yyerror("illegal function declaration");
			}
			(yyvsp[-5].init_decl).category = CATEGORY_FUNC;
			(yyvsp[-5].init_decl).params = (yyvsp[-3].param_list);
			(yyvsp[-5].init_decl).variadic = true;
			(yyval.init_decl) = (yyvsp[-5].init_decl);
		}
#line 1896 "y.tab.c"
    break;

  case 108: /* pointer: '*'  */
#line 417 "src\\parser.y"
              { (yyval.ival) = 1; }
#line 1902 "y.tab.c"
    break;

  case 109: /* pointer: '*' pointer  */
#line 418 "src\\parser.y"
                      { (yyval.ival) = (yyvsp[0].ival) + 1; }
#line 1908 "y.tab.c"
    break;

  case 110: /* parameter_list: parameter_declaration  */
#line 423 "src\\parser.y"
                {
			(yyval.param_list) = new param_t;
			*(yyval.param_list) = (yyvsp[0].param);

			//$$->next = nullptr;
			// no need to set this, as it was already set in 
			// parameter_declaration using ZERO()
		}
#line 1921 "y.tab.c"
    break;

  case 111: /* parameter_list: parameter_list ',' parameter_declaration  */
#line 432 "src\\parser.y"
                {
			auto idl = new param_t;
			*idl = (yyvsp[0].param);

			auto p = (yyvsp[-2].param_list);
			for(; p->next != nullptr; p = p->next);
			p->next = idl;

			(yyval.param_list) = (yyvsp[-2].param_list);
		}
#line 1936 "y.tab.c"
    break;

  case 112: /* parameter_declaration: declaration_specifiers declarator  */
#line 446 "src\\parser.y"
                { 
			if ((yyvsp[0].init_decl).category != CATEGORY_VAR)
			{
				yyerror("only value-type and pointers are supported in parameter list");
			}
			ZERO((yyval.param));
			(yyval.param).type = (yyvsp[-1].decl_specif).type; 
			(yyval.param).specif = (yyvsp[-1].decl_specif).specif;
			(yyval.param).depth = (yyvsp[0].init_decl).depth;
			(yyval.param).name = (yyvsp[0].init_decl).name;
		}
#line 1952 "y.tab.c"
    break;

  case 113: /* parameter_declaration: declaration_specifiers pointer  */
#line 458 "src\\parser.y"
                { 
			ZERO((yyval.param));
			(yyval.param).type = (yyvsp[-1].decl_specif).type; 
			(yyval.param).specif = (yyvsp[-1].decl_specif).specif;
			(yyval.param).depth = (yyvsp[0].ival);
		}
#line 1963 "y.tab.c"
    break;

  case 114: /* parameter_declaration: declaration_specifiers  */
#line 465 "src\\parser.y"
                { 
			ZERO((yyval.param));
			(yyval.param).type = (yyvsp[0].decl_specif).type; 
			(yyval.param).specif = (yyvsp[0].decl_specif).specif;
		}
#line 1973 "y.tab.c"
    break;


#line 1977 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 557 "src\\parser.y"

