#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <stdnoreturn.h>

#include "expr_vector.h"


noreturn void error_var(const char *message, const char *var);
noreturn void error_var_already_declared_in_func_param(const char *var_name);
noreturn void error_var_already_declared_in_local_scope(const char *var_name);
noreturn void error_var_already_declared_as_global(const char *var_name);
noreturn void error_var_not_declared(const char *var_name);

noreturn void error_func(const char *message, const char *other);
noreturn void error_not_declared_func(const char *func);
noreturn void error_not_void_not_return(const char *func);
noreturn void error_wrong_return_type(const char *func, const char *expected_type, const char *actual_type);

noreturn void error_expr(const char *message, ExprData *expr_data);
noreturn void error_not_enough_parameters(ExprData *func);
noreturn void error_too_many_arguments_to_call(ExprData *func);
noreturn void error_calling_not_declared_func(ExprData *func);
noreturn void error_wrong_param_type_for_calling_func(ExprData *func);
noreturn void error_var_wrong_type(ExprData *var_name);

#endif /* ERROR_HANDLER_H */
