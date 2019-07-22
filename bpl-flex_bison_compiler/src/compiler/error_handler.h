#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <stdnoreturn.h>

#include "expression.h"


noreturn void error_var(const char *message, const char *var);
noreturn void error_var_already_declared_in_func_param(const char *var_name);
noreturn void error_var_already_declared_in_local_scope(const char *var_name);
noreturn void error_var_already_declared_as_global(const char *var_name);
noreturn void error_var_not_declared(const char *var_name);

void error_func(const char *message, const char *other);
void error_not_declared_func(const char *func);
void error_not_void_not_return(const char *func);
void error_wrong_return_type(const char *func, const char *expected_type, const char *actual_type);

void error_expr(const char *message, const ExprData *expr_data);
void error_not_enough_parameters(const ExprData *func);
void error_too_many_arguments_to_call(const ExprData *func);
void error_calling_not_declared_func(const ExprData *func);
void error_wrong_param_type_for_calling_func(const ExprData *func);

#endif /* ERROR_HANDLER_H */
