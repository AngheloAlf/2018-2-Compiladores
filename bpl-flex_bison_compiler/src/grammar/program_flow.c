#include "program_flow.h"

#include <assert.h>
#include <string.h>

#include "assembly_gen.h"
#include "error_handler.h"

extern int lineCounter;
extern int in_line_character_counter;


// set-up

void prepare_vars(){
    FuncData *lib_func;

    lib_func = FuncData_init(int_type, "read");
    lib_func->paramList = VarVector_init(0);
    FuncVector_endadd(func_vector, lib_func);

    lib_func = FuncData_init(void_type, "writeln");
    lib_func->paramList = VarVector_init(0);
    FuncVector_endadd(func_vector, lib_func);
}

void vars_init_and_prepare(){
    global_vars = VarVector_init(8);
    local_scope = ScopeData_init();
    is_local_var = false;

    func_vector = FuncVector_init(8);
    param_list = VarVector_init(8);

    strings_constants = StringVector_init(8);

    last_expression = NULL;

    if_else_stack = ExprVector_init(8);
    while_stack = ExprVector_init(8);

    prepare_vars();
}

void vars_free(){
    assert(ExprVector_len(while_stack) == 0);
    ExprVector_free(while_stack);
    assert(ExprVector_len(if_else_stack) == 0);
    ExprVector_free(if_else_stack);

    StringVector_clean(strings_constants);
    StringVector_free(strings_constants);

    VarVector_clean(param_list);
    VarVector_free(param_list);
    FuncVector_clean(func_vector);
    FuncVector_free(func_vector);

    ScopeData_clean(local_scope);
    ScopeData_free(local_scope);
    VarVector_clean(global_vars);
    VarVector_free(global_vars);
}


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

void verify_var_declared(char *var_name, int flags, ExprType operator_type){
    VarData *var = search_variable(var_name, param_list, NULL);

    var->used = true;

    if(flags == IS_WHATEVER){
        return;
    }
    if(flags & NOT_POINTER_NOT_ARRAY){
        if(var->type == int_pointer || var->type == string_pointer || var->type == int_array || var->type == string_array){
            fprintf(stderr, "[ERROR] Can't apply '%s' to variable '%s'.\n", ExprType_name(operator_type), var_name);
            error_var("The variable '%s' is a pointer/array.", var_name);
        }
        return;
    }
    if(flags & IS_POINTER){
        if(var->type != int_pointer && var->type != string_pointer){
            fprintf(stderr, "[ERROR] Can't apply '%s' to variable '%s'.\n", ExprType_name(operator_type), var_name);
            error_var("The variable '%s' is not a pointer.", var_name);
        }
        return;
    }
    if(flags & IS_ARRAY){
        if(var->type != int_array && var->type != string_array){
            fprintf(stderr, "[ERROR] Can't apply '%s' to variable '%s'.\n", ExprType_name(operator_type), var_name);
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

    write_function(data);

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
        if(TypesEnum_is_array(var_data->type) && !var_data->is_fake_var) *ids -= 8;
        if(!var_data->used && !var_data->is_fake_var){
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
        /*if(!var->used && !var->is_fake_var){
            printf("[Warning] %i.%i Declared but not used variable: %s\n", var->line, var->column, var->id);
        }*/
        global_ids -= 8 * (TypesEnum_is_array(var->type) ? var->array_size : 1);
    }

    int ids = get_parameters_size() + get_all_declared_variables_size();
    // funcs_params
    FuncData *func_data = FuncVector_endtop(func_vector);
    for(int i = 0; i < VarVector_len(func_data->paramList); ++i){
        VarData *var = VarVector_item(func_data->paramList, i);
        if(!var->used && !var->is_fake_var){
            printf("[Warning] %i.%i Declared but not used variable: %s\n", var->line, var->column, var->id);
        }
        var->var_id = ids;
        ids -= 8;
    }

    // scopes
    set_vars_ids_to_scopes(local_scope, &ids);
}

void verify_return_expr(ExprType expr){
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

void add_return(ExprType expr){
    assert(expr == expr_return_void || expr == expr_return_expr);
    verify_return_expr(expr);
    add_expr("return", expr); 
}


/// strings

void add_string_constant(const char *string){
    StringData *sd = StringData_init(string);
    StringVector_endadd(strings_constants, sd);
    add_expr(string, expr_str);
}

void set_strings_ids(){
    for(int i = 0; i < StringVector_len(strings_constants); ++i){
        StringData *str = StringVector_item(strings_constants, i);
        str->str_id = i;
    }
}


/// exprs

void generate_fake_var_for_expr(ScopeData *actual_scope, ExprData *expr){
    static int fake_var_id = 0;
    if(!expr->has_fake_var){
        expr->has_fake_var = true;
        expr->fake_var_id = ++fake_var_id;

        TypesEnum fake_var_type = void_type;
        if(ExprType_is_var(expr->type)){
            VarData *real_var = search_variable(expr->expr, param_list, actual_scope);
            fake_var_type = real_var->type;
        }
        else if(expr->type == expr_func_call){
            FuncData *called_func = FuncVector_search_func(func_vector, expr->expr);
            assert(called_func != NULL);
            fake_var_type = called_func->type;
        }
        if(fake_var_type == void_type){
            if(expr->type == expr_str){
                fake_var_type = string_type;
            }
            else{
                fake_var_type = int_type;
            }
        }

        VarData *fake_var = VarData_fake_var(expr, fake_var_type);
        VarVector_endadd(actual_scope->declared_vars, fake_var);
    }
}

void set_if_id(ExprData *expr){
    assert(expr->type == expr_if || expr->type == expr_else || expr->type == expr_if_end);
    ExprData *old_if;
    static int if_id = 0;

    expr->is_flow_control = true;
    switch(expr->type){
        case expr_if:
            expr->flow_control_id = ++if_id;
            ExprVector_endadd(if_else_stack, expr);
            break;
        case expr_else:
            assert(ExprVector_len(if_else_stack) > 0);
            old_if = ExprVector_endtop(if_else_stack);
            assert(!old_if->has_else);
            old_if->has_else = true;
            expr->flow_control_id = old_if->flow_control_id;
            break;
        case expr_if_end:
            assert(ExprVector_len(if_else_stack) > 0);
            old_if = ExprVector_endpop(if_else_stack);
            expr->flow_control_id = old_if->flow_control_id;
            break;
        default:
            break;
    }
}

void set_while_id(ExprData *expr){
    assert(expr->type == expr_while || expr->type == expr_while_condition || expr->type == expr_while_end);
    ExprData *old_while;
    static int while_id = 0;

    expr->is_flow_control = true;
    switch(expr->type){
        case expr_while:
            expr->flow_control_id = ++while_id;
            ExprVector_endadd(while_stack, expr);
            break;
        case expr_while_condition:
            assert(ExprVector_len(while_stack) > 0);
            old_while = ExprVector_endtop(while_stack);
            expr->flow_control_id = old_while->flow_control_id;
            break;
        case expr_while_end:
            assert(ExprVector_len(while_stack) > 0);
            old_while = ExprVector_endpop(while_stack);
            expr->flow_control_id = old_while->flow_control_id;
            break;
        default:
            break;
    }
}

void add_expr(const char *expr, ExprType expr_type){
    ScopeData *actual_scope = ScopeData_get_last_not_ended_scope(local_scope);
    ExprData *actual_expression = ExprData_init(expr, expr_type, lineCounter, in_line_character_counter);

    switch(expr_type){
        case expr_if:
        case expr_else:
        case expr_if_end:
            set_if_id(actual_expression);
            break;

        case expr_while:
        case expr_while_condition:
        case expr_while_end:
            set_while_id(actual_expression);
            break;

        case expr_comparation_leq:
        case expr_comparation_lss:
        case expr_comparation_equ:
        case expr_comparation_neq:
        case expr_comparation_gtr:
        case expr_comparation_geq:

        case expr_arithmetic_add:
        case expr_arithmetic_sub:
        case expr_arithmetic_mul:
        case expr_arithmetic_div:
        case expr_arithmetic_mod:
        case expr_arithmetic_neg:
            generate_fake_var_for_expr(actual_scope, last_expression);

        case expr_func_call:
        case expr_array:
        case expr_array_ampersand:
        case expr_assignation_var:
            generate_fake_var_for_expr(actual_scope, actual_expression);
            break;

        default:
            // TODO: show error.
            break;
    }
    ExprVector_endadd(actual_scope->exprs, actual_expression);
    last_expression = actual_expression;
}

void set_last_expr_as_func_arg(){
    if(last_expression != NULL){
        assert(last_expression->is_func_argument == false);
        last_expression->is_func_argument = true;
        ScopeData *actual_scope = ScopeData_get_last_not_ended_scope(local_scope);
        generate_fake_var_for_expr(actual_scope, last_expression);
    }
}

VarData *get_fake_var(ScopeData *actual_scope, int fake_var_id){
    VarData *variable;
    do{
        for(int i = 0; i < VarVector_len(actual_scope->declared_vars); ++i){
            variable = VarVector_item(actual_scope->declared_vars, i);
            if(variable->is_fake_var && variable->fake_var_id == fake_var_id){
                variable->used = true;
                return variable;
            }
        }
    } while((actual_scope = actual_scope->up_scope) != NULL);
    
    return NULL;
}

ExprData *make_fake_expr(ScopeData *scope, const ExprData *orig_expr){
    assert(orig_expr->has_fake_var);
    if(!orig_expr->has_fake_var){
        ExprData_print(orig_expr);
    }
    assert(orig_expr->has_fake_var);
    VarData *fake_var = get_fake_var(scope, orig_expr->fake_var_id);
    assert(fake_var != NULL);
    return ExprData_fake_expr(fake_var, orig_expr);
}
