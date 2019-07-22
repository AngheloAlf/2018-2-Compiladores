#include "asm_register.h"


ExprTypeEnum arithmetic_aux_add(ExprContainer *container, ExprData *ari_fake_expr_var, ExprData *right_fake_expr_var, const char *register_name){
    // storing left side of expression in memory, calculating its value if it is necessary
    ExprTypeEnum left_type = store_stackpop_in_fake_var(container, ari_fake_expr_var, register_name);
    // loading left of expression into the correct register
    load_var_into_register(container, ari_fake_expr_var, "rax");
    // performing addition
    VarData *fake_var = get_fake_var(container->scope, right_fake_expr_var->fake_var_id);
    fprintf(container->out_file, "\taddq\t-%i(%%rbp), %%rax\n", fake_var->var_id);
    // storing addition result in memory
    store_register_in_var(container, ari_fake_expr_var, "rax");
    return left_type;
}

ExprTypeEnum arithmetic_aux_sub(ExprContainer *container, ExprData *ari_fake_expr_var, ExprData *right_fake_expr_var, const char *register_name){
    // storing left side of expression in memory, calculating it if it is necessary
    ExprTypeEnum left_type = store_stackpop_in_fake_var(container, ari_fake_expr_var, register_name);
    // loading left side of expression into the correct register
    load_var_into_register(container, ari_fake_expr_var, "rax");
    // performing substraction
    VarData *fake_var = get_fake_var(container->scope, right_fake_expr_var->fake_var_id);
    fprintf(container->out_file, "\tsubq\t-%i(%%rbp), %%rax\n", fake_var->var_id);
    // storing substraction result in memory
    store_register_in_var(container, ari_fake_expr_var, "rax");
    return left_type;
}

ExprTypeEnum arithmetic_aux_mul(ExprContainer *container, ExprData *ari_fake_expr_var, ExprData *right_fake_expr_var, const char *register_name){
    // storing left side of expression in memory, calculating it if it is necessary
    ExprTypeEnum left_type = store_stackpop_in_fake_var(container, ari_fake_expr_var, register_name);
    // loading left side of expression into the correct register
    load_var_into_register(container, ari_fake_expr_var, "rax");
    // performing multiplication
    VarData *fake_var = get_fake_var(container->scope, right_fake_expr_var->fake_var_id);
    fprintf(container->out_file, "\timulq\t-%i(%%rbp), %%rax\n", fake_var->var_id);
    // storing multiplication result in memory
    store_register_in_var(container, ari_fake_expr_var, "rax");
    return left_type;
}

ExprTypeEnum arithmetic_aux_div(ExprContainer *container, ExprData *ari_fake_expr_var, ExprData *right_fake_expr_var, const char *register_name){
    // storing left side of expression in memory, calculating it if it is necessary
    ExprTypeEnum left_type = store_stackpop_in_fake_var(container, ari_fake_expr_var, register_name);
    // loading left side of expression into the correct register
    load_var_into_register(container, ari_fake_expr_var, "rax");
    // performing division
    VarData *fake_var = get_fake_var(container->scope, right_fake_expr_var->fake_var_id);
    fprintf(container->out_file, "\tcqto\n\tidivq\t-%i(%%rbp)\n", fake_var->var_id);
    // storing division result in memory
    store_register_in_var(container, ari_fake_expr_var, "rax");
    return left_type;
}

ExprTypeEnum arithmetic_aux_mod(ExprContainer *container, ExprData *ari_fake_expr_var, ExprData *right_fake_expr_var, const char *register_name){
    // storing left side of expression in memory, calculating it if it is necessary
    ExprTypeEnum left_type = store_stackpop_in_fake_var(container, ari_fake_expr_var, register_name);
    // loading left side of expression into the correct register
    load_var_into_register(container, ari_fake_expr_var, "rax");
    // performing division
    VarData *fake_var = get_fake_var(container->scope, right_fake_expr_var->fake_var_id);
    fprintf(container->out_file, "\tcqto\n\tidivq\t-%i(%%rbp)\n", fake_var->var_id);
    // storing modulo result in memory
    store_register_in_var(container, ari_fake_expr_var, "rdx");
    return left_type;
}

ExprTypeEnum arithmetic_aux_neg(ExprContainer *container, ExprData *ari_fake_expr_var, ExprData *right_fake_expr_var){
    // loading right side of expression into the correct register
    ExprTypeEnum type = load_var_into_register(container, right_fake_expr_var, "rax");
    // performing negation
    fprintf(container->out_file, "\tnegq\t%%rax\n");
    // storing negation result in memory
    store_register_in_var(container, ari_fake_expr_var, "rax");
    return type;
}


TypesEnum store_arithmetic_in_fake_var(ExprContainer *container, const ExprData *arithmetic_expression, const char *register_name){
    ExprTypeEnum ar_type = arithmetic_expression->type;
    assert(arithmetic_expression->has_fake_var);
    assert(ar_type == expr_arithmetic_add || ar_type == expr_arithmetic_sub || ar_type == expr_arithmetic_mul || ar_type == expr_arithmetic_div || ar_type == expr_arithmetic_mod || ar_type == expr_arithmetic_neg);

    fprintf(container->out_file, "\t# calculating '%s'\n", ExprType_name(ar_type));

    ExprData *ari_fake_expr_var = make_fake_expr(container->scope, arithmetic_expression);

    ExprData *right = ExprVector_endpop(container->exprs_stack);
    assert(right->has_fake_var);
    ExprData *right_fake_expr_var = make_fake_expr(container->scope, right);
    ExprTypeEnum fake_var_type = store_expression_in_fake_var(container, right, right_fake_expr_var, register_name);

    ExprTypeEnum left_side_type;
    switch(ar_type){
        case expr_arithmetic_add:
            left_side_type = arithmetic_aux_add(container, ari_fake_expr_var, right_fake_expr_var, register_name);
            break;
        case expr_arithmetic_sub:
            left_side_type = arithmetic_aux_sub(container, ari_fake_expr_var, right_fake_expr_var, register_name);
            break;
        case expr_arithmetic_mul:
            left_side_type = arithmetic_aux_mul(container, ari_fake_expr_var, right_fake_expr_var, register_name);
            break;
        case expr_arithmetic_div:
            left_side_type = arithmetic_aux_div(container, ari_fake_expr_var, right_fake_expr_var, register_name);
            break;
        case expr_arithmetic_mod:
            left_side_type = arithmetic_aux_mod(container, ari_fake_expr_var, right_fake_expr_var, register_name);
            break;
        case expr_arithmetic_neg:
            left_side_type = arithmetic_aux_neg(container, ari_fake_expr_var, right_fake_expr_var);
            break;
        default:
            left_side_type = expr_none;
            break;
    }
    assert(left_side_type == fake_var_type);
    
    ExprData_free(right_fake_expr_var);
    ExprData_free(right);
    ExprVector_endadd(container->exprs_stack, ari_fake_expr_var);

    fprintf(container->out_file, "\t# end of '%s'\n\n", ExprType_name(ar_type));

    return fake_var_type;
}
