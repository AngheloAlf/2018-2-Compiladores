%{
#include <stdio.h>
#include <string.h>
#include <stdnoreturn.h>
#include <stdbool.h>

#include "program_flow.h"

// Who needs headers anyway?

extern int yylex();
extern int yyparse();
extern FILE *yyin;

extern int lineCounter;
extern int in_line_character_counter;
extern noreturn void invalid(const char *s);
extern void file_write(FILE *fp, int how_many, ...);
extern FILE *out_file;

extern char *yytext;

void yyerror(const char *s);
%}

%union {
    int token;
	char *sval;
}

%expect 1

%token <sval> INT_VALUE
%token <sval> STRING_VALUE
%token <sval> IDENTIF

%token <token> L_PAREN
%token <token> R_PAREN
%token <token> L_BRACK
%token <token> R_BRACK
%token <token> L_CURLY
%token <token> R_CURLY

%token <token> VOID_TYPE_
%token <sval> TYPE_VALUE

%token <token> SEMI_COLON
%token <token> COMMA_CONST
%token <token> ASTERISC_CONST
%token <token> AMPERSAND_CONST

%right <token> LEQ_CONST
%right <token> LSS_CONST
%right <token> EQU_CONST
%right <token> NEQ_CONST
%right <token> GTR_CONST
%right <token> GEQ_CONST
%right <token> ASSIGNATION_CONST

%left <token> PLUS_CONST
%left <token> MINUS_CONST
%left <token> SLASH_CONST
%left <token> MODULO_CONST

%token <token> IF_EXPR
%left <token> ELSE_EXPR
%token <token> WHILE_EXPR
%token <token> RETURN_EXPR

%token <token> WRITE_EXPR
%token <token> WRITELN_EXPR
%token <token> READ_EXPR


%destructor { free($$); } INT_VALUE
%destructor { free($$); } STRING_VALUE
%destructor { free($$); } IDENTIF

%destructor { free($$); } TYPE_VALUE


%type <sval> type_specifier
%type <sval> var

%type <token> args;
%type <token> arg_list;

%start program

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
    | fun_def
    ;

type_specifier:
    VOID_TYPE_                                                      { $$ = strdup("void"); }
    | TYPE_VALUE                                                    { $$ = $1; }
    ;

var_dec:
    type_specifier IDENTIF SEMI_COLON                               { declare_variable($1, $2, false, false, 0); free($1); free($2); }
    | type_specifier ASTERISC_CONST IDENTIF SEMI_COLON              { declare_variable($1, $3, true, false, 0); free($1); free($3); }
    | type_specifier IDENTIF L_BRACK INT_VALUE R_BRACK SEMI_COLON   { declare_variable($1, $2, false, true, atoi($4)); free($1); free($2); free($4); }
    ;

fun_def:
    func_signature compound_stmt                                    { end_function_definition(); }
    ;

fun_dec:
    func_signature SEMI_COLON                                       { end_function_declaration(); }
    ;

func_signature:
    type_specifier IDENTIF L_PAREN params R_PAREN                   { declare_new_function($1, $2); free($1); free($2); }
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
    TYPE_VALUE IDENTIF                                              { add_var_as_func_par($1, $2, false, false); free($1); free($2); }
    | TYPE_VALUE ASTERISC_CONST IDENTIF                             { add_var_as_func_par($1, $3, true, false); free($1); free($3); }
    | TYPE_VALUE IDENTIF L_BRACK R_BRACK                            { add_var_as_func_par($1, $2, false, true); free($1); free($2); }
    ;

compound_stmt:
    l_curly_bracket scope_local_decls statement_list R_CURLY        { end_scope(); }
    ;

l_curly_bracket:
    L_CURLY                                                         { new_scope(); }
    ;

scope_local_decls:
    local_decs
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
    if_expression statement else_stmt                               { add_expr("", expr_if_end); }
    ;

if_expression:
    IF_EXPR L_PAREN expression R_PAREN                              { add_expr("", expr_if); }
    ;

else_stmt:
    else_expression statement
    | %empty
    ;

else_expression:
    ELSE_EXPR                                                       { add_expr("", expr_else); }
    ;

while_stmt:
    while_expression statement                                      { add_expr("", expr_while_end); }
    ;

while_expression:
    while_identif L_PAREN expression R_PAREN                        { add_expr("", expr_while_condition); }
    ;

while_identif:
    WHILE_EXPR                                                      { add_expr("", expr_while); }
    ;

return_stmt:
    RETURN_EXPR SEMI_COLON                                          { add_return(expr_return_void); }
    | RETURN_EXPR expression SEMI_COLON                             { add_return(expr_return_expr); }
    | RETURN_EXPR string_constant SEMI_COLON                        { add_return(expr_return_expr); }
    ;

write_stmt:
    WRITE_EXPR L_PAREN posible_argument R_PAREN SEMI_COLON          { add_expr("write", expr_write_func_call); }
    | WRITELN_EXPR L_PAREN R_PAREN SEMI_COLON                       { add_expr("writeln", expr_func_call); }
    ;

expression:
    var ASSIGNATION_CONST string_constant                           { assign_value_var($1); add_expr("", expr_assignation_var); free($1); }
    | var ASSIGNATION_CONST expression                              { assign_value_var($1); add_expr("", expr_assignation_var); free($1); }
    | comp_exp
    ;

var:
    IDENTIF                                                         { $$ = $1; verify_var_declared($1, IS_WHATEVER, expr_var); add_expr($1, expr_var); }
    | IDENTIF L_BRACK expression R_BRACK                            { $$ = $1; verify_var_declared($1, IS_ARRAY, expr_array); add_expr($1, expr_array); }
    | ASTERISC_CONST IDENTIF                                        { $$ = $2; verify_var_declared($2, IS_POINTER | IS_ARRAY, expr_var_asterisc); add_expr($2, expr_var_asterisc); }
    ;

comp_exp:
    e  LEQ_CONST  e                                                 { add_expr("", expr_comparation_leq); }
    | e  LSS_CONST  e                                               { add_expr("", expr_comparation_lss); }
    | e  EQU_CONST  e                                               { add_expr("", expr_comparation_equ); }
    | e  NEQ_CONST  e                                               { add_expr("", expr_comparation_neq); }
    | e  GTR_CONST  e                                               { add_expr("", expr_comparation_gtr); }
    | e  GEQ_CONST  e                                               { add_expr("", expr_comparation_geq); }
    | e
    ;

e:
    e PLUS_CONST t                                                  { add_expr("", expr_arithmetic_add); }
    | e MINUS_CONST t                                               { add_expr("", expr_arithmetic_sub); }
    | t                                                                                 
    ;

t:
    t ASTERISC_CONST f                                              { add_expr("", expr_arithmetic_mul); }
    | t SLASH_CONST f                                               { add_expr("", expr_arithmetic_div); }
    | t MODULO_CONST f                                              { add_expr("", expr_arithmetic_mod); }
    | f
    ;

f:
    MINUS_CONST f                                                   { add_expr("", expr_arithmetic_neg); }
    | factor
    ;

factor:
    L_PAREN expression R_PAREN
    | fun_call
    | read_stmt
    | var                                                           { free($1); }
    | AMPERSAND_CONST IDENTIF                                       { verify_var_declared($2, NOT_POINTER_NOT_ARRAY, expr_var_ampersand); add_expr($2, expr_var_ampersand); free($2); }
    | AMPERSAND_CONST IDENTIF L_BRACK expression R_BRACK            { verify_var_declared($2, IS_ARRAY, expr_array_ampersand); add_expr($2, expr_array_ampersand); free($2); }
    | INT_VALUE                                                     { add_expr($1, expr_int); free($1); }
    ;

read_stmt:
    READ_EXPR L_PAREN R_PAREN                                       { add_expr("read", expr_func_call); }
    ;

fun_call:
    IDENTIF L_PAREN args R_PAREN                                    { add_func_call($1, $3); free($1); }
    ;

args: 
    arg_list                                                        { $$ = $1; }
    | %empty                                                        { $$ = 0; }
    ;

arg_list:
    arg_list COMMA_CONST posible_argument                           { $$ = $$ + 1; }
    | posible_argument                                              { $$ = 1; }
    ;

posible_argument:
    string_constant                                                 { set_last_expr_as_func_arg(); }
    | expression                                                    { set_last_expr_as_func_arg(); }
    ;

string_constant:
    STRING_VALUE                                                    { add_string_constant($1); }
    ;

%% 

void yyerror(const char *s){
    fprintf(stderr, "line: %i.%i: %s\n", lineCounter, in_line_character_counter, s);
    fprintf(stderr, "\tyytext: %s\n", yytext);
    // invalid(s);
}
