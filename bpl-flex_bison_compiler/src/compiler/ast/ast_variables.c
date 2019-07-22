#include "ast_handler.h"

#include <stdio.h>

#include "error_handler.h"

extern int lineCounter;
extern int in_line_character_counter;

/// vars

void add_declared_var(VarData *var){
    VarVector *scope;
    if(is_local_var){
        ScopeData *actual_scope = ScopeData_get_last_not_ended_scope(local_scope);

        VarData *variable = VarVector_search_var(actual_scope->declared_vars, var->id);
        if(variable != NULL){
            error_var_already_declared_in_local_scope(var->id);
        }

        scope = actual_scope->declared_vars;
    }
    else{
        if(VarVector_search_var(global_vars, var->id) != NULL){
            error_var_already_declared_as_global(var->id);
        }
        scope = global_vars;
    }
    VarVector_endadd(scope, var);
}

void declare_variable(const char *type, char *id, bool pointer, bool array, int array_size){
    add_declared_var(VarData_init(TypesEnum_init(type, pointer, array), id, array_size, false, lineCounter, in_line_character_counter));
}

void verify_var_declared(char *var_name, int flags, ExprTypeEnum operator_type){
    VarData *var = search_variable(var_name, param_list, NULL);

    var->used = true;

    if(flags == IS_WHATEVER){
        return;
    }
    if(flags & NOT_POINTER_NOT_ARRAY){
        if(var->type == int_pointer || var->type == string_pointer || var->type == int_array || var->type == string_array){
            fprintf(stderr, "[ERROR] Can't apply '%s' to variable '%s'.\n", ExprTypeEnum_name(operator_type), var_name);
            error_var("The variable '%s' is a pointer/array.", var_name);
        }
        return;
    }
    if(flags & IS_POINTER){
        if(var->type != int_pointer && var->type != string_pointer){
            fprintf(stderr, "[ERROR] Can't apply '%s' to variable '%s'.\n", ExprTypeEnum_name(operator_type), var_name);
            error_var("The variable '%s' is not a pointer.", var_name);
        }
        return;
    }
    if(flags & IS_ARRAY){
        if(var->type != int_array && var->type != string_array){
            fprintf(stderr, "[ERROR] Can't apply '%s' to variable '%s'.\n", ExprTypeEnum_name(operator_type), var_name);
            error_var("The variable '%s' is not an array.", var_name);
        }
        return;
    }
}

void assign_value_var(char *var_name){
    VarData *var = search_variable(var_name, param_list, NULL);
    var->get_assigned = true;
}


int get_all_declared_variables_size(){
    int bytes_size = 0;
    bytes_size += VarVector_get_variables_size(local_scope->declared_vars);
    bytes_size += ScopeVector_get_variables_size(local_scope->scopes);
    return bytes_size;
}

void new_scope(){
    ScopeData *scope = ScopeData_get_last_not_ended_scope(local_scope);
    ScopeData *next_scope = ScopeData_init(8);
    next_scope->up_scope = scope;
    ScopeVector_endadd(scope->scopes, next_scope);

    ExprVector_endadd(scope->exprs, ExprData_init("", expr_scope, lineCounter, in_line_character_counter)); 
    /*if(scope->up_scope != NULL){
        ExprVector_endadd(scope->up_scope->exprs, ExprData_init("", expr_scope)); 
    }*/
}

void end_scope(){
    ScopeData *scope = ScopeData_get_last_not_ended_scope(local_scope);
    if(scope != NULL){
        scope->has_ended = true;

        /*if(scope->up_scope != NULL){
            ExprVector_endadd(scope->up_scope->exprs, ExprData_init("", expr_scope_end)); 
        }*/
        ExprVector_endadd(scope->exprs, ExprData_init("", expr_scope_end, lineCounter, in_line_character_counter)); 
    }
}

VarData *search_variable(const char *var_name, VarVector *func_params, ScopeData *scope){
    VarData *var;
    if(scope != NULL){
        var = ScopeData_search_var_actual_or_upper_scope(scope, var_name);
    }
    else{
        var = ScopeData_search_var_last_scope(local_scope, var_name);
    }

    if(var == NULL){
        var = VarVector_search_var(func_params, var_name);
    }
    if(var == NULL){
        var = VarVector_search_var(global_vars, var_name);
    }
    if(var == NULL){
        error_var_not_declared(var_name);
    }

    return var;
}
