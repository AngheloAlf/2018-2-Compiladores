#include "scope.h"

#include <stdlib.h>
#include <stdio.h>

#include "util.h"


ScopeData *ScopeData_init(){
    ScopeData *scope = malloc(sizeof(ScopeData));

    scope->scopes = ScopeVector_init(8);
    scope->declared_vars = VarVector_init(8);
    scope->exprs = ExprVector_init(8);
    
    scope->up_scope = NULL;
    scope->has_ended = false;

    return scope;
}

void ScopeData_free(ScopeData *scope){
    ScopeVector_clean(scope->scopes);
    ScopeVector_free(scope->scopes);
    VarVector_clean(scope->declared_vars);
    VarVector_free(scope->declared_vars);
    ExprVector_clean(scope->exprs);
    ExprVector_free(scope->exprs);
    free(scope);
}

void ScopeData_clean(ScopeData *scope){
    ScopeVector_clean(scope->scopes);
    VarVector_clean(scope->declared_vars);
    ExprVector_clean(scope->exprs);
    scope->up_scope = NULL;
    scope->has_ended = false;
}

void ScopeData_print(ScopeData *scope){
    printf("scope:\n");
    printf("has_ended: %s\n", bool_name(scope->has_ended));
    printf("up_scope: %p\n", (void *)scope->up_scope);
    VarVector_print(scope->declared_vars);
    ExprVector_print(scope->exprs);
    ScopeVector_print(scope->scopes);
    printf("\n");
}

void ScopeData_print_vars(ScopeData *scope){
    printf("scope:\n");
    VarVector_print(scope->declared_vars);
    ScopeVector_print_vars(scope->scopes);
    printf("\n");
}

ScopeData *ScopeData_get_last_not_ended_scope(ScopeData *actual_scope){
    int scopes_len = ScopeVector_len(actual_scope->scopes);
    if(actual_scope->has_ended){
        return NULL;
    }
    if(scopes_len > 0){
        ScopeData *aux = ScopeVector_endtop(actual_scope->scopes);
        ScopeData *result = ScopeData_get_last_not_ended_scope(aux);
        if(result != NULL && !result->has_ended){
            return result;
        }
    }
    return actual_scope;
}

VarData *ScopeData_search_var_actual_or_upper_scope(ScopeData *actual_scope, const char *var_name){
    VarData *variable = NULL;
    do{
        variable = VarVector_search_var(actual_scope->declared_vars, var_name);
    } while(variable == NULL && (actual_scope = actual_scope->up_scope) != NULL);
    
    return variable;
}

VarData *ScopeData_search_var_last_scope(ScopeData *actual_scope, const char *var_name){
    ScopeData *last_scope = ScopeData_get_last_not_ended_scope(actual_scope);
    return ScopeData_search_var_actual_or_upper_scope(last_scope, var_name);
}


void ScopeVector_clean(ScopeVector *scopes){
    while(ScopeVector_len(scopes)){
        ScopeData *data = ScopeVector_endpop(scopes);
        //ScopeData_print(data);
        ScopeData_free(data);
    }
}

void ScopeVector_print(ScopeVector *scopes){
    static int recursive_print = -1;
    recursive_print += 1;
    for(int i = 0; i < ScopeVector_len(scopes); ++i){
        printf("scope_vector:\t%i\t%i\n", recursive_print, i);

        ScopeData *scope = ScopeVector_item(scopes, i);
        ScopeData_print(scope);
    }
    recursive_print -= 1;
}

void ScopeVector_print_vars(ScopeVector *scopes){
    static int recursive_print = -1;
    recursive_print += 1;
    for(int i = 0; i < ScopeVector_len(scopes); ++i){
        printf("scope_vector:\t%i\t%i\n", recursive_print, i);

        ScopeData *scope = ScopeVector_item(scopes, i);
        ScopeData_print_vars(scope);
    }
    recursive_print -= 1;
}

VarData *ScopeVector_search_var_in_last_scope(ScopeVector *vec, char *var_name);

int ScopeVector_get_variables_size(ScopeVector *vec){
    int bytes_size = 0;
    for(int i = 0; i < ScopeVector_len(vec); ++i){
        ScopeData *scope = ScopeVector_item(vec, i);
        bytes_size += VarVector_get_variables_size(scope->declared_vars);
        bytes_size += ScopeVector_get_variables_size(scope->scopes);
    }
    return bytes_size;
}
