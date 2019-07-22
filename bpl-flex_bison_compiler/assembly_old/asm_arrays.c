#include "asm_register.h"



#include "error_handler.h"
#include "util.h"


/// NOTE: The register %r15 may be used internally for arrays operations. Don't use that register to store data.


void prepare_index_and_check(ExprContainer *container, VarData *array, ExprData *fake_expr){
    const char *internal_register = "r15";

    // store index in fake var
    ExprTypeEnum fake_exprtype = store_stackpop_in_fake_var(container, fake_expr, internal_register);
    assert(fake_exprtype == expr_int);

    load_fake_var_into_register(container, fake_expr, "rsi");
    if(array->var_id>0){
        if(!array->is_func_param){
            fprintf(container->out_file, "\tmovq\t$-1, %%rdi\n");
            fprintf(container->out_file, "\tmovq\t-%i(%%rbp,%%rdi,8), %%rdi\n", array->var_id);
        }
        else{
            fprintf(container->out_file, "\tmovq\t-%i(%%rbp), %%rdi\t\n", array->var_id);
            fprintf(container->out_file, "\tsubq\t$8, %%rdi\n");
            fprintf(container->out_file, "\tsubq\t(%%rdi), %%rdi\n");
        }
    }
    else{
        fprintf(container->out_file, "\tmovq\t$%i, %%rdi\n", array->array_size);
    }
    fprintf(container->out_file, "\tcall\t.check_array_index\n");
}

ExprTypeEnum load_array_into_register(ExprContainer *container, const ExprData *expression, const char *register_name){
    assert(expression->type == expr_array);
    const char *expr_name = expression->expr;
    const char *asm_str;

    VarData *variable = search_variable(expression->expr, container->function->paramList, container->scope);

    assert(ExprVector_len(container->exprs_stack) > 0);
    char *index_name = strdup(ExprVector_endtop(container->exprs_stack)->expr);

    // store index in fake var
    assert(expression->has_fake_var);
    ExprData *fake_expr = make_fake_expr(container->scope, expression);
    prepare_index_and_check(container, variable, fake_expr);
    VarData *fake_var = get_fake_var(container->scope, fake_expr->fake_var_id);

    if(variable->var_id > 0){ // local
        if(!variable->is_func_param){
            // load index from memory to register
            load_fake_var_into_register(container, fake_expr, register_name);
            // load array[index] into the register
            asm_str = "\tmovq\t-%i(%%rbp,%%%s,8), %%%s # %s[%s] -> %%%s\n";
            fprintf(container->out_file, asm_str, variable->var_id, register_name, register_name, expr_name, index_name, register_name);
        }
        else{
            // prepare index
            // Multiply index by 8
            asm_str = "\tsalq\t$3, -%i(%%rbp) # (%s << 3) \n";
            fprintf(container->out_file, asm_str, fake_var->var_id, index_name);
            
            // get the value from the array
            // load array address
            asm_str = "\tmovq\t-%i(%%rbp), %%%s # <load> %s[]\n";
            fprintf(container->out_file, asm_str, variable->var_id, register_name, expr_name);
            // add index to array
            asm_str = "\taddq\t-%i(%%rbp), %%%s # <load> %s[%s]\n";
            fprintf(container->out_file, asm_str, fake_var->var_id, register_name, expr_name, index_name);
            // get value from (array + index)
            asm_str = "\tmovq\t(%%%s), %%%s # %s[%s] -> %%%s\n";
            fprintf(container->out_file, asm_str, register_name, register_name, expr_name, index_name, register_name);
        }
    }
    else{ // global
        // load index from memory to register
        load_fake_var_into_register(container, fake_expr, register_name);
        // load array[index] into the register
        asm_str = "\tmovq\t%s(,%%%s,8), %%%s # %s[%s]-> %%%s\n";
        fprintf(container->out_file, asm_str, expr_name, register_name, register_name, expr_name, index_name, register_name);
    }
    free(index_name);
    ExprData_free(fake_expr);

    return get_ExprType_const(variable->type);
}

ExprTypeEnum load_array_address_into_register(ExprContainer *container, const ExprData *expression, const char *register_name){
    assert(expression->type == expr_array_ampersand);
    const char *expr_name = expression->expr;
    const char *asm_str;

    VarData *variable = search_variable(expression->expr, container->function->paramList, container->scope);

    assert(ExprVector_len(container->exprs_stack) > 0);
    char *index_name = strdup(ExprVector_endtop(container->exprs_stack)->expr);

    // store index in fake var
    assert(expression->has_fake_var);
    ExprData *fake_expr = make_fake_expr(container->scope, expression);
    prepare_index_and_check(container, variable, fake_expr);
    VarData *fake_var = get_fake_var(container->scope, fake_expr->fake_var_id);

    if(variable->var_id > 0){ // local
        if(!variable->is_func_param){
            // prepare index
            // Multiply index by 8
            asm_str = "\tsalq\t$3, -%i(%%rbp) # (%s << 3) \n";
            fprintf(container->out_file, asm_str, fake_var->var_id, index_name);

            // get the address from the array
            // load array address
            asm_str = "\tleaq\t-%i(%%rbp), %%%s # <load> &%s[]\n";
            fprintf(container->out_file, asm_str, variable->var_id, register_name, expr_name);
            // add index to array address
            asm_str = "\taddq\t-%i(%%rbp), %%%s # &%s[%s] -> %%%s\n";
            fprintf(container->out_file, asm_str, fake_var->var_id, register_name, expr_name, index_name, register_name);
        }
        else{
            // prepare index
            // Multiply index by 8
            asm_str = "\tsalq\t$3, -%i(%%rbp) # (%s << 3) \n";
            fprintf(container->out_file, asm_str, fake_var->var_id, index_name);


            // get the value from the array
            // load array address
            asm_str = "\tmovq\t-%i(%%rbp), %%%s # <load> &%s[]\n";
            fprintf(container->out_file, asm_str, variable->var_id, register_name, expr_name);
            // add index to array
            asm_str = "\taddq\t-%i(%%rbp), %%%s # &%s[%s] -> %%%s\n";
            fprintf(container->out_file, asm_str, fake_var->var_id, register_name, expr_name, index_name, register_name);
        }
    }
    else{ // global
        // prepare index
        // Multiply index by 8
        asm_str = "\tsalq\t$3, -%i(%%rbp) # (%s << 3) \n";
        fprintf(container->out_file, asm_str, fake_var->var_id, index_name);


        // get the value from the array
        // load array address
        asm_str = "\tmovq\t$%s, %%%s # <load> &%s[]\n";
        fprintf(container->out_file, asm_str, expr_name, register_name, expr_name);
        // add index to array
        asm_str = "\taddq\t-%i(%%rbp), %%%s # &%s[%s] -> %%%s\n";
        fprintf(container->out_file, asm_str, fake_var->var_id, register_name, expr_name, index_name, register_name);
    }
    free(index_name);
    ExprData_free(fake_expr);

    return get_ExprType_const(variable->type);
}

void store_register_in_array(ExprContainer *container, const ExprData *expression, const char *register_name){
    assert(expression->type == expr_array);
    assert(strcmp(register_name, "r15") != 0);

    const char *expr_name = expression->expr;
    const char *internal_register = "r15";
    const char *asm_str;

    VarData *variable = search_variable(expression->expr, container->function->paramList, container->scope);

    assert(ExprVector_len(container->exprs_stack) > 0);
    char *index_name = strdup(ExprVector_endtop(container->exprs_stack)->expr);

    // store index in fake var
    assert(expression->has_fake_var);
    ExprData *fake_expr = make_fake_expr(container->scope, expression);
    prepare_index_and_check(container, variable, fake_expr);
    VarData *fake_var = get_fake_var(container->scope, fake_expr->fake_var_id);

    if(variable->var_id > 0){ // local
        if(!variable->is_func_param){
            // // load index from memory to register
            load_fake_var_into_register(container, fake_expr, internal_register);
            // load array[index] into the register
            asm_str = "\tmovq\t%%%s, -%i(%%rbp,%%%s,8) # %%%s -> %s[%s]\n";
            fprintf(container->out_file, asm_str, register_name, variable->var_id, internal_register, register_name, expr_name, index_name);
        }
        else{
            // prepare index
            // Multiply index by 8
            asm_str = "\tsalq\t$3, -%i(%%rbp) # (%s << 3) \n";
            fprintf(container->out_file, asm_str, fake_var->var_id, index_name);

            // get the value from the array
            // load array address
            asm_str = "\tmovq\t-%i(%%rbp), %%%s # <load> %s[]\n";
            fprintf(container->out_file, asm_str, variable->var_id, internal_register, expr_name);
            // add index to array
            asm_str = "\taddq\t-%i(%%rbp), %%%s # <load> %s[%s]\n";
            fprintf(container->out_file, asm_str, fake_var->var_id, internal_register, expr_name, index_name);
            // get value from (array + index)
            asm_str = "\tmovq\t%%%s, (%%%s) # %%%s -> %s[%s]\n";
            fprintf(container->out_file, asm_str, register_name, internal_register, register_name, expr_name, index_name);
        }
    }
    else{ // global
        // load index from memory to register
        load_fake_var_into_register(container, fake_expr, internal_register);
        // load array[index] into the register
        asm_str = "\tmovq\t%%%s, %s(,%%%s,8) # %%%s -> %s[%s]\n";
        fprintf(container->out_file, asm_str, register_name, expr_name, internal_register, register_name, expr_name, index_name);
    }
    free(index_name);
    ExprData_free(fake_expr);
}
