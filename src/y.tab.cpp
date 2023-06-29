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
int yylex(void);
void yyerror(const char* s);
#define ZERO(s) memset(&s, 0, sizeof(s))

// states of the parser
bool declare;

#line 82 "y.tab.c"

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
#line 13 "src\\parser.y"

	long long ival;
	long double fval;
	const char* sval;

	struct {
		int type; 
		int specif; 
		const char* name; // valid only if type == TYPE_TYPDEF
	} decl_specif;

#line 193 "y.tab.c"

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
#define YYLAST   703

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  153
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  251

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
       0,    50,    50,    51,    52,    53,    54,    58,    59,    60,
      61,    62,    63,    64,    65,    69,    70,    74,    75,    76,
      77,    78,    79,    83,    84,    85,    86,    87,    88,    92,
      93,    97,    98,    99,   100,   104,   105,   106,   110,   111,
     112,   116,   117,   118,   119,   120,   124,   125,   126,   130,
     131,   135,   136,   140,   141,   145,   146,   150,   151,   155,
     156,   160,   161,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   179,   180,   184,   191,   192,   202,
     203,   214,   215,   228,   229,   233,   234,   238,   239,   243,
     244,   245,   246,   247,   248,   252,   256,   257,   258,   259,
     262,   263,   267,   268,   269,   270,   271,   272,   276,   277,
     281,   282,   286,   287,   291,   292,   296,   297,   298,   302,
     303,   307,   308,   309,   310,   311,   312,   316,   320,   321,
     325,   326,   330,   331,   335,   336,   340,   341,   345,   346,
     347,   348,   349,   350,   354,   355,   356,   357,   358,   362,
     363,   367,   368,   372
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

#define YYPACT_NINF (-148)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     426,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
    -148,     8,   426,   426,   426,   164,  -148,  -148,  -148,   -38,
     -35,  -148,   -42,    86,    61,  -148,  -148,  -148,  -148,  -148,
    -148,     8,  -148,   318,   182,  -148,   303,   486,    86,  -148,
     -18,  -148,  -148,  -148,  -148,   583,   604,   604,   474,  -148,
    -148,  -148,  -148,  -148,  -148,   318,  -148,    93,    20,   642,
    -148,    -7,   -26,    49,    13,    76,    26,    39,    68,    82,
      11,  -148,  -148,  -148,    70,    91,    94,   100,   301,    84,
      88,   393,   156,  -148,  -148,  -148,   -24,  -148,     8,  -148,
    -148,  -148,   241,  -148,  -148,  -148,  -148,  -148,  -148,     8,
       3,  -148,  -148,   110,   474,  -148,   642,  -148,  -148,    21,
     142,   142,   -38,   114,  -148,   -20,   162,  -148,  -148,   512,
     642,   166,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
    -148,  -148,  -148,   642,  -148,  -148,   642,   642,   642,   642,
     642,   642,   642,   642,   642,   642,   642,   642,   642,   642,
     642,   642,   642,   642,   642,   301,   642,   377,   642,   125,
    -148,  -148,  -148,    -4,   101,   642,  -148,  -148,  -148,  -148,
    -148,   639,  -148,   133,  -148,  -148,  -148,  -148,   642,   259,
    -148,  -148,  -148,    30,  -148,    87,  -148,  -148,  -148,  -148,
    -148,    -7,    -7,   -26,   -26,    49,    49,    49,    49,    13,
      13,    76,    26,    39,    68,    82,   -48,  -148,    32,   415,
     415,    33,   143,  -148,  -148,  -148,   151,  -148,  -148,  -148,
    -148,  -148,  -148,   642,  -148,   642,   301,   545,   571,   301,
     642,  -148,  -148,  -148,   167,   301,    38,   301,    53,  -148,
      55,   301,  -148,   301,  -148,   301,   139,  -148,  -148,  -148,
    -148
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    87,    88,    95,    89,    90,    91,    92,    93,    94,
     152,     0,    77,    79,    81,     0,   149,   151,   102,   108,
       0,    83,    85,   101,     0,    78,    80,    82,     1,   150,
     109,     0,    76,     0,     0,   153,     0,     0,   100,    84,
      85,     3,     4,     2,     5,     0,     0,     0,     0,    23,
      24,    25,    26,    27,    28,     0,     7,    17,    29,     0,
      31,    35,    38,    41,    46,    49,    51,    53,    55,    57,
      59,    61,   116,    86,     2,     0,     0,     0,     0,     0,
       0,     0,     0,   134,   128,    74,     0,   132,     0,   133,
     121,   122,     0,   130,   123,   124,   125,   126,   105,   113,
       0,   110,   103,     0,     0,    21,     0,    18,    19,     0,
      96,    98,   114,     0,   119,     0,     0,    13,    14,     0,
       0,     0,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    63,     0,    29,    20,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,   146,   147,     0,     0,     0,   135,   129,   131,   112,
     106,     0,   104,     0,     6,    97,    99,   115,     0,     0,
     117,    12,     9,     0,    15,     0,    11,    62,    32,    33,
      34,    36,    37,    39,    40,    44,    45,    42,    43,    47,
      48,    50,    52,    54,    56,    58,     0,   127,     0,     0,
       0,     0,     0,   148,   144,    75,     0,   111,    22,    30,
     118,   120,    10,     0,     8,     0,     0,     0,     0,     0,
       0,   107,    16,    60,   136,     0,     0,     0,     0,   138,
       0,     0,   142,     0,   140,     0,     0,   137,   143,   141,
     139
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -148,  -148,  -148,  -148,   -22,  -148,   -41,   -27,     7,    62,
       5,    71,    74,    60,    69,    80,  -148,     9,   -33,  -148,
     -47,   -23,     2,  -148,   204,  -148,   -40,   -36,    47,    -5,
     212,   -14,  -148,    66,   145,   -46,  -148,   -75,  -148,   230,
    -148,   165,  -147,  -148,  -148,  -148,  -148,   243,  -148
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    56,    57,   183,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    85,   133,
      86,    10,    88,    20,    21,    12,    13,    14,   112,    40,
      23,    24,   100,   101,   113,    73,   115,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    15,    16,    17
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      72,   109,    11,   159,   103,    30,    22,   165,   110,   114,
     210,    87,   111,    18,    25,    26,    27,    11,   135,    19,
      31,   225,    72,   105,   107,   108,   143,   144,    33,   153,
      34,   165,   139,   140,   163,   179,    32,   134,    99,   122,
     123,   124,   125,   126,   127,   128,   129,   166,   130,   131,
     136,   165,    33,   180,   170,   137,   138,   109,   171,   109,
     141,   142,   227,   228,   110,    19,    18,   213,   111,    87,
     110,   110,   174,   185,   111,   111,   165,   145,   146,   154,
     207,   222,   149,   226,   229,   223,   184,   165,   165,   243,
     132,   147,   148,   165,   169,   188,   189,   190,   177,   152,
     187,   116,   117,   118,   245,   150,   246,   206,   165,   208,
     165,   211,   191,   192,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   215,   221,   209,   151,    36,   219,    37,   155,
     224,   156,   165,   119,   157,   120,    72,   121,   193,   194,
     158,   234,   199,   200,   239,   160,   134,   175,   176,   161,
     242,   164,   244,   172,    28,   178,   247,   181,   248,   212,
     249,   186,   214,    99,     3,     4,     5,     6,     7,     8,
     236,   238,     9,   240,   218,    41,    42,    74,    44,    45,
     232,    46,    47,   230,     1,     2,     3,     4,     5,     6,
       7,     8,   231,   134,     9,   195,   196,   197,   198,   241,
     250,   203,     1,     2,     3,     4,     5,     6,     7,     8,
     201,   204,     9,    75,   202,    76,    77,    78,    79,    80,
      81,    82,    48,   205,   233,    39,    38,   217,    49,    50,
      51,    52,    53,    54,    41,    42,    74,    44,    45,   173,
      46,    47,    35,    83,    34,    84,     0,   168,    29,     0,
       0,     0,    41,    42,    43,    44,    45,     0,    46,    47,
       0,     1,     2,     3,     4,     5,     6,     7,     8,     0,
       0,     9,    75,     0,    76,    77,    78,    79,    80,    81,
      82,    48,     0,     0,     0,     0,     0,    49,    50,    51,
      52,    53,    54,     0,    41,    42,    74,    44,    45,    48,
      46,    47,    83,    34,   167,    49,    50,    51,    52,    53,
      54,    41,    42,    43,    44,    45,     0,    46,    47,     0,
       0,    55,   220,     1,     2,     3,     4,     5,     6,     7,
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
      42,    43,    44,    45,     0,    46,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     4,     5,     6,
       7,     8,     0,     0,     9,    41,    42,    43,    44,    45,
       0,    46,    47,     0,    48,     0,     0,     0,     0,     0,
      49,    50,    51,    52,    53,    54,    48,     0,     0,   102,
       0,     0,    49,    50,    51,    52,    53,    54,    41,    42,
      43,    44,    45,     0,    46,    47,     0,     0,     0,     0,
       0,     0,    48,   182,     0,     0,     0,     0,    49,    50,
      51,    52,    53,    54,    41,    42,    43,    44,    45,     0,
      46,    47,     0,     0,     0,     0,    41,    42,    43,    44,
      45,     0,    46,    47,     0,    48,   235,     0,     0,     0,
       0,    49,    50,    51,    52,    53,    54,    41,    42,    43,
      44,    45,     0,    46,    47,     0,     0,     0,     0,     0,
       0,    48,   237,     0,     0,     0,     0,    49,    50,    51,
      52,    53,    54,   104,     0,     0,     0,     0,     0,    49,
      50,    51,    52,    53,    54,    41,    42,    43,    44,    45,
       0,    46,    47,     0,   106,     0,     0,     0,     0,     0,
      49,    50,    51,    52,    53,    54,   216,     0,     0,     1,
       2,     3,     4,     5,     6,     7,     8,     0,     0,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    48,     0,     0,     0,     0,     0,    49,    50,
      51,    52,    53,    54
};

static const yytype_int16 yycheck[] =
{
      33,    48,     0,    78,    37,    19,    11,    55,    48,    55,
     157,    34,    48,     5,    12,    13,    14,    15,    59,    57,
      55,    69,    55,    45,    46,    47,    13,    14,    70,    18,
      72,    55,    58,    59,    81,    55,    71,    59,    36,    19,
      20,    21,    22,    23,    24,    25,    26,    71,    28,    29,
      57,    55,    70,    73,    51,    62,    63,   104,    55,   106,
      11,    12,   209,   210,   104,    57,     5,    71,   104,    92,
     110,   111,    51,   120,   110,   111,    55,    64,    65,    68,
     155,    51,    56,    51,    51,    55,   119,    55,    55,    51,
      70,    15,    16,    55,    99,   136,   137,   138,   112,    17,
     133,     8,     9,    10,    51,    66,    51,   154,    55,   156,
      55,   158,   139,   140,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   165,   179,   157,    67,    50,   178,    52,    69,
      53,    50,    55,    50,    50,    52,   179,    54,   141,   142,
      50,   226,   147,   148,   229,    71,   178,   110,   111,    71,
     235,     5,   237,    53,     0,    51,   241,     5,   243,    44,
     245,     5,    71,   171,    32,    33,    34,    35,    36,    37,
     227,   228,    40,   230,    51,     3,     4,     5,     6,     7,
     223,     9,    10,    50,    30,    31,    32,    33,    34,    35,
      36,    37,    51,   225,    40,   143,   144,   145,   146,    42,
      71,   151,    30,    31,    32,    33,    34,    35,    36,    37,
     149,   152,    40,    41,   150,    43,    44,    45,    46,    47,
      48,    49,    50,   153,   225,    31,    24,   171,    56,    57,
      58,    59,    60,    61,     3,     4,     5,     6,     7,   104,
       9,    10,    22,    71,    72,    73,    -1,    92,    15,    -1,
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
       4,     5,     6,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
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
      97,    98,   103,   104,   105,    96,    96,    96,     0,   121,
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
      51,    55,    53,   108,    51,   102,   102,   105,    51,    55,
      73,     5,    51,    77,    92,    94,     5,    92,    80,    80,
      80,    81,    81,    82,    82,    83,    83,    83,    83,    84,
      84,    85,    86,    87,    88,    89,    94,   111,    94,    95,
     116,    94,    44,    71,    71,    92,    27,   107,    51,    80,
      73,   109,    51,    55,    53,    69,    51,   116,   116,    51,
      50,    51,    92,    91,   111,    51,    94,    51,    94,   111,
      94,    42,   111,    51,   111,    51,    51,   111,   111,   111,
      71
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
     106,   106,   107,   107,   108,   108,   109,   109,   109,   110,
     110,   111,   111,   111,   111,   111,   111,   112,   113,   113,
     114,   114,   115,   115,   116,   116,   117,   117,   118,   118,
     118,   118,   118,   118,   119,   119,   119,   119,   119,   120,
     120,   121,   121,   122
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
       1,     3,     2,     1,     1,     2,     1,     3,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     2,     3,
       1,     2,     1,     1,     1,     2,     5,     7,     5,     7,
       6,     7,     6,     7,     3,     2,     2,     2,     3,     1,
       2,     1,     1,     3
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
#line 185 "src\\parser.y"
                { 
			declare = false;
		}
#line 1579 "y.tab.c"
    break;

  case 77: /* declaration_specifiers: storage_class_specifier  */
#line 191 "src\\parser.y"
                                  { (yyval.decl_specif) = (yyvsp[0].decl_specif); declare = true; }
#line 1585 "y.tab.c"
    break;

  case 78: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 193 "src\\parser.y"
                {
			if ((yyvsp[-1].decl_specif).specif & (yyvsp[0].decl_specif).specif)
			{
				yyerror("duplicated specifier");
			}
			(yyvsp[0].decl_specif).specif |= (yyvsp[-1].decl_specif).specif;
			(yyval.decl_specif) = (yyvsp[0].decl_specif);
			declare = true;
		}
#line 1599 "y.tab.c"
    break;

  case 79: /* declaration_specifiers: type_specifier  */
#line 202 "src\\parser.y"
                         { (yyval.decl_specif) = (yyvsp[0].decl_specif); declare = true; }
#line 1605 "y.tab.c"
    break;

  case 80: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 204 "src\\parser.y"
                {
			if ((yyvsp[0].decl_specif).type != 0)
			{
				yyerror("duplicated specifier");
			}
			(yyvsp[0].decl_specif).type = (yyvsp[-1].decl_specif).type;
			(yyvsp[0].decl_specif).name = (yyvsp[-1].decl_specif).name;
			(yyval.decl_specif) = (yyvsp[0].decl_specif);
			declare = true;
		}
#line 1620 "y.tab.c"
    break;

  case 81: /* declaration_specifiers: type_qualifier  */
#line 214 "src\\parser.y"
                         { (yyval.decl_specif) = (yyvsp[0].decl_specif); declare = true; }
#line 1626 "y.tab.c"
    break;

  case 82: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 216 "src\\parser.y"
                {
			if ((yyvsp[-1].decl_specif).specif & (yyvsp[0].decl_specif).specif)
			{
				yyerror("duplicated specifier");
			}
			(yyvsp[0].decl_specif).specif |= (yyvsp[-1].decl_specif).specif;
			(yyval.decl_specif) = (yyvsp[0].decl_specif);
			declare = true;
		}
#line 1640 "y.tab.c"
    break;

  case 87: /* storage_class_specifier: TYPEDEF  */
#line 238 "src\\parser.y"
                  { ZERO((yyval.decl_specif)); (yyval.decl_specif).specif = SPECIF_TYPEDEF; }
#line 1646 "y.tab.c"
    break;

  case 88: /* storage_class_specifier: STATIC  */
#line 239 "src\\parser.y"
                 { ZERO((yyval.decl_specif)); (yyval.decl_specif).specif = SPECIF_STATIC; }
#line 1652 "y.tab.c"
    break;

  case 89: /* type_specifier: VOID  */
#line 243 "src\\parser.y"
               { ZERO((yyval.decl_specif)); (yyval.decl_specif).type = TYPE_VOID; }
#line 1658 "y.tab.c"
    break;

  case 90: /* type_specifier: CHAR  */
#line 244 "src\\parser.y"
               { ZERO((yyval.decl_specif)); (yyval.decl_specif).type = TYPE_CHAR; }
#line 1664 "y.tab.c"
    break;

  case 91: /* type_specifier: SHORT  */
#line 245 "src\\parser.y"
                { ZERO((yyval.decl_specif)); (yyval.decl_specif).type = TYPE_SHORT; }
#line 1670 "y.tab.c"
    break;

  case 92: /* type_specifier: INT  */
#line 246 "src\\parser.y"
              { ZERO((yyval.decl_specif)); (yyval.decl_specif).type = TYPE_INT; }
#line 1676 "y.tab.c"
    break;

  case 93: /* type_specifier: LONG  */
#line 247 "src\\parser.y"
               { ZERO((yyval.decl_specif)); (yyval.decl_specif).type = TYPE_LONG; }
#line 1682 "y.tab.c"
    break;

  case 94: /* type_specifier: TYPE  */
#line 248 "src\\parser.y"
               { ZERO((yyval.decl_specif)); (yyval.decl_specif).type = TYPE_TYPEDEF; (yyval.decl_specif).name = (yyvsp[0].sval); }
#line 1688 "y.tab.c"
    break;

  case 95: /* type_qualifier: CONST  */
#line 252 "src\\parser.y"
                { ZERO((yyval.decl_specif)); (yyval.decl_specif).specif = SPECIF_CONST; }
#line 1694 "y.tab.c"
    break;


#line 1698 "y.tab.c"

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

#line 375 "src\\parser.y"

