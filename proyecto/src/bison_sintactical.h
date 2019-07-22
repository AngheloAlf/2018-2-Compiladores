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

#ifndef YY_YY_BISON_SINTACTICAL_H_INCLUDED
# define YY_YY_BISON_SINTACTICAL_H_INCLUDED
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
    INT_VALUE = 258,
    STRING_VALUE = 259,
    IDENTIF = 260,
    LEFT_PARENTHESIS = 261,
    RIGHT_PARENTHESIS = 262,
    LEFT_BRACKET_ = 263,
    RIGHT_BRACKET_ = 264,
    LEFT_CURLY_ = 265,
    RIGHT_CURLY_ = 266,
    VOID_TYPE_ = 267,
    TYPE_VALUE = 268,
    SEMI_COLON = 269,
    COMMA_CONST = 270,
    ASTERISC_CONST = 271,
    AMPERSAND_CONST = 272,
    ASSIGNATION_CONST = 273,
    COMPARATORS = 274,
    PLUS_CONST = 275,
    MINUS_CONST = 276,
    MUL_OPERATION = 277,
    IF_EXPR = 278,
    ELSE_EXPR = 279,
    WHILE_EXPR = 280,
    RETURN_EXPR = 281,
    WRITE_EXPR = 282,
    WRITELN_EXPR = 283,
    READ_EXPR = 284
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 18 "sintactical.y" /* yacc.c:1909  */

	int ival;
	char *sval;

#line 89 "bison_sintactical.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BISON_SINTACTICAL_H_INCLUDED  */
