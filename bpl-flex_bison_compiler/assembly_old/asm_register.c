#include "asm_register.h"

#include "ast_handler.h"

#include "error_handler.h"
#include "util.h"

ExprTypeEnum get_ExprType_const(TypesEnum type){
    return (TypesEnum_is_int(type) ? expr_int : (TypesEnum_is_string(type) ? expr_str : expr_none));
}


ExprTypeEnum load_const_expr_into_register(ExprContainer *container, ExprData *expression, const char *register_name){
    assert(ExprType_is_const(expression->type));
    const char *expr_name = expression->expr;
    const char *asm_str;

    ExprTypeEnum const_type = expr_none;
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

ExprTypeEnum load_var_into_register(ExprContainer *container, ExprData *expression, const char *register_name){
    assert(expression->type == expr_var);
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

ExprTypeEnum load_var_pointer_into_register(ExprContainer *container, ExprData *expression, const char *register_name){
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

ExprTypeEnum load_var_address_into_register(ExprContainer *container, ExprData *expression, const char *register_name){
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

ExprTypeEnum load_array_into_register(ExprContainer *container, ExprData *expression, const char *register_name);

ExprTypeEnum load_array_address_into_register(ExprContainer *container, ExprData *expression, const char *register_name);

/** 
 * load the *expression* into *register_name* 
 * in *aux_register*, an intermediate value could be stored. dont use a register with an important value
 * **/
ExprTypeEnum load_expression_into_register(ExprContainer *container, ExprData *expression, const char *register_name){
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
