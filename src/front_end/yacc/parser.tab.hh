/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_TAB_HH_INCLUDED
# define YY_YY_PARSER_TAB_HH_INCLUDED
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
    LCURLYBRACKET = 258,
    RCURLYBRACKET = 259,
    LPAREN = 260,
    RPAREN = 261,
    SEMICOLON = 262,
    CHAR = 263,
    DOUBLE = 264,
    ENUM = 265,
    FLOAT = 266,
    INT = 267,
    LONG = 268,
    SHORT = 269,
    STRUCT = 270,
    UNION = 271,
    UNSIGNED = 272,
    VOID = 273,
    FOR = 274,
    DO = 275,
    WHILE = 276,
    IF = 277,
    ELSE = 278,
    BREAK = 279,
    CONTINUE = 280,
    GOTO = 281,
    SWITCH = 282,
    CASE = 283,
    DEFAULT = 284,
    RETURN = 285,
    AUTO = 286,
    EXTERN = 287,
    REGISTER = 288,
    STATIC = 289,
    CONST = 290,
    SIZEOF = 291,
    TYPEDEF = 292,
    VOLATILE = 293,
    NUM = 294,
    CHARACTER = 295,
    ASSIGN = 296,
    MUL = 297,
    DIV = 298,
    PLUS = 299,
    MINUS = 300,
    MODULO = 301,
    INC = 302,
    DEC = 303,
    EQ = 304,
    NEQ = 305,
    GT = 306,
    LT = 307,
    GE = 308,
    LE = 309,
    LNOT = 310,
    LAND = 311,
    LOR = 312,
    NOT = 313,
    AND = 314,
    OR = 315,
    XOR = 316,
    LSHFT = 317,
    RSHFT = 318,
    ADDASSIGN = 319,
    SUBASSIGN = 320,
    MULASSIGN = 321,
    DIVASSIGN = 322,
    MODASSIGN = 323,
    ANDASSIGN = 324,
    ORASSIGN = 325,
    XORASSIGN = 326,
    LSHASSIGN = 327,
    RSHASSIGN = 328,
    DEREF = 329,
    STRING = 330,
    NAME = 331
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 11 "parser.yy" /* yacc.c:1909  */

    yytokentype token;
    int intVal;
    char *stringVal;
    struct AstClass *node;

#line 138 "parser.tab.hh" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_HH_INCLUDED  */
