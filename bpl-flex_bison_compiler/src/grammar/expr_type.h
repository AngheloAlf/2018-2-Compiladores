#ifndef EXPR_TYPE_H
#define EXPR_TYPE_H

#include <stdbool.h>


typedef enum{
    expr_none, // for errors and stuff

    expr_write_func_call,

    expr_func_call,
    expr_return_expr,
    expr_return_void,

    expr_var,
    expr_var_asterisc,
    expr_var_ampersand,

    expr_array,
    expr_array_ampersand,

    expr_if,
    expr_if_end,
    expr_else,
    expr_while,
    expr_while_condition,
    expr_while_end,

    expr_int,
    expr_str,

    expr_comparation_leq,
    expr_comparation_lss,
    expr_comparation_equ,
    expr_comparation_neq,
    expr_comparation_gtr,
    expr_comparation_geq,

    expr_arithmetic_add,
    expr_arithmetic_sub,
    expr_arithmetic_mul,
    expr_arithmetic_div,
    expr_arithmetic_mod,
    expr_arithmetic_neg,

    expr_assignation_var,

    expr_scope,
    expr_scope_end,
} ExprType;

const char *ExprType_name(ExprType expr_type);
bool ExprType_is_const(ExprType expr_type);
bool ExprType_is_var(ExprType expr_type);

#endif /* EXPR_TYPE_H */
