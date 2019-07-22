#include "expr_vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "util.h"

ExprData *ExprData_init(const char *expr, ExprType expr_type, int line, int column){
    ExprData *data = malloc(sizeof(ExprData));
    data->expr = strdup(expr);
    data->type = expr_type;

    data->is_func_argument = false;
    data->arguments_amount = 0;

    data->is_flow_control = false;
    data->flow_control_id = 0;
    data->has_else = false;

    data->has_fake_var = false;
    data->fake_var_id = 0;
    data->is_fake_expr = false;

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
    printf("\ttype: %s\n", ExprType_name(data->type));
    printf("\tis_func_argument: %s\n", bool_name(data->is_func_argument));
    if(data->has_fake_var){
        printf("\tfake_var_id: %i\n", data->fake_var_id);
        printf("\tis_fake_expr: %s\n", bool_name(data->is_fake_expr));
    }
    printf("\tline: %i\n", data->line);
    printf("\tcolumn: %i\n", data->column);
}
ExprData *ExprData_copy(const ExprData *other_expr){
    ExprData *data = malloc(sizeof(ExprData));
    data->expr = strdup(other_expr->expr);
    data->type = other_expr->type;
    data->is_func_argument = other_expr->is_func_argument;
    data->arguments_amount = other_expr->arguments_amount;

    data->is_flow_control = other_expr->is_flow_control;
    data->flow_control_id = other_expr->flow_control_id;
    data->has_else = other_expr->has_else;

    data->has_fake_var = other_expr->has_fake_var;
    data->fake_var_id = other_expr->fake_var_id;
    data->is_fake_expr = other_expr->is_fake_expr;

    data->line = other_expr->line;
    data->column = other_expr->column;
    return data;
}
ExprData *ExprData_fake_expr(const VarData *fake_var, const ExprData *real_expr){
    assert(fake_var != NULL && real_expr != NULL);
    assert(real_expr->has_fake_var && real_expr->fake_var_id > 0);

    ExprData *data = malloc(sizeof(ExprData));
    data->expr = strdup(fake_var->id);
    data->type = expr_var;
    data->is_func_argument = real_expr->is_func_argument;
    data->arguments_amount = 0;

    data->is_flow_control = real_expr->is_flow_control;
    data->flow_control_id = real_expr->flow_control_id;
    data->has_else = real_expr->has_else;

    data->has_fake_var = true;
    data->fake_var_id = fake_var->fake_var_id;
    data->is_fake_expr = true;

    data->line = real_expr->line;
    data->column = real_expr->column;
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
