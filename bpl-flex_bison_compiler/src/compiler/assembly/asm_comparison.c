#include "asm_register.h"

#include <assert.h>

void store_comparation_in_stack(ExprContainer *container, const ExprData *comp_expression, const char *register_name){
    ExprTypeEnum comp_type = comp_expression->type;
    assert(comp_type == expr_comparation_leq || comp_type == expr_comparation_lss || comp_type == expr_comparation_equ || comp_type == expr_comparation_neq || comp_type == expr_comparation_gtr || comp_type == expr_comparation_geq);

    fprintf(container->out_file, "\t# calculating '%s'\n", ExprTypeEnum_name(comp_type));

    // store right side of expression in memory, calculating its value if it is necessary
    assert(ExprVector_len(container->exprs_stack) > 1);
    ExprData *right = ExprVector_endpop(container->exprs_stack);
    ExprData *stack_expr = ExprData_stack(right);
    stack_expr->type = expr_int;
    stack_expr->is_func_argument = comp_expression->is_func_argument;
    load_expression_into_register(container, right, register_name);
    store_register_in_stack(container, register_name);
    ExprData_free(right);
    // storing left side of expression in memory, calculating its value if it is necessary
    ExprData *left = ExprVector_endpop(container->exprs_stack);
    load_expression_into_register(container, left, register_name);
    store_register_in_stack(container, register_name);
    ExprData_free(left);

    // do the comparison
    load_stack_into_register(container, "rax");
    load_stack_into_register(container, register_name);
    fprintf(container->out_file, "\tcmpq\t%%%s, %%rax\n", register_name);

    // set 0 or 1 depending of the result of the comparison
    switch(comp_type){
        case expr_comparation_leq:
            fprintf(container->out_file, "\tsetle\t%%al\n");
            break;
        case expr_comparation_lss:
            fprintf(container->out_file, "\tsetl\t%%al\n");
            break;
        case expr_comparation_equ:
            fprintf(container->out_file, "\tsete\t%%al\n");
            break;
        case expr_comparation_neq:
            fprintf(container->out_file, "\tsetne\t%%al\n");
            break;
        case expr_comparation_gtr:
            fprintf(container->out_file, "\tsetg\t%%al\n");
            break;
        case expr_comparation_geq:
            fprintf(container->out_file, "\tsetge\t%%al\n");
            break;
        default:
            assert(!"invalid comparation");
            break;
    }

    // move from 8bit register into 64 bit register and store in memory
    fprintf(container->out_file, "\tmovzbq\t%%al, %%rax\n");
    store_register_in_stack(container, "rax");

    fprintf(container->out_file, "\t# end of '%s'\n\n", ExprTypeEnum_name(comp_type));

    ExprVector_endadd(container->exprs_stack, stack_expr);
}
