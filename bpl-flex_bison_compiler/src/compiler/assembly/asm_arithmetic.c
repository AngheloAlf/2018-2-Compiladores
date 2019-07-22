#include "asm_register.h"

#include "expr_type_enum.h"

/*

void arithmetic_aux_add(ExprContainer *container, const char *register_name){
    // loading left of expression into a register
    load_stack_into_register(container, "rax");
    // loading right of expression into a register
    load_stack_into_register(container, register_name);
    // performing
    fprintf(container->out_file, "\taddq\t%%%s, %%rax\n", register_name);
    // storing result in memory
    store_register_in_stack(container, "rax");
}

void arithmetic_aux_sub(ExprContainer *container, const char *register_name){
    // loading left of expression into a register
    load_stack_into_register(container, "rax");
    // loading right of expression into a register
    load_stack_into_register(container, register_name);
    // performing
    fprintf(container->out_file, "\tsubq\t%%%s, %%rax\n", register_name);
    // storing result in memory
    store_register_in_stack(container, "rax");
}

void arithmetic_aux_mul(ExprContainer *container, const char *register_name){
    // loading left of expression into a register
    load_stack_into_register(container, "rax");
    // loading right of expression into a register
    load_stack_into_register(container, register_name);
    // performing
    fprintf(container->out_file, "\timulq\t%%%s, %%rax\n", register_name);
    // storing result in memory
    store_register_in_stack(container, "rax");
}

void arithmetic_aux_div(ExprContainer *container, const char *register_name){
    // loading left of expression into a register
    load_stack_into_register(container, "rax");
    // loading right of expression into a register
    load_stack_into_register(container, register_name);
    // performing
    fprintf(container->out_file, "\tcqto\n\tidivq\t%%%s\n", register_name);
    // storing result in memory
    store_register_in_stack(container, "rax");
}

void arithmetic_aux_mod(ExprContainer *container, const char *register_name){
    // loading left of expression into a register
    load_stack_into_register(container, "rax");
    // loading right of expression into a register
    load_stack_into_register(container, register_name);
    // performing
    fprintf(container->out_file, "\tcqto\n\tidivq\t%%%s\n", register_name);
    // storing result in memory
    store_register_in_stack(container, "rdx");
}

void arithmetic_aux_neg(ExprContainer *container){
    load_stack_into_register(container, "rax");
    // performing negation
    fprintf(container->out_file, "\tnegq\t%%rax\n");
    // storing result in memory
    store_register_in_stack(container, "rax");
}


void store_arithmetic_in_stack(ExprContainer *container, const ExprData *arithmetic_expression, const char *register_name){
    ExprTypeEnum ar_type = arithmetic_expression->type;
    assert(ar_type == expr_arithmetic_add || ar_type == expr_arithmetic_sub || ar_type == expr_arithmetic_mul || ar_type == expr_arithmetic_div || ar_type == expr_arithmetic_mod || ar_type == expr_arithmetic_neg);

    fprintf(container->out_file, "\t# calculating '%s'\n", ExprTypeEnum_name(ar_type));

    ExprData *right = ExprVector_endpop(container->exprs_stack);
    load_expression_into_register(container, right, register_name);
    store_register_in_stack(container, register_name);
    ExprData *stack_expr = ExprData_stack(right);
    stack_expr->type = expr_int;
    stack_expr->is_func_argument = arithmetic_expression->is_func_argument;
    ExprData_free(right);

    if(ar_type != expr_arithmetic_neg){
        // storing left side of expression in memory, calculating its value if it is necessary
        ExprData *left = ExprVector_endpop(container->exprs_stack);
        if(left->value_in_stack){

        }
        load_expression_into_register(container, left, register_name);
        store_register_in_stack(container, register_name);
        ExprData_free(left);
    }

    switch(ar_type){
        case expr_arithmetic_add:
            arithmetic_aux_add(container, register_name);
            break;
        case expr_arithmetic_sub:
            arithmetic_aux_sub(container, register_name);
            break;
        case expr_arithmetic_mul:
            arithmetic_aux_mul(container, register_name);
            break;
        case expr_arithmetic_div:
            arithmetic_aux_div(container, register_name);
            break;
        case expr_arithmetic_mod:
            arithmetic_aux_mod(container, register_name);
            break;
        case expr_arithmetic_neg:
            arithmetic_aux_neg(container);
            break;
        default:
            assert(!"What?");
            break;
    }
    fprintf(container->out_file, "\t# end of '%s'\n\n", ExprTypeEnum_name(ar_type));

    ExprVector_endadd(container->exprs_stack, stack_expr);
}
*/

void arithmetic_negation(ExprContainer *container, const ExprData *arithmetic_expression, const char *register_name){

    ExprData *right = ExprVector_endpop(container->exprs_stack);
    load_expression_into_register(container, right, register_name);

    fprintf(container->out_file, "\tmovq\t%%%s, %%rax\n", register_name);
    fprintf(container->out_file, "\tnegq\t%%rax\n");
    store_register_in_stack(container, "rax");

    ExprData *stack_expr = ExprData_stack(right);
    stack_expr->type = expr_int;
    stack_expr->is_func_argument = arithmetic_expression->is_func_argument;
    ExprData_free(right);

    ExprVector_endadd(container->exprs_stack, stack_expr);
}


void store_arithmetic_in_stack(ExprContainer *container, const ExprData *arithmetic_expression, const char *register_name){
    ExprTypeEnum ar_type = arithmetic_expression->type;
    assert(ar_type == expr_arithmetic_add || ar_type == expr_arithmetic_sub || ar_type == expr_arithmetic_mul || ar_type == expr_arithmetic_div || ar_type == expr_arithmetic_mod || ar_type == expr_arithmetic_neg);

    fprintf(container->out_file, "\t# calculating '%s'\n", ExprTypeEnum_name(ar_type));

    if(ar_type == expr_arithmetic_neg){
        arithmetic_negation(container, arithmetic_expression, register_name);
    }
    else{
        ExprData *right = ExprVector_endpop(container->exprs_stack);
        ExprData *left = ExprVector_endpop(container->exprs_stack);

        if(!right->value_in_stack){
            load_expression_into_register(container, right, register_name);
            store_register_in_stack(container, register_name);
        }
        if(!left->value_in_stack){
            load_expression_into_register(container, left, register_name);
            store_register_in_stack(container, register_name);
        }

        ExprData *stack_expr = ExprData_stack(right);
        stack_expr->type = expr_int;
        stack_expr->is_func_argument = arithmetic_expression->is_func_argument;


        if(left->value_in_stack && !right->value_in_stack){
            // loading right of expression into a register
            load_stack_into_register(container, register_name);
            // loading left of expression into a register
            load_stack_into_register(container, "rax");
        }
        else{
            // loading left of expression into a register
            load_stack_into_register(container, "rax");
            // loading right of expression into a register
            load_stack_into_register(container, register_name);
        }

        ExprData_free(left);
        ExprData_free(right);

        switch(ar_type){
            case expr_arithmetic_add:
                fprintf(container->out_file, "\taddq\t%%%s, %%rax\n", register_name);
                break;
            case expr_arithmetic_sub:
                fprintf(container->out_file, "\tsubq\t%%%s, %%rax\n", register_name);
                break;
            case expr_arithmetic_mul:
                fprintf(container->out_file, "\timulq\t%%%s, %%rax\n", register_name);
                break;
            case expr_arithmetic_div:
            case expr_arithmetic_mod:
                fprintf(container->out_file, "\tcqto\n\tidivq\t%%%s\n", register_name);
                break;
            default:
                assert(!"What?");
                break;
        }
        if(ar_type != expr_arithmetic_mod){
            store_register_in_stack(container, "rax");
        }
        else{
            store_register_in_stack(container, "rdx");
        }
        ExprVector_endadd(container->exprs_stack, stack_expr);
    }
    fprintf(container->out_file, "\t# end of '%s'\n\n", ExprTypeEnum_name(ar_type));
}
