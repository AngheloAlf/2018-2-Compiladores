#ifndef EXPR_VECTOR_H
#define EXPR_VECTOR_H

#include <stdbool.h>

#include "cadts_vector.h"

#include "expr_type_enum.h"

typedef struct{
    char *expr;
    ExprTypeEnum type;
    bool value_in_stack;

    bool is_func_argument;
    int arguments_amount;

    bool is_flow_control;
    int flow_control_id;
    bool has_else;

    int line;
    int column;
} ExprData;
CADTS_VECTOR(ExprVector, ExprData*)

#include "variable.h"

ExprData *ExprData_init(const char *expr, ExprTypeEnum expr_type, int line, int column);
void ExprData_free(ExprData *data);
void ExprData_print(const ExprData *data);
ExprData *ExprData_copy(const ExprData *other_expr);
ExprData *ExprData_stack(const ExprData *other);

void ExprVector_clean(ExprVector *vec);
void ExprVector_print(ExprVector *vec);

#endif /* EXPR_VECTOR_H */
