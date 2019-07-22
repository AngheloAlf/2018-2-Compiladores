#ifndef PROGRAM_FLOW_H
#define PROGRAM_FLOW_H

#include <stdbool.h>

#include "types_enum.h"
#include "variable.h"
#include "scope.h"
#include "function.h"
#include "string_vector.h"
#include "expr_type_enum.h"
#include "expression.h"

// set-up
void vars_init_and_prepare();
void vars_free();


// vars
void add_declared_var(VarData *var);
void declare_variable(const char *type, char *id, bool pointer, bool array, int array_size);

void verify_var_declared(char *var_name, int flags, ExprTypeEnum operator_type);

void assign_value_var(char *var_name);

int get_all_declared_variables_size();

void new_scope();
void end_scope();

VarData *search_variable(const char *var_name, VarVector *func_params, ScopeData *scope);

VarVector *global_vars;
ScopeData *local_scope;

bool is_local_var;


/// funcs
void declare_new_function(const char *function_ret_type, char *function_name);
void end_function_declaration();
void end_function_definition();
void verify_func_declared(const char *func_name);
void add_func_call(const char *func_name, int arguments_amount);

void add_var_as_func_par(const char *type, char *id, bool pointer, bool array);
int get_parameters_size();
void set_vars_ids();

void verify_return_expr(ExprTypeEnum expr);
void add_return(ExprTypeEnum expr);

FuncVector *func_vector;
VarVector *param_list;


/// strings
void add_string_constant(const char *string);
void set_strings_ids();

StringVector *strings_constants;


// exprs
void add_expr(const char *expr, ExprTypeEnum expr_type);
void set_last_expr_as_func_arg();

ExprData *last_expression;

ExprVector *if_else_stack;
ExprVector *while_stack;

#endif /* PROGRAM_FLOW_H */
