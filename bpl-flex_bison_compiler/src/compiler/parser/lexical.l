%option nounput yylineno
%option interactive
%option noyywrap 

%{
#include <stdio.h>
#include <string.h>
#include <stdnoreturn.h>
#include <stdbool.h>
#include "bison_sintactical.h"


noreturn void invalid(const char *s);

void update_new_line();
extern int in_line_character_counter;

#define set_string_token(return_token) {\
    yylval.sval = strdup(yytext);\
    in_line_character_counter += strlen(yytext);\
    return return_token;\
}\

#define set_token(return_token) {\
    in_line_character_counter += strlen(yytext);\
    return yylval.token = return_token;\
}\


%}

%x COMMENT


ESPACIO         [ \t]*
N_LINE          [\n|\r|\r\n]
LETRA           [a-zA-Z]
NUMERO          [0-9]+
VARIABLE        _*{LETRA}([_0-9]|{LETRA})*

INT_TYPE        int
STRING_TYPE     string
VOID_TYPE       void

BASIC_TYPES     {INT_TYPE}|{STRING_TYPE}

KEYWORDS        int|void|string|if|else|while|return|write|writeln|read

PLUS            \+
MINUS           \-

SLASH           \/
MODULO          \%

ASTERISC        \*
AMPERSAND       "&"

COMP_LEQ        \<=
COMP_LSS        \<
COMP_EQU        ==
COMP_NEQ        !=
COMP_GTR        \>
COMP_GEQ        \>=
STRING          \"[^\"]*\"
ASIGNATION      =

IF              if
ELSE            else
WHILE           while

WRITE           write
WRITELN         writeln
READ            read

RETURN          return

SEMICOLON       ;
COMMA           ,
LEFT_PAREN      \(
RIGHT_PAREN     \)
LEFT_BRACKET    "["
RIGHT_BRACKET   "]"
LEFT_CURLY      \{
RIGHT_CURLY     \}

%%


"/*"                { BEGIN(COMMENT); }
<COMMENT>"*/"       { BEGIN(INITIAL); }
<COMMENT>{N_LINE}   { update_new_line(); }
<COMMENT>.          { ; }



{NUMERO}            { set_string_token(INT_VALUE); }
{STRING}            { set_string_token(STRING_VALUE); }

{VOID_TYPE}         { set_token(VOID_TYPE_); }

{BASIC_TYPES}       { set_string_token(TYPE_VALUE); }
{SEMICOLON}         { set_token(SEMI_COLON); }

{LEFT_PAREN}        { set_token(L_PAREN); }
{RIGHT_PAREN}       { set_token(R_PAREN); }

{LEFT_BRACKET}      { set_token(L_BRACK); }
{RIGHT_BRACKET}     { set_token(R_BRACK); }


{COMMA}             { set_token(COMMA_CONST); }
{ASTERISC}          { set_token(ASTERISC_CONST); }
{AMPERSAND}         { set_token(AMPERSAND_CONST); }

{COMP_LEQ}          { set_token(LEQ_CONST); }
{COMP_LSS}          { set_token(LSS_CONST); }
{COMP_EQU}          { set_token(EQU_CONST); }
{COMP_NEQ}          { set_token(NEQ_CONST); }
{COMP_GTR}          { set_token(GTR_CONST); }
{COMP_GEQ}          { set_token(GEQ_CONST); }
{ASIGNATION}        { set_token(ASSIGNATION_CONST); }

{PLUS}              { set_token(PLUS_CONST); }
{MINUS}             { set_token(MINUS_CONST); }

{SLASH}             { set_token(SLASH_CONST); }
{MODULO}            { set_token(MODULO_CONST); }

{LEFT_CURLY}        { set_token(L_CURLY); }
{RIGHT_CURLY}       { set_token(R_CURLY); }

{IF}                { set_token(IF_EXPR); }
{ELSE}              { set_token(ELSE_EXPR); }
{WHILE}             { set_token(WHILE_EXPR); }

{RETURN}            { set_token(RETURN_EXPR); }

{WRITE}             { set_token(WRITE_EXPR); }
{WRITELN}           { set_token(WRITELN_EXPR); }
{READ}              { set_token(READ_EXPR); }


{VARIABLE}          { set_string_token(IDENTIF); }

{ESPACIO}           { ++in_line_character_counter; }
{N_LINE}            { update_new_line(); }

.                   { printf("What is this: '%s'?\n", yytext); ++in_line_character_counter; }

%%

void free_flex_stack(){
    yy_delete_buffer(*yy_buffer_stack);
    yyfree(yy_buffer_stack);
}
