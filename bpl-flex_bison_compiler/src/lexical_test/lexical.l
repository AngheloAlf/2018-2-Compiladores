%option nounput yylineno
%option interactive
%option noyywrap 

%{
#include <stdio.h>
#include <stdnoreturn.h>
#include <stdbool.h>
noreturn void invalid(char *s);

%}

%x COMMENT_STATE


ESPACIO         [ \t\n\r]*
LETRA           [a-zA-Z]
NUMERO          \-?[0-9]+
VARIABLE        _*{LETRA}([_0-9]|{LETRA})*

COMENTARIO      \/\*(.|{ESPACIO})*\*\/

INT_TYPE        int
STRING_TYPE     string
VOID_TYPE       void
POINTER_TYPE    {ESPACIO}(\*|\&){ESPACIO}

ARREGLOINDICE   {ESPACIO}\[{ESPACIO}({NUMERO})?{ESPACIO}\]{ESPACIO}

KEYWORDS        int|void|string|if|else|while|return|write|writeln|read

ARITMETICA      \+|\-|\*|\/|\%
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

%%


"/*"                {BEGIN(COMMENT_STATE);}
<COMMENT_STATE>"*/" {BEGIN(INITIAL);}
<COMMENT_STATE>\n   {;}
<COMMENT_STATE>.    {;}

{CURLY}             {return 41;}
{PAREN}             {return 42;}
{SEMICOLON}         {return 43;}
{COMMA}             {return 44;}
{ASIGNATION}        {return 45;}
{BRACKET}           {return 46;}

{INT_TYPE}          {return 11;}
{STRING_TYPE}       {return 12;}
{POINTER_TYPE}      {return 13;}
{ARREGLOINDICE}     {return 14;}
{VOID_TYPE}         {return 15;}

{FLOW_CONTROL}      {return 21;}
{LIB_FUNC}          {return 22;}
{RETURN}            {return 23;}

{STRING}            {return 31;}
{ARITMETICA}        {return 32;}
{COMPARADORES}      {return 33;}

{VARIABLE}          {return 1;}
{NUMERO}            {return 2;}

{ESPACIO}           ;
.                   {invalid(yytext);}



%%

