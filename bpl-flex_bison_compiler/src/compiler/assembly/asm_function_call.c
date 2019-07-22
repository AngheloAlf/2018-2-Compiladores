#include "asm_register.h"

#include "ast_handler.h"

#include "error_handler.h"
#include "util.h"

#define check_var_type(var_to_pass, param, var_type, param_type) ((param->type == param_type) && (var_to_pass->type == var_type))

bool check_func_param_type(ExprContainer *container, VarData *func_argument, ExprData *actual_parameter){
    VarData *var_to_pass = NULL;
    if(actual_parameter->type != expr_int && actual_parameter->type != expr_str){
        var_to_pass = ScopeData_search_var_actual_or_upper_scope(container->scope, actual_parameter->expr);
        if(var_to_pass == NULL){
            var_to_pass = VarVector_search_var(container->function->paramList, actual_parameter->expr);
        }
        if(var_to_pass == NULL){
            var_to_pass = VarVector_search_var(global_vars, actual_parameter->expr);
        }
        // assert(var_to_pass != NULL);
        if(var_to_pass == NULL){
            fprintf(stderr, "[Warning] Error in line %i.%i\n", actual_parameter->line, actual_parameter->column);
            // TODO: throw error
            return false;
        }
    }
    bool is_valid = false;
    switch(func_argument->type){
        case int_type:
            if(actual_parameter->type == expr_int) return true;
            is_valid = check_var_type(var_to_pass, actual_parameter, int_type, expr_var)
                    || check_var_type(var_to_pass, actual_parameter, int_pointer, expr_var_asterisc)
                    || check_var_type(var_to_pass, actual_parameter, int_array, expr_array);
            break;
        case int_array:
            is_valid = check_var_type(var_to_pass, actual_parameter, int_array, expr_var)
                    || check_var_type(var_to_pass, actual_parameter, int_array, expr_array_ampersand);
            break;
        case int_pointer:
            is_valid = check_var_type(var_to_pass, actual_parameter, int_pointer, expr_var)
                    || check_var_type(var_to_pass, actual_parameter, int_type, expr_var_ampersand);
            break;
        case string_type:
            if(actual_parameter->type == expr_str) return true;
            is_valid = check_var_type(var_to_pass, actual_parameter, string_type, expr_var)
                    || check_var_type(var_to_pass, actual_parameter, string_pointer, expr_var_asterisc)
                    || check_var_type(var_to_pass, actual_parameter, string_array, expr_array);
            break;
        case string_array:
            is_valid = check_var_type(var_to_pass, actual_parameter, string_array, expr_var)
                    || check_var_type(var_to_pass, actual_parameter, string_array, expr_array_ampersand);
            break;
        case string_pointer:
            is_valid = check_var_type(var_to_pass, actual_parameter, string_pointer, expr_var)
                    || check_var_type(var_to_pass, actual_parameter, string_type, expr_var_ampersand);
            break;
        default:
            return false;
    }
    return is_valid;
}


void func_call_parse_arguments(ExprContainer *container, const ExprData *func_call_expr, FuncData *called_func, const char *register_name){
    const char *params_registers[6] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
    int parameters_left = VarVector_len(called_func->paramList);
    if(func_call_expr->arguments_amount != parameters_left){
        if(func_call_expr->arguments_amount < parameters_left){
            assert(func_call_expr->arguments_amount >= parameters_left); // TODO: remove
            error_not_enough_parameters(func_call_expr);
        }
        else{
            error_too_many_arguments_to_call(func_call_expr);
        }
    }
    assert(func_call_expr->arguments_amount == parameters_left);
    VarData *argument;
    ExprData *func_param;
    while(--parameters_left >= 0){
        assert(ExprVector_len(container->exprs_stack) > 0);
        if(ExprVector_len(container->exprs_stack) <= 0){
            printf("fatal error while calling func '%s'\n", called_func->name);
            exit(-1);
        }

        func_param = ExprVector_endpop(container->exprs_stack);
        if(!func_param->is_func_argument){
            ExprData_print(func_param);
            assert(func_param->is_func_argument); // TODO: remove
            error_not_enough_parameters(func_call_expr);
        }

        argument = VarVector_item(called_func->paramList, parameters_left);
        if(!check_func_param_type(container, argument, func_param)){
            error_wrong_param_type_for_calling_func(func_call_expr);
        }

        if(parameters_left >= 6){
            // push argument into stack
            load_expression_into_register(container, func_param, register_name);
            fprintf(container->out_file, "\tpushq\t%%%s # <push> %s\n", register_name, func_param->expr);
        }
        else{
            // load argument into register
            load_expression_into_register(container, func_param, params_registers[parameters_left]);
        }

        ExprData_free(func_param);
    }
}

ExprTypeEnum load_func_call_into_register(ExprContainer *container, ExprData *func_call_expr, const char *register_name){
    assert(func_call_expr->type == expr_func_call);
    const char *func_name = func_call_expr->expr;

    FuncData *called_func = FuncVector_search_func(func_vector, func_name);
    if(called_func == NULL){
        error_calling_not_declared_func(func_call_expr);
    }

    fprintf(container->out_file, "\t# set-up to call '%s'\n", func_name);

    int parameters_left = VarVector_len(called_func->paramList);
    int stacked_parameters = parameters_left - 6;

    // align stack
    if(stacked_parameters > 0 && (stacked_parameters * 8) % 16 != 0){
        fprintf(container->out_file, "\tsubq\t$8, %%rsp\n");
    }

    if(container->stack_size % 2 != 0){
        fprintf(container->out_file, "\tsubq\t$8, %%rsp\n");
    }

    // push and load arguments 
    func_call_parse_arguments(container, func_call_expr, called_func, register_name);

    // call function
    fprintf(container->out_file, "\tcall\t%s\n", func_name);

    // restore memory to stack
    if(stacked_parameters > 0){
        int stack_par_size = get_aligned_stack_size(8*stacked_parameters);
        fprintf(container->out_file, "\taddq\t$%i, %%rsp\n", stack_par_size);
    }

    if(container->stack_size % 2 != 0){
        fprintf(container->out_file, "\taddq\t$8, %%rsp\n");
    }

    // move return value into register
    if(called_func->type != void_type){
        fprintf(container->out_file, "\tmovq\t%%rax, %%%s\n", register_name);
    }

    fprintf(container->out_file, "\t# end the call of '%s'\n\n", func_name);

    return get_ExprType_const(called_func->type);
}
