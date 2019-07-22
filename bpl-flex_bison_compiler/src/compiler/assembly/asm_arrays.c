#include "asm_register.h"

#include <string.h>

#include "ast_handler.h"

#include "error_handler.h"
#include "util.h"


/// NOTE: The register %r15 may be used internally for arrays operations. Don't use that register to store data.


void prepare_index_and_check(ExprContainer *container, VarData *array){
    // store index in stack
    assert(ExprVector_len(container->exprs_stack) > 0);
    ExprData *index = ExprVector_endpop(container->exprs_stack);
    load_expression_into_register(container, index, "rsi");
    store_register_in_stack(container, "rsi");
    ExprData_free(index);

    // Prepare the call for the bound-check's function.
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
    const char *internal_register = "r15";
    const char *expr_name = expression->expr;
    const char *asm_str;

    VarData *array_variable = search_variable(expression->expr, container->function->paramList, container->scope);

    assert(ExprVector_len(container->exprs_stack) > 0);
    char *index_name = strdup(ExprVector_endtop(container->exprs_stack)->expr);

    // store index in stack and bound-check
    prepare_index_and_check(container, array_variable);

    if(array_variable->var_id > 0){ // local
        if(!array_variable->is_func_param){
            // load index from memory to register
            load_stack_into_register(container, register_name);
            // load array[index] into the register
            asm_str = "\tmovq\t-%i(%%rbp,%%%s,8), %%%s # %s[%s] -> %%%s\n";
            fprintf(container->out_file, asm_str, array_variable->var_id, register_name, register_name, expr_name, index_name, register_name);
        }
        else{
            // prepare index
            // Multiply index by 8
            load_stack_into_register(container, internal_register);
            asm_str = "\tsalq\t$3, %%%s # (%s << 3) \n";
            fprintf(container->out_file, asm_str, internal_register, index_name);
            
            // get the value from the array
            // load array address
            asm_str = "\tmovq\t-%i(%%rbp), %%%s # <load> %s[]\n";
            fprintf(container->out_file, asm_str, array_variable->var_id, register_name, expr_name);
            // add index to array
            asm_str = "\taddq\t%%%s, %%%s # <load> %s[%s]\n";
            fprintf(container->out_file, asm_str, internal_register, register_name, expr_name, index_name);
            // get value from (array + index)
            asm_str = "\tmovq\t(%%%s), %%%s # %s[%s] -> %%%s\n";
            fprintf(container->out_file, asm_str, register_name, register_name, expr_name, index_name, register_name);
        }
    }
    else{ // global
        // load index from memory to register
        load_stack_into_register(container, register_name);
        // load array[index] into the register
        asm_str = "\tmovq\t%s(,%%%s,8), %%%s # %s[%s]-> %%%s\n";
        fprintf(container->out_file, asm_str, expr_name, register_name, register_name, expr_name, index_name, register_name);
    }
    free(index_name);

    return get_ExprType_const(array_variable->type);
}

ExprTypeEnum load_array_address_into_register(ExprContainer *container, const ExprData *expression, const char *register_name){
    assert(expression->type == expr_array_ampersand);
    const char *expr_name = expression->expr;
    const char *internal_register = "r15";
    const char *asm_str;

    VarData *array_variable = search_variable(expression->expr, container->function->paramList, container->scope);

    assert(ExprVector_len(container->exprs_stack) > 0);
    char *index_name = strdup(ExprVector_endtop(container->exprs_stack)->expr);

    // store index in stack
    prepare_index_and_check(container, array_variable);

    // prepare index
    // Multiply index by 8
    load_stack_into_register(container, internal_register);
    asm_str = "\tsalq\t$3, %%%s # (%s << 3) \n";
    fprintf(container->out_file, asm_str, internal_register, index_name);

    if(array_variable->var_id > 0){ // local
        if(!array_variable->is_func_param){
            // get the address from the array
            // load array address
            asm_str = "\tleaq\t-%i(%%rbp), %%%s # <load> &%s[]\n";
            fprintf(container->out_file, asm_str, array_variable->var_id, register_name, expr_name);
            // add index to array address
            asm_str = "\taddq\t%%%s, %%%s # &%s[%s] -> %%%s\n";
            fprintf(container->out_file, asm_str, internal_register, register_name, expr_name, index_name, register_name);
        }
        else{
            // get the value from the array
            // load array address
            asm_str = "\tmovq\t-%i(%%rbp), %%%s # <load> &%s[]\n";
            fprintf(container->out_file, asm_str, array_variable->var_id, register_name, expr_name);
            // add index to array
            asm_str = "\taddq\t%%%s, %%%s # &%s[%s] -> %%%s\n";
            fprintf(container->out_file, asm_str, internal_register, register_name, expr_name, index_name, register_name);
        }
    }
    else{ // global
        // get the value from the array
        // load array address
        asm_str = "\tmovq\t$%s, %%%s # <load> &%s[]\n";
        fprintf(container->out_file, asm_str, expr_name, register_name, expr_name);
        // add index to array
        asm_str = "\taddq\t%%%s, %%%s # &%s[%s] -> %%%s\n";
        fprintf(container->out_file, asm_str, internal_register, register_name, expr_name, index_name, register_name);
    }
    free(index_name);

    return get_ExprType_const(array_variable->type);
}

void store_register_in_array(ExprContainer *container, const ExprData *expression, const char *register_name){
    assert(expression->type == expr_array);
    assert(strcmp(register_name, "r15") != 0);

    const char *expr_name = expression->expr;
    const char *internal_register = "r15";
    const char *asm_str;

    VarData *array_variable = search_variable(expression->expr, container->function->paramList, container->scope);

    assert(ExprVector_len(container->exprs_stack) > 0);
    char *index_name = strdup(ExprVector_endtop(container->exprs_stack)->expr);

    // store index in fake var
    prepare_index_and_check(container, array_variable);

    if(array_variable->var_id > 0){ // local
        if(!array_variable->is_func_param){
            // load index from memory to register
            load_stack_into_register(container, internal_register);
            // load array[index] into the register
            asm_str = "\tmovq\t%%%s, -%i(%%rbp,%%%s,8) # %%%s -> %s[%s]\n";
            fprintf(container->out_file, asm_str, register_name, array_variable->var_id, internal_register, register_name, expr_name, index_name);
        }
        else{
            // prepare index
            // Multiply index by 8
            load_stack_into_register(container, internal_register);
            asm_str = "\tsalq\t$3, %%%s # (%s << 3) \n";
            fprintf(container->out_file, asm_str, internal_register, index_name);

            // get the value into the array
            // load array address
            asm_str = "\taddq\t-%i(%%rbp), %%%s # <load> %s[]\n";
            fprintf(container->out_file, asm_str, array_variable->var_id, internal_register, expr_name);
            // get value into (array + index)
            asm_str = "\tmovq\t%%%s, (%%%s) # %%%s -> %s[%s]\n";
            fprintf(container->out_file, asm_str, register_name, internal_register, register_name, expr_name, index_name);
        }
    }
    else{ // global
        // load index from memory to register
        load_stack_into_register(container, internal_register);
        // load array[index] into the register
        asm_str = "\tmovq\t%%%s, %s(,%%%s,8) # %%%s -> %s[%s]\n";
        fprintf(container->out_file, asm_str, register_name, expr_name, internal_register, register_name, expr_name, index_name);
    }
    free(index_name);
}
