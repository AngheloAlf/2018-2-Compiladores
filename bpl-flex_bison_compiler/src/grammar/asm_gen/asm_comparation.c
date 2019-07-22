#include "asm_expr.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "types_enum.h"

#include "program_flow.h"

TypesEnum store_comparation_in_fake_var(ExprContainer *container, const ExprData *comp_expression, const char *register_name){
    ExprType comp_type = comp_expression->type;
    assert(comp_expression->has_fake_var);
    assert(comp_type == expr_comparation_leq || comp_type == expr_comparation_lss || comp_type == expr_comparation_equ || comp_type == expr_comparation_neq || comp_type == expr_comparation_gtr || comp_type == expr_comparation_geq);

    fprintf(container->out_file, "\t# calculating '%s'\n", ExprType_name(comp_type));

    // store right side of expression in memory, calculating its value if it is necessary
    assert(ExprVector_len(container->exprs_stack) > 0);
    ExprData *right = ExprVector_endpop(container->exprs_stack);
    assert(right->has_fake_var);
    ExprData *right_fake_expr_var = make_fake_expr(container->scope, right);
    ExprType fake_var_type = store_expression_in_fake_var(container, right, right_fake_expr_var, register_name);

    // storing left side of expression in memory, calculating its value if it is necessary
    ExprData *dest_expr = make_fake_expr(container->scope, comp_expression);
    ExprType left_type = store_stackpop_in_fake_var(container, dest_expr, register_name);
    assert(fake_var_type == left_type);

    // do the comparation
    load_var_into_register(container, dest_expr, "rax");
    // load_var_into_register(container, right_fake_expr_var, "rdi");
    VarData *right_fake_var = get_fake_var(container->scope, right_fake_expr_var->fake_var_id);
    fprintf(container->out_file, "\tcmpq\t-%i(%%rbp), %%rax\n", right_fake_var->var_id);

    // set 0 or 1 depending of the result of the comparation
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
    store_register_in_var(container, dest_expr, "rax");

    ExprData_free(right_fake_expr_var);
    ExprData_free(right);
    ExprVector_endadd(container->exprs_stack, dest_expr);

    fprintf(container->out_file, "\t# end of '%s'\n\n", ExprType_name(comp_type));

    return fake_var_type;
}
