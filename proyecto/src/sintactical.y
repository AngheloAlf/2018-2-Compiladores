%{
#include <stdio.h>
#include <stdnoreturn.h>

// stuff from flex that bison needs to know about:
extern int yylex();
extern int yyparse();
extern FILE *yyin;

extern int lineCounter;
extern noreturn void invalid(const char *s);

extern char *yytext;

void yyerror(const char *s);
%}

%union {
	int ival;
	char *sval;
}

%token <ival> INT_VALUE
%token <sval> STRING_VALUE
%token <sval> IDENTIF
%token <sval> LEFT_PARENTHESIS
%token <sval> RIGHT_PARENTHESIS
%token <sval> LEFT_BRACKET_
%token <sval> RIGHT_BRACKET_
%token <sval> LEFT_CURLY_
%token <sval> RIGHT_CURLY_

%token <sval> VOID_TYPE_
%token <sval> TYPE_VALUE

%token <sval> SEMI_COLON
%token <sval> COMMA_CONST
%token <sval> ASTERISC_CONST
%token <sval> AMPERSAND_CONST

%token <sval> ASSIGNATION_CONST
%token <sval> COMPARATORS

%token <sval> PLUS_CONST
%token <sval> MINUS_CONST
%token <sval> MUL_OPERATION


%token <sval> IF_EXPR
%token <sval> ELSE_EXPR
%token <sval> WHILE_EXPR
%token <sval> RETURN_EXPR

%token <sval> WRITE_EXPR
%token <sval> WRITELN_EXPR
%token <sval> READ_EXPR



%%

program:
    declaration_list 
    ;


declaration_list:
    declaration_list declaration  
    | declaration
    ;

declaration:
    var_dec
    | fun_dec
    ;

var_dec:
    TYPE_VALUE IDENTIF SEMI_COLON
    | TYPE_VALUE ASTERISC_CONST IDENTIF SEMI_COLON
    | TYPE_VALUE IDENTIF LEFT_BRACKET_ INT_VALUE RIGHT_BRACKET_ SEMI_COLON
    ;


fun_dec:
    TYPE_VALUE IDENTIF LEFT_PARENTHESIS params RIGHT_PARENTHESIS compound_stmt 
    | VOID_TYPE_ IDENTIF LEFT_PARENTHESIS params RIGHT_PARENTHESIS compound_stmt 
    ;


params:
    VOID_TYPE_
    | param_list
    ;

param_list:
    param_list COMMA_CONST param 
    | param
    ;

param:
    TYPE_VALUE IDENTIF
    | TYPE_VALUE ASTERISC_CONST IDENTIF
    | TYPE_VALUE IDENTIF LEFT_BRACKET_ RIGHT_BRACKET_
    ;

compound_stmt:
    LEFT_CURLY_ local_decs statement_list RIGHT_CURLY_
    ;

local_decs:
    local_decs var_dec
    | %empty
    ;

statement_list:
    statement_list statement
    | %empty
    ;

statement:
    expression_stmt 
    | compound_stmt 
    | if_stmt
    | while_stmt
    | return_stmt
    | write_stmt
    ;

expression_stmt:
    expression SEMI_COLON
    | SEMI_COLON
    ;

if_stmt:
    IF_EXPR LEFT_PARENTHESIS expression RIGHT_PARENTHESIS statement else_stmt
    ;

else_stmt:
    ELSE_EXPR statement
    | %empty
    ;

while_stmt:
    WHILE_EXPR LEFT_PARENTHESIS expression RIGHT_PARENTHESIS statement
    ;

return_stmt:
    RETURN_EXPR SEMI_COLON
    | RETURN_EXPR expression SEMI_COLON
    ;

write_stmt:
    WRITE_EXPR LEFT_PARENTHESIS expression RIGHT_PARENTHESIS SEMI_COLON
    | WRITELN_EXPR LEFT_PARENTHESIS RIGHT_PARENTHESIS SEMI_COLON
    ;

expression:
    var ASSIGNATION_CONST expression  
    | comp_exp
    ;

var:
    IDENTIF
    | variable_array_index
    | ASTERISC_CONST IDENTIF
    ;

comp_exp:
    e  COMPARATORS  e
    | e
    ;

e:
    e addop t
    | t
    ;

addop:
    PLUS_CONST
    | MINUS_CONST
    ;

t:
    t mulop f 
    | f
    ;

mulop:
    ASTERISC_CONST
    | MUL_OPERATION
    ;

f:
    MINUS_CONST f
    | AMPERSAND_CONST factor 
    | ASTERISC_CONST factor
    | factor
    ;

factor:
    LEFT_PARENTHESIS expression RIGHT_PARENTHESIS
    | fun_call
    | read_stmt
    | ASTERISC_CONST IDENTIF
    | IDENTIF
    | variable_array_index
    | INT_VALUE
    | STRING_VALUE
    ;

variable_array_index:
    IDENTIF LEFT_BRACKET_ expression RIGHT_BRACKET_
    ;

read_stmt:
    READ_EXPR LEFT_PARENTHESIS RIGHT_PARENTHESIS
    ;

fun_call:
    IDENTIF LEFT_PARENTHESIS args RIGHT_PARENTHESIS
    ;

args: 
    arg_list
    | %empty
    ;

arg_list:
    arg_list COMMA_CONST expression 
    | expression
    ;



%% 

void yyerror(const char *s){
    printf("line: %i ", lineCounter);
    printf("%s\n",s);
    printf("yytext: %s\n", yytext);
    // invalid(s);
}
