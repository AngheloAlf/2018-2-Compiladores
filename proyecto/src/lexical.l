%option nounput yylineno
%option interactive
%option noyywrap 

%{
#include <stdio.h>
#include <stdnoreturn.h>
#include <stdbool.h>
#include "bison_sintactical.h"

noreturn void invalid(const char *s);

extern int lineCounter;

%}

%x COMMENT_STATE


ESPACIO         [ \t\n\r]*
LETRA           [a-zA-Z]
NUMERO          [0-9]+
VARIABLE        _*{LETRA}([_0-9]|{LETRA})*

COMENTARIO      \/\*(.|{ESPACIO})*\*\/

INT_TYPE        int
STRING_TYPE     string
VOID_TYPE       void

BASIC_TYPES     {INT_TYPE}|{STRING_TYPE}

POINTER_TYPE    {ESPACIO}(\*|\&){ESPACIO}

ARREGLOINDICE   {ESPACIO}\[{ESPACIO}({NUMERO})?{ESPACIO}\]{ESPACIO}

KEYWORDS        int|void|string|if|else|while|return|write|writeln|read

PLUS            \+
MINUS           \-

OPERA_SUMA      {PLUS}|{MINUS}
OPERA_MULT      \*|\/|\%

ARITMETICA      {OPERA_SUMA}|{OPERA_MULT}
COMPARADORES    \<=|\<|==|!=|\>|\>=
STRING          \"[^\"]*\"
ASIGNATION      =


IF              if
ELSE            else
WHILE           while

FLOW_CONTROL    {IF}|{ELSE}|{WHILE}

WRITE           write
WRITELN         writeln
READ            read

LIB_FUNC        {WRITE}|{WRITELN}|{READ}

RETURN          return

CURLY           \{|\}
PAREN           \(|\)
BRACKET         "["|"]"

SEMICOLON       ;
COMMA           ,
LEFT_PAREN      \(
RIGHT_PAREN     \)
LEFT_BRACKET    "["
RIGHT_BRACKET   "]"
LEFT_CURLY      \{
RIGHT_CURLY     \}

ASTERISC        \*
AMPERSAND       "&"

%%


"/*"                {BEGIN(COMMENT_STATE);}
<COMMENT_STATE>"*/" {BEGIN(INITIAL);}
<COMMENT_STATE>\n   {++lineCounter;}
<COMMENT_STATE>.    {;}


{VOID_TYPE}         { yylval.sval = strdup(yytext); return VOID_TYPE_;}

{NUMERO}            { yylval.ival = atoi(yytext); return INT_VALUE; /*return 11;*/}
{STRING}            { yylval.sval = strdup(yytext); return STRING_VALUE; /*return 12;*/}
{BASIC_TYPES}       { yylval.sval = strdup(yytext); return TYPE_VALUE;}
{SEMICOLON}         { yylval.sval = strdup(yytext); return SEMI_COLON;}

{LEFT_PAREN}        { yylval.sval = strdup(yytext); return LEFT_PARENTHESIS;}
{RIGHT_PAREN}       { yylval.sval = strdup(yytext); return RIGHT_PARENTHESIS;}

{LEFT_BRACKET}      { yylval.sval = strdup(yytext); return LEFT_BRACKET_;}
{RIGHT_BRACKET}     { yylval.sval = strdup(yytext); return RIGHT_BRACKET_;}


{COMMA}             { yylval.sval = strdup(yytext); return COMMA_CONST;}
{ASTERISC}          { yylval.sval = strdup(yytext); return ASTERISC_CONST;}
{AMPERSAND}         { yylval.sval = strdup(yytext); return AMPERSAND_CONST;}

{ASIGNATION}        { yylval.sval = strdup(yytext); return ASSIGNATION_CONST;}
{COMPARADORES}      { yylval.sval = strdup(yytext); return COMPARATORS;}

{PLUS}              { yylval.sval = strdup(yytext); return PLUS_CONST;}
{MINUS}             { yylval.sval = strdup(yytext); return MINUS_CONST;}

{OPERA_MULT}        { yylval.sval = strdup(yytext); return MUL_OPERATION;}

{LEFT_CURLY}        { yylval.sval = strdup(yytext); return LEFT_CURLY_;}
{RIGHT_CURLY}       { yylval.sval = strdup(yytext); return RIGHT_CURLY_;}

{IF}                { yylval.sval = strdup(yytext); return IF_EXPR;}
{ELSE}              { yylval.sval = strdup(yytext); return ELSE_EXPR;}
{WHILE}             { yylval.sval = strdup(yytext); return WHILE_EXPR;}

{RETURN}            { yylval.sval = strdup(yytext); return RETURN_EXPR;}

{WRITE}             { yylval.sval = strdup(yytext); return WRITE_EXPR;}
{WRITELN}           { yylval.sval = strdup(yytext); return WRITELN_EXPR;}
{READ}              { yylval.sval = strdup(yytext); return READ_EXPR;}


{VARIABLE}          { yylval.sval = strdup(yytext); return IDENTIF;}

. ;

\n                  {++lineCounter;}

%%

