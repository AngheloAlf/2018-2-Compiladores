#include "error_handler.h"

#include <stdlib.h>
#include <stdio.h>

#include "variable.h"
#include "scope.h"
#include "function.h"

extern int lineCounter;
extern int in_line_character_counter;

noreturn void error_var(const char *message, const char *var){
    fprintf(stderr, "[ERROR] Line %i, column %i \n\t", lineCounter, in_line_character_counter);
    fprintf(stderr, message, var);
    fprintf(stderr, "\n\n");
    // fprintf(stderr, "dumping vars\n");
    // printf("Globals:\n");
    // VarVector_print(global_vars);
    // printf("\nLocals:\n");
    // ScopeData_print_vars(local_scope);
    exit(-1);
}

noreturn void error_var_already_declared_as_func_param(const char *var_name){
    error_var("[ERROR] The variable '%s' is already declared as a function parameter.", var_name);
}

noreturn void error_var_already_declared_in_local_scope(const char *var_name){
    error_var("[ERROR] The variable '%s' is already declared as local variable in this scope.", var_name);
}

noreturn void error_var_already_declared_as_global(const char *var_name){
    error_var("[ERROR] The variable '%s' is already declared as global.", var_name);
}

noreturn void error_var_not_declared(const char *var_name){
    error_var("[ERROR] The variable '%s' has not been declared.", var_name);
}


void error_func(const char *message, const char *other){
    fprintf(stderr, message, other);
    // fprintf(stderr, "dumping funcs\n");
    // FuncVector_print(func_vector);
    // exit(-1);
}

void error_not_declared_func(const char *func){
    error_func("[Warning] The function '%s' has not been declared\n", func);
}

void error_not_void_not_return(const char *func){
    error_func("[Warning] The non-void function '%s' does not has a return.\n", func);
}

void error_wrong_return_type(const char *func, const char *expected_type, const char *actual_type){
    fprintf(stderr, "[Warning] Expected type '%s', got type '%s'.\n", expected_type, actual_type);
    error_func("[Warning] Wrong return type for function '%s'.\n", func);
}


void error_expr(const char *message, const ExprData *expr_data){
    fprintf(stderr, "[Warning] Line %i, column %i \n\t", expr_data->line, expr_data->column);
    fprintf(stderr, message, expr_data->expr);
    // exit(-1);
}

void error_not_enough_parameters(const ExprData *func){
    error_expr("[Warning] Not enough parameters to call the function '%s'.\n", func);
}

void error_too_many_arguments_to_call(const ExprData *func){
    error_expr("[Warning] Too many arguments when calling function '%s'.\n", func);
}

void error_calling_not_declared_func(const ExprData *func){
    error_expr("[Warning] Trying to call the not declared function '%s'.\n", func);
}

void error_wrong_param_type_for_calling_func(const ExprData *func){
    error_expr("[Warning] Wrong parameter type when calling '%s'.\n", func);
}
