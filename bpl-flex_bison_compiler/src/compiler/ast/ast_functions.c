#include "ast_handler.h"

#include <stdio.h>

#include "assembly_generator.h"

#include "error_handler.h"

extern int lineCounter;
extern int in_line_character_counter;

extern FILE *out_file;

/// funcs

void declare_new_function(const char *function_ret_type, char *function_name){
    is_local_var = true;
    FuncVector_endadd(func_vector, FuncData_init(TypesEnum_init(function_ret_type, false, false), function_name));  
}

void end_function_declaration(){
    is_local_var = false;
}

void end_function_definition(){
    is_local_var = false;

    FuncData *data = FuncVector_endtop(func_vector);
    data->paramList = param_list;
    param_list = VarVector_init(8);

    write_function(out_file, data);

    ScopeData_clean(local_scope);
}

void verify_func_declared(const char *func_name){
    FuncData *var;
    var = FuncVector_search_func(func_vector, func_name);
    if(var == NULL){
        error_not_declared_func(func_name);
    }
    var->used = true;
}

void add_func_call(const char *func_name, int arguments_amount){
    verify_func_declared(func_name);
    add_expr(func_name, expr_func_call);
    last_expression->arguments_amount = arguments_amount;
}

void add_var_as_func_par(const char *type, char *id, bool pointer, bool array){
    if(VarVector_search_var(param_list, id) != NULL){
        error_func("[ERROR]The parameter '%s' is already declared.\n", id);
    }

    VarData *data = VarData_init(TypesEnum_init(type, pointer, array), id, 0, true, lineCounter, in_line_character_counter);
    VarVector_endadd(param_list, data);
}

int get_parameters_size(){
    int bytes_size = 0;
    FuncData *data = FuncVector_endtop(func_vector);
    for(int i = 0; i < VarVector_len(data->paramList); ++i){
        bytes_size += 8;
    }
    return bytes_size;
}

void set_vars_ids_to_scopes(ScopeData *scope_data, int *ids){
    for(int i = 0; i < VarVector_len(scope_data->declared_vars); ++i){
        VarData *var_data = VarVector_item(scope_data->declared_vars, i);
        if(TypesEnum_is_array(var_data->type)) *ids -= 8;
        if(!var_data->used){
            printf("[Warning] %i.%i Declared but not used variable: %s\n", var_data->line, var_data->column, var_data->id);
        }
        var_data->var_id = *ids;
        int size_needed = (TypesEnum_is_array(var_data->type) ? var_data->array_size : 1);
        *ids -= 8 * (size_needed > 0 ? size_needed : 1);
    }

    for(int i = 0; i < ScopeVector_len(scope_data->scopes); ++i){
        ScopeData *sub_scope = ScopeVector_item(scope_data->scopes, i);
        set_vars_ids_to_scopes(sub_scope, ids);
    }
}

void set_vars_ids(){
    int global_ids = -8;
    for(int i = 0; i < VarVector_len(global_vars); ++i){
        VarData *var = VarVector_item(global_vars, i);
        var->var_id = global_ids;
        /*if(!var->used){
            printf("[Warning] %i.%i Declared but not used variable: %s\n", var->line, var->column, var->id);
        }*/
        global_ids -= 8 * (TypesEnum_is_array(var->type) ? var->array_size : 1);
    }

    int ids = get_parameters_size() + get_all_declared_variables_size();
    // funcs_params
    FuncData *func_data = FuncVector_endtop(func_vector);
    for(int i = 0; i < VarVector_len(func_data->paramList); ++i){
        VarData *var = VarVector_item(func_data->paramList, i);
        if(!var->used){
            printf("[Warning] %i.%i Declared but not used variable: %s\n", var->line, var->column, var->id);
        }
        var->var_id = ids;
        ids -= 8;
    }

    // scopes
    set_vars_ids_to_scopes(local_scope, &ids);
}

void verify_return_expr(ExprTypeEnum expr){
    FuncData *func = FuncVector_endtop(func_vector);
    func->has_return = true;
    if(func->type == void_type){
        if(expr != expr_return_void){
            error_func("The function '%s' is void type, but the return has an expression.", func->name);
        }
    }
    else{
        if(expr != expr_return_expr){
            error_func("The function '%s' has a return type (different from void), but the return does not has an expression.", func->name);
        }
    }
}

void add_return(ExprTypeEnum expr){
    assert(expr == expr_return_void || expr == expr_return_expr);
    verify_return_expr(expr);
    add_expr("return", expr); 
}