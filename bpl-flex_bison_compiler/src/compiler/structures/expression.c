#include "expression.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "util.h"

ExprData *ExprData_init(const char *expr, ExprTypeEnum expr_type, int line, int column){
    ExprData *data = malloc(sizeof(ExprData));
    data->expr = strdup(expr);
    data->type = expr_type;
    data->value_in_stack = false;

    data->is_func_argument = false;
    data->arguments_amount = 0;

    data->is_flow_control = false;
    data->flow_control_id = 0;
    data->has_else = false;

    data->line = line;
    data->column = column;
    return data;
}
void ExprData_free(ExprData *data){
    free(data->expr);
    free(data);
}
void ExprData_print(const ExprData *data){
    printf("expression:\n");
    printf("\texpr: %s\n", data->expr);
    printf("\ttype: %s\n", ExprTypeEnum_name(data->type));
    printf("\tvalue_in_stack: %s\n", bool_name(data->value_in_stack));
    printf("\tis_func_argument: %s\n", bool_name(data->is_func_argument));

    printf("\tline: %i\n", data->line);
    printf("\tcolumn: %i\n", data->column);
}
ExprData *ExprData_copy(const ExprData *other_expr){
    ExprData *data = malloc(sizeof(ExprData));
    data->expr = strdup(other_expr->expr);
    data->type = other_expr->type;
    data->value_in_stack = other_expr->value_in_stack;

    data->is_func_argument = other_expr->is_func_argument;
    data->arguments_amount = other_expr->arguments_amount;

    data->is_flow_control = other_expr->is_flow_control;
    data->flow_control_id = other_expr->flow_control_id;
    data->has_else = other_expr->has_else;

    data->line = other_expr->line;
    data->column = other_expr->column;
    return data;
}
ExprData *ExprData_stack(const ExprData *other){
    ExprData *data = malloc(sizeof(ExprData));
    data->expr = strdup(ExprTypeEnum_name(other->type));
    data->type = other->type;
    data->value_in_stack = true;

    data->is_func_argument = other->is_func_argument;
    data->arguments_amount = other->arguments_amount;

    data->is_flow_control = other->is_flow_control;
    data->flow_control_id = other->flow_control_id;
    data->has_else = other->has_else;

    data->line = other->line;
    data->column = other->column;
    return data;
}

void ExprVector_clean(ExprVector *vec){
    while(ExprVector_len(vec)){
        ExprData *data = ExprVector_endpop(vec);
        ExprData_free(data);
    }
}
void ExprVector_print(ExprVector *vec){
    for(int i = 0; i < ExprVector_len(vec); ++i){
        ExprData_print(ExprVector_item(vec, i));
    }
}
