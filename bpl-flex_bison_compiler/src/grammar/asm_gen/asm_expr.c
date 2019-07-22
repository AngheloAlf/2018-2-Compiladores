#include "asm_expr.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "types_enum.h"

#include "program_flow.h"

#include "error_handler.h"
#include "util.h"

ExprType get_ExprType_const(TypesEnum type){
    return (TypesEnum_is_int(type) ? expr_int : (TypesEnum_is_string(type) ? expr_str : expr_none));
}


ExprType load_const_expr_into_register(ExprContainer *container, ExprData *expression, const char *register_name){
    assert(ExprType_is_const(expression->type));
    const char *expr_name = expression->expr;
    const char *asm_str;

    ExprType const_type = expr_none;
    if(expression->type == expr_int){
        asm_str = "\tmovq\t$%s, %%%s # <load> %s -> %%%s\n";
        fprintf(container->out_file, asm_str, expr_name, register_name, expr_name, register_name);
        const_type = expr_int;
    }
    else if(expression->type == expr_str){
        asm_str = "\tmovq\t$.%s_str_%i, %%%s # <load> %s -> %%%s\n";
        StringData *str_data = StringVector_search(strings_constants, expr_name);
        int str_id = str_data->str_id;
        fprintf(container->out_file, asm_str, container->function->name, str_id, register_name, expr_name, register_name);
        const_type = expr_str;
    }
    return const_type;
}

ExprType load_var_into_register(ExprContainer *container, ExprData *expression, const char *register_name){
    assert(expression->type == expr_var);
    // assert(!expression->is_fake_expr); // TODO
    const char *expr_name = expression->expr;
    const char *asm_str;

    VarData *variable = search_variable(expression->expr, container->function->paramList, container->scope);
    if(variable->var_id > 0){
        if(TypesEnum_is_array(variable->type) && !variable->is_func_param){
            asm_str = "\tleaq\t-%i(%%rbp), %%%s # <load> %s -> %%%s\n";
        }
        else{
            asm_str = "\tmovq\t-%i(%%rbp), %%%s # <load> %s -> %%%s\n";
        }
        fprintf(container->out_file, asm_str, variable->var_id, register_name, expr_name, register_name);
    }
    else{ // global
        if(TypesEnum_is_array(variable->type)){
            asm_str = "\tmovq\t$%s, %%%s # <load> %s -> %%%s\n";
        }
        else{
            asm_str = "\tmovq\t%s(%%rip), %%%s # <load> %s -> %%%s\n";
        }
        fprintf(container->out_file, asm_str, expr_name, register_name, expr_name, register_name);
    }
    return get_ExprType_const(variable->type);
}

ExprType load_var_pointer_into_register(ExprContainer *container, ExprData *expression, const char *register_name){
    assert(expression->type == expr_var_asterisc);
    const char *expr_name = expression->expr;
    const char *asm_str;

    VarData *variable = search_variable(expression->expr, container->function->paramList, container->scope);
    if(variable->var_id > 0){
        if(!variable->is_func_param){
            asm_str = "\tleaq\t-%i(%%rbp), %%%s # <load> %s -> %%%s \n";
            fprintf(container->out_file, asm_str, variable->var_id, register_name, expr_name, register_name);
        }
        else{
            asm_str = "\tmovq\t-%i(%%rbp), %%%s # <load> %s -> %%%s \n";
            fprintf(container->out_file, asm_str, variable->var_id, register_name, expr_name, register_name);
        }
    }
    else{ // global
        asm_str = "\tmovq\t%s(%%rip), %%%s # <load> %s -> %%%s\n";
        fprintf(container->out_file, asm_str, expr_name, register_name, expr_name, register_name);
    }
    asm_str = "\tmovq\t(%%%s), %%%s # <mov> *%s -> %%%s\n";
    fprintf(container->out_file, asm_str, register_name, register_name, expr_name, register_name);

    return get_ExprType_const(variable->type);
}

ExprType load_var_address_into_register(ExprContainer *container, ExprData *expression, const char *register_name){
    assert(expression->type == expr_var_ampersand);
    const char *expr_name = expression->expr;
    const char *asm_str;

    VarData *variable = search_variable(expression->expr, container->function->paramList, container->scope);
    if(variable->var_id > 0){
        asm_str = "\tleaq\t-%i(%%rbp), %%%s # <load> &%s -> %%%s\n";
        fprintf(container->out_file, asm_str, variable->var_id, register_name, expr_name, register_name);
    }
    else{ // global
        asm_str = "\tmovq\t$%s, %%%s # <load> &%s -> %%%s\n";
        fprintf(container->out_file, asm_str, expr_name, register_name, expr_name, register_name);
    }
    return get_ExprType_const(variable->type);
}

ExprType load_array_into_register(ExprContainer *container, ExprData *expression, const char *register_name);

ExprType load_array_address_into_register(ExprContainer *container, ExprData *expression, const char *register_name);

/** 
 * load the *expression* into *register_name* 
 * in *aux_register*, an intermediate value could be stored. dont use a register with an important value
 * **/
ExprType load_expression_into_register(ExprContainer *container, ExprData *expression, const char *register_name){
    switch(expression->type){
        case expr_int:
        case expr_str:
            return load_const_expr_into_register(container, expression, register_name);
            break;
        case expr_var:
            return load_var_into_register(container, expression, register_name);
            break;
        case expr_var_asterisc:
            return load_var_pointer_into_register(container, expression, register_name);
            break;
        case expr_var_ampersand:
            return load_var_address_into_register(container, expression, register_name);
            break;
        case expr_array:
            return load_array_into_register(container, expression, register_name);
            break;
        case expr_array_ampersand:
            return load_array_address_into_register(container, expression, register_name);
            break;
        default:
            printf("unexpected expression\n");
            ExprData_print(expression);
            assert(!"unexpected expression");
            break;
    }
    return expr_none;
}



void store_register_in_var(ExprContainer *container, ExprData *expression, const char *register_name){
    if(!(expression->type == expr_var)) printf("%s\n", ExprType_name(expression->type));
    assert(expression->type == expr_var);
    /*if(expression->is_fake_expr){
        ExprData_print(expression);
        VarData *variable = search_variable(expression->expr, container->function->paramList, container->scope);
        VarData_print(variable);
    }
    assert(!expression->is_fake_expr);*/
    /*if(strcmp("7_=_fake_var", expression->expr) == 0){
        ExprData_print(expression);
        VarData *variable = search_variable(expression->expr, container->function->paramList, container->scope);
        VarData_print(variable);
        // assert(!expression->is_fake_expr);
        // assert(!"fuck");
    }*/
    const char *expr_name = expression->expr;
    const char *asm_str;

    VarData *variable = search_variable(expression->expr, container->function->paramList, container->scope);
    if(variable->var_id > 0){
        asm_str = "\tmovq\t%%%s, -%i(%%rbp) # %%%s -> %s\n";
        fprintf(container->out_file, asm_str, register_name, variable->var_id, register_name, expr_name);
    }
    else{ // global
        asm_str = "\tmovq\t%%%s, %s(%%rip) # %%%s -> %s\n";
        fprintf(container->out_file, asm_str, register_name, expr_name, register_name, expr_name);
    }
}

void store_register_in_var_pointer(ExprContainer *container, ExprData *expression, const char *register_name){
    assert(expression->type == expr_var_asterisc);
    const char *expr_name = expression->expr;
    const char *asm_str;
    const char *internal_register = "r15";

    VarData *variable = search_variable(expression->expr, container->function->paramList, container->scope);
    if(variable->var_id > 0){
        if(!variable->is_func_param){
            asm_str = "\tleaq\t-%i(%%rbp), %%%s # <load> %s -> %%%s \n";
            fprintf(container->out_file, asm_str, variable->var_id, internal_register, expr_name, internal_register);
        }
        else{
            asm_str = "\tmovq\t-%i(%%rbp), %%%s # <load> %s -> %%%s\n";
            fprintf(container->out_file, asm_str, variable->var_id, internal_register, expr_name, internal_register);
        }
     }
    else{ // global
        asm_str = "\tmovq\t%s(%%rip), %%%s # <load> %s -> %%%s\n";
        fprintf(container->out_file, asm_str, expr_name, internal_register, expr_name, internal_register);
    }
    asm_str = "\tmovq\t%%%s, (%%%s) # %%%s -> *%s\n";
    fprintf(container->out_file, asm_str, register_name, internal_register, register_name, expr_name);
}

void store_register_in_array(ExprContainer *container, ExprData *expression, const char *register_name);

/// stores the *register* into *expression
void store_register_in_expression(ExprContainer *container, ExprData *expression, const char *register_name){
    switch(expression->type){
        case expr_var:
            store_register_in_var(container, expression, register_name);
            break;
        case expr_var_asterisc:
            store_register_in_var_pointer(container, expression, register_name);
            break;
        case expr_array:
            store_register_in_array(container, expression, register_name);
            break;
         default:
            printf("unexpected expression\n");
            ExprData_print(expression);
            assert(!"unexpected expression");
            break;
    }
}


ExprType load_fake_var_into_register(ExprContainer *container, ExprData *src_fake, const char *register_name){
    assert(src_fake->is_fake_expr);
    const char *asm_str = "\tmovq\t-%i(%%rbp), %%%s\n";
    VarData *fake_var = get_fake_var(container->scope, src_fake->fake_var_id);
    fprintf(container->out_file, asm_str, fake_var->var_id, register_name);
    return get_ExprType_const(fake_var->type);
}

ExprType store_register_in_fake_var(ExprContainer *container, ExprData *dst_fake, const char *register_name){
    assert(dst_fake->is_fake_expr);
    const char *asm_str = "\tmovq\t %%%s, -%i(%%rbp)\n";
    VarData *fake_var = get_fake_var(container->scope, dst_fake->fake_var_id);
    fprintf(container->out_file, asm_str, register_name, fake_var->var_id);
    return get_ExprType_const(fake_var->type);
}

ExprType store_expression_in_fake_var(ExprContainer *container, ExprData *expression, ExprData *dest_fake, const char *register_name){
    assert(dest_fake->has_fake_var);
    ExprType var_type = load_expression_into_register(container, expression, register_name);
    store_register_in_var(container, dest_fake, register_name);
    return var_type;
}

ExprType store_stackpop_in_fake_var(ExprContainer *container, ExprData *dest_fake, const char *register_name){
    assert(dest_fake->has_fake_var);
    assert(ExprVector_len(container->exprs_stack) > 0);
    ExprData *stacktop = ExprVector_endpop(container->exprs_stack);
    ExprType stacktop_type = store_expression_in_fake_var(container, stacktop, dest_fake, register_name);
    ExprData_free(stacktop);
    return stacktop_type;
}
