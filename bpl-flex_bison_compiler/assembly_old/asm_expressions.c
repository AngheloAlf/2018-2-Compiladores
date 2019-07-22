#include "asm_register.h"

#include <stdio.h>

#include "variable.h"
#include "function.h"
#include "expression.h"

#include "ast_handler.h"

void parse_var_assignation(ExprContainer *container, const ExprData *expression){
    const char *register_name = "r12";

    fprintf(container->out_file, "\t# start of '%s'\n", ExprType_name(expression->type));
    assert(ExprVector_len(container->exprs_stack)>0);
    ExprData *right_assignation = ExprVector_endpop(container->exprs_stack);
    ExprTypeEnum right_type = load_expression_into_register(container, right_assignation, register_name);

    ExprData *fake_expr_var = make_fake_expr(container->scope, expression);
    store_register_in_expression(container, fake_expr_var, register_name);

    assert(ExprVector_len(container->exprs_stack)>0);
    ExprData *left_assignation = ExprVector_endpop(container->exprs_stack);
    VarData *left_var = search_variable(left_assignation->expr, container->function->paramList, container->scope);
    if(get_ExprType_const(left_var->type) != right_type){
        error_var_wrong_type(left_assignation);
    }
    store_register_in_expression(container, left_assignation, register_name);

    ExprVector_endadd(container->exprs_stack, fake_expr_var);
    ExprData_free(left_assignation);
    ExprData_free(right_assignation);

    fprintf(container->out_file, "\t# end of '%s'\n", ExprType_name(expression->type));
}

void parse_func_call(ExprContainer *container, ExprData *func_call_expr){
    const char *register_name = "r13";

    load_func_call_into_register(container, func_call_expr, register_name);
    FuncData *function_called = FuncVector_search_func(func_vector, func_call_expr->expr);
    if(function_called->type != void_type){
        VarData *fake_var = get_fake_var(container->scope, func_call_expr->fake_var_id);
        ExprData *fake_expr = ExprData_fake_expr(fake_var, func_call_expr);
        store_register_in_expression(container, fake_expr, register_name);
        ExprVector_endadd(container->exprs_stack, fake_expr);
    }
}

/// 'write()' function call 
void parse_write_func_call(ExprContainer *container, ExprData *func_call_expr){
    const char *register_name = "r13";

    const char *func_name = func_call_expr->expr;
    const char *asm_str;
    const char *first_argument = "rdi";
    const char *write_type_name;
    
    assert(func_call_expr->type == expr_write_func_call);

    asm_str = "\n\t# set-up to call '%s'\n";
    fprintf(container->out_file, asm_str, func_name);

    if(ExprVector_len(container->exprs_stack) == 0){
        // no more expressions
        // error!
        printf("error while calling func '%s'\n", func_name);
        exit(-1);
    }

    ExprData *func_param = ExprVector_endpop(container->exprs_stack);
    if(!func_param->is_func_argument){
        error_not_enough_parameters(func_call_expr);
    }
    ExprTypeEnum expr_type = load_expression_into_register(container, func_param, register_name);
    // if(expr_type == expr_none){
    //     printf("%s\n", func_param->expr);
    // }
    assert(expr_type != expr_none);
    if(expr_type == expr_str){
        write_type_name = "string";
    }
    else{
        write_type_name = "int";
    }

    asm_str = "\tmovq\t%%%s, %%%s # %s -> %%%s\n";
    fprintf(container->out_file, asm_str, register_name, first_argument, func_param->expr, first_argument);
    ExprData_free(func_param);

    asm_str = "\tcall\t.write_%s\n";
    fprintf(container->out_file, asm_str, write_type_name);

    asm_str = "\t# cleaning up the call of '%s'\n\n";
    fprintf(container->out_file, asm_str, func_name);
}

void parse_return(ExprContainer *container, ExprData *return_type_expr){
    const char *register_name = "r12";

    const char *return_register = "rax";
    
    const char *asm_str;
    if(return_type_expr->type == expr_return_expr){
        ExprData *ret_expr = ExprVector_endpop(container->exprs_stack);

        ExprTypeEnum return_type = load_expression_into_register(container, ret_expr, register_name);
        ExprTypeEnum expected_type = get_ExprType_const(container->function->type);
        if(return_type != expected_type){
            error_wrong_return_type(container->function->name, ExprType_name(expected_type), ExprType_name(return_type));
        }
        asm_str = "\tmovq\t%%%s, %%%s # <return> %s\n";
        fprintf(container->out_file, asm_str, register_name, return_register, ret_expr->expr);

        ExprData_free(ret_expr);
    }
    asm_str = "\tjmp \t.%s_epilogue # return;\n";
    fprintf(container->out_file, asm_str, container->function->name);
}

void parse_arithmetic(ExprContainer *container, ExprData *arithmetic_expr){
    const char *register_name = "r13";

    store_arithmetic_in_fake_var(container, arithmetic_expr, register_name);
}

void parse_comparation(ExprContainer *container, ExprData *comparation_expr){
    const char *register_name = "r13";

    store_comparation_in_fake_var(container, comparation_expr, register_name);
}

void parse_if(ExprContainer *container, ExprData *expr){
    assert(expr->type == expr_if);
    assert(expr->is_flow_control);
    const char *register_name = "r14";
    int if_id = expr->flow_control_id;
    const char *asm_str;

    fprintf(container->out_file, "\t# start of '%s'\n", ExprType_name(expr->type));

    asm_str = ".%s_if_%i:\n";
    fprintf(container->out_file, asm_str, container->function->name, if_id);

    ExprData *condition = ExprVector_endpop(container->exprs_stack);
    load_expression_into_register(container, condition, register_name);

    asm_str = "\tcmpq\t$0, %%%s\n";
    fprintf(container->out_file, asm_str, register_name);

    asm_str = "\tje\t\t.%s_%s_%i\n";
    fprintf(container->out_file, asm_str, container->function->name, (expr->has_else ? "else" : "if_end"), if_id);

    ExprData_free(condition);

    fprintf(container->out_file, "\t# end of '%s'\n", ExprType_name(expr->type));
}
void parse_else(ExprContainer *container, ExprData *expr){
    assert(expr->type == expr_else);
    assert(expr->is_flow_control);
    int if_id = expr->flow_control_id;
    const char *asm_str;
    asm_str = "\tjmp\t\t.%s_if_end_%i\n";
    fprintf(container->out_file, asm_str, container->function->name, if_id);
    asm_str = ".%s_else_%i:\n";
    fprintf(container->out_file, asm_str, container->function->name, if_id);
}
void parse_if_end(ExprContainer *container, ExprData *expr){
    assert(expr->type == expr_if_end);
    assert(expr->is_flow_control);
    const char *asm_str = ".%s_if_end_%i:\n";
    fprintf(container->out_file, asm_str, container->function->name, expr->flow_control_id);
}

void parse_while(ExprContainer *container, ExprData *expr){
    assert(expr->type == expr_while);
    assert(expr->is_flow_control);
    int while_id = expr->flow_control_id;

    fprintf(container->out_file, "\t# start of '%s'\n", ExprType_name(expr->type));
    fprintf(container->out_file, ".%s_while_%i:\n", container->function->name, while_id);
    fprintf(container->out_file, "\t# end of '%s'\n", ExprType_name(expr->type));
}
void parse_while_condition(ExprContainer *container, ExprData *expr){
    assert(expr->type == expr_while_condition);
    assert(expr->is_flow_control);
    const char *register_name = "r14";
    const char *asm_str;
    int while_id = expr->flow_control_id;

    fprintf(container->out_file, "\t# start of '%s'\n", ExprType_name(expr->type));

    ExprData *condition = ExprVector_endpop(container->exprs_stack);
    load_expression_into_register(container, condition, register_name);

    asm_str = "\tcmpq\t$0, %%%s\n";
    fprintf(container->out_file, asm_str, register_name);
    asm_str = "\tje\t\t.%s_while_end_%i\n";
    fprintf(container->out_file, asm_str, container->function->name, while_id);

    ExprData_free(condition);

    fprintf(container->out_file, "\t# end of '%s'\n", ExprType_name(expr->type));
}
void parse_while_end(ExprContainer *container, ExprData *expr){
    assert(expr->type == expr_while_end);
    assert(expr->is_flow_control);
    int while_id = expr->flow_control_id;
    const char *asm_str;

    fprintf(container->out_file, "\t# start of '%s'\n", ExprType_name(expr->type));

    asm_str = "\tjmp\t\t.%s_while_%i\n";
    fprintf(container->out_file, asm_str, container->function->name, while_id);

    asm_str = ".%s_while_end_%i:\n";
    fprintf(container->out_file, asm_str, container->function->name, while_id);

    fprintf(container->out_file, "\t# end of '%s'\n", ExprType_name(expr->type));
}

void aux_write_function_exprs(FILE *output_file, FuncData *function, ScopeData *scope){
    if(function->type != void_type && !function->has_return){
        error_not_void_not_return(function->name);
    }
    ExprVector *exprs_vec = scope->exprs;
    int scope_index = 0;
    ExprVector *exprs_stack = ExprVector_init(4);

    ExprContainer container;
    container.out_file = output_file;
    container.function = function;
    container.scope = scope;
    container.exprs_stack = exprs_stack;

    for(int i = 0; i < ExprVector_len(exprs_vec); ++i){
        ExprData *expr = ExprVector_item(exprs_vec, i);
        // ExprData_print(expr);
        assert(expr->type != expr_none);

        switch(expr->type){
            case expr_scope:{
                    ScopeData *next_scope = ScopeVector_item(scope->scopes, scope_index);
                    aux_write_function_exprs(output_file, function, next_scope);

                    ++scope_index;
                }
                break;
            case expr_scope_end:
                break;

            case expr_int:
            case expr_str:
                ExprVector_endadd(exprs_stack, ExprData_copy(expr));
                break;

            case expr_var:
            case expr_var_asterisc:
            case expr_var_ampersand:
            case expr_array:
            case expr_array_ampersand:
                ExprVector_endadd(exprs_stack, ExprData_copy(expr));
                break;

            case expr_assignation_var:
                parse_var_assignation(&container, expr);
                break;

            case expr_func_call:
                parse_func_call(&container, expr);
                break;

            case expr_write_func_call:
                parse_write_func_call(&container, expr);
                break;

            case expr_return_void:
            case expr_return_expr:
                parse_return(&container, expr);
                break;

            case expr_arithmetic_add:
            case expr_arithmetic_sub:
            case expr_arithmetic_mul:
            case expr_arithmetic_div:
            case expr_arithmetic_mod:
            case expr_arithmetic_neg:
                parse_arithmetic(&container, expr);
                break;

            case expr_comparation_leq:
            case expr_comparation_lss:
            case expr_comparation_equ:
            case expr_comparation_neq:
            case expr_comparation_gtr:
            case expr_comparation_geq:
                parse_comparation(&container, expr);
                break;

            case expr_if:
                parse_if(&container, expr);
                break;
            case expr_else:
                parse_else(&container, expr);
                break;
            case expr_if_end:
                parse_if_end(&container, expr);
                break;

            case expr_while:
                parse_while(&container, expr);
                break;
            case expr_while_condition:
                parse_while_condition(&container, expr);
                break;
            case expr_while_end:
                parse_while_end(&container, expr);
                break;

            default:
                ExprData_print(expr);
                ExprVector_endadd(exprs_stack, ExprData_copy(expr));
                assert(!"This should not happen\n");
                printf("This should not happen\n");
                break;
        }
    }

    ExprVector_clean(exprs_stack);
    ExprVector_free(exprs_stack);
}

