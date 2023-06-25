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
    ID = 258,                      /* ID  */
    NUM = 259,                     /* NUM  */
    DEC = 260,                     /* DEC  */
    STR = 261,                     /* STR  */
    VOID = 262,                    /* VOID  */
    CHAR = 263,                    /* CHAR  */
    SHORT = 264,                   /* SHORT  */
    INT = 265,                     /* INT  */
    LONG = 266,                    /* LONG  */
    FLOAT = 267,                   /* FLOAT  */
    DOUBLE = 268,                  /* DOUBLE  */
    TYPE = 269,                    /* TYPE  */
    IF = 270,                      /* IF  */
    ELSE = 271,                    /* ELSE  */
    WHILE = 272,                   /* WHILE  */
    FOR = 273,                     /* FOR  */
    CONTINUE = 274,                /* CONTINUE  */
    BREAK = 275,                   /* BREAK  */
    RETURN = 276,                  /* RETURN  */
    SIZEOF = 277,                  /* SIZEOF  */
    LOGAND = 278,                  /* LOGAND  */
    LOGOR = 279,                   /* LOGOR  */
    ASGN = 280,                    /* ASGN  */
    PLUSASGN = 281,                /* PLUSASGN  */
    MINUSASGN = 282,               /* MINUSASGN  */
    MULASGN = 283,                 /* MULASGN  */
    DIVASGN = 284,                 /* DIVASGN  */
    MODASGN = 285,                 /* MODASGN  */
    SHLASGN = 286,                 /* SHLASGN  */
    SHRASGN = 287,                 /* SHRASGN  */
    ANDASGN = 288,                 /* ANDASGN  */
    ORASGN = 289,                  /* ORASGN  */
    XORASGN = 290,                 /* XORASGN  */
    EQ = 291,                      /* EQ  */
    NE = 292,                      /* NE  */
    LE = 293,                      /* LE  */
    GE = 294,                      /* GE  */
    SHL = 295,                     /* SHL  */
    SHR = 296,                     /* SHR  */
    LOGNOT = 297,                  /* LOGNOT  */
    NOT = 298,                     /* NOT  */
    INCR = 299,                    /* INCR  */
    DECR = 300,                    /* DECR  */
    ARW = 301                      /* ARW  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
