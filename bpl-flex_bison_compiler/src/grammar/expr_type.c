#include "expr_type.h"

#include <stdlib.h>

const char *ExprType_name(ExprType expr_type){
    switch(expr_type){
        case expr_write_func_call:
            return "'write' function call";
        case expr_func_call:
            return "function call";
        case expr_return_expr:
            return "return expr;";
        case expr_return_void:
            return "return;";

        case expr_var:
            return "variable";
        case expr_var_asterisc:
            return "pointer to variable (*)";
        case expr_var_ampersand:
            return "address of variable (&)";

        case expr_array:
            return "array";
        case expr_array_ampersand:
            return "address of array (&)";

        case expr_if:
            return "if";
        case expr_if_end:
            return "if end";
        case expr_else:
            return "else";
        case expr_while:
            return "while";
        case expr_while_condition:
            return "while condition";
        case expr_while_end:
            return "while end";

        case expr_int:
            return "integer";
        case expr_str:
            return "string";

        case expr_comparation_leq:
            return "comparation: less or equal";
        case expr_comparation_lss:
            return "comparation: less";
        case expr_comparation_equ:
            return "comparation: equal";
        case expr_comparation_neq:
            return "comparation: not equal";
        case expr_comparation_gtr:
            return "comparation: greater";
        case expr_comparation_geq:
            return "comparation: greater or equal";

        case expr_arithmetic_add:
            return "arithmetic: addition";
        case expr_arithmetic_sub:
            return "arithmetic: substraction";
        case expr_arithmetic_mul:
            return "arithmetic: multiplication";
        case expr_arithmetic_div:
            return "arithmetic: division";
        case expr_arithmetic_mod:
            return "arithmetic: modulo";
        case expr_arithmetic_neg:
            return "arithmetic: negation";

        case expr_assignation_var:
            return "variable assignation";

        case expr_scope:
            return "scope";
        case expr_scope_end:
            return "end of scope";
        
        case expr_none:
            return "(!) none expression // if you are seeing this, it may be a bug";
    }
    return NULL;
}

bool ExprType_is_const(ExprType expr_type){
    return expr_type == expr_int || expr_type == expr_str;
}

bool ExprType_is_var(ExprType expr_type){
    switch(expr_type){
        case expr_var:
        case expr_var_asterisc:
        case expr_var_ampersand:
        case expr_array:
        case expr_array_ampersand:
            return true;
        default:
            return false;
    }
}
