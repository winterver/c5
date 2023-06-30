/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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
#line 26 "src\\parser.y"

	long long ival;
	long double fval;
	const char* sval;

	struct {
		int type; 
		int specif; 
		const char* name; // valid only if type == TYPE_TYPDEF
	} decl_specif;

	init_decl_t init_decl;
	std::vector<init_decl_t>* init_decl_list;

	param_t param;
	std::vector<param_t>* param_list;

#line 131 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
