#ifndef EXPR_VECTOR_H
#define EXPR_VECTOR_H

#include <stdbool.h>

#include "cadts_vector.h"

#include "expr_type.h"

typedef struct{
    char *expr;
    ExprType type;

    bool is_func_argument;
    int arguments_amount;

    bool is_flow_control;
    int flow_control_id;
    bool has_else;

    bool has_fake_var;
    int fake_var_id;
    bool is_fake_expr;

    int line;
    int column;
} ExprData;
CADTS_VECTOR(ExprVector, ExprData*)

#include "var_vector.h"

ExprData *ExprData_init(const char *expr, ExprType expr_type, int line, int column);
void ExprData_free(ExprData *data);
void ExprData_print(const ExprData *data);
ExprData *ExprData_copy(const ExprData *other_expr);
ExprData *ExprData_fake_expr(const VarData *fake_var, const ExprData *real_expr);

void ExprVector_clean(ExprVector *vec);
void ExprVector_print(ExprVector *vec);

#endif /* EXPR_VECTOR_H */
