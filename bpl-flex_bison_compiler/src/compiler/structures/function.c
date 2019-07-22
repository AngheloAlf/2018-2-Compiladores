#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdnoreturn.h>

#include "util.h"

#include "function.h"

FuncData *FuncData_init(TypesEnum type, const char *id){
    FuncData *func = malloc(sizeof(FuncData));
    func->type = type;
    func->name = strdup(id);
    func->used = false;
    func->paramList = NULL;
    func->has_return = false;
    return func;
}

void FuncData_free(FuncData *func){
    free(func->name);
    if(func->paramList != NULL){
        VarVector_clean(func->paramList);
        VarVector_free(func->paramList);
    }
    free(func);
}

void FuncData_print(FuncData *func){
    printf("func:\n");
    printf("\ttype: %s\n", TypesEnum_get_name(func->type));
    printf("\tname: %s\n", func->name);
    printf("\tused: %s\n", bool_name(func->used));
    printf("\thas_return: %s\n", bool_name(func->has_return));
    if(func->paramList != NULL){
        VarVector_print(func->paramList);
    }
}


void FuncVector_clean(FuncVector *vec){
    while(FuncVector_len(vec)){
        FuncData *func = FuncVector_endpop(vec);
        FuncData_free(func);
    }
}

void FuncVector_print(FuncVector *vec){
    for(int i = 0; i < FuncVector_len(vec); ++i){
        FuncData *var = FuncVector_item(vec, i);
        FuncData_print(var);
    }
}

FuncData *FuncVector_search_func(FuncVector *vec, const char *func_name){
    for(int i = 0; i < FuncVector_len(vec); ++i){
        FuncData *func = FuncVector_item(vec, i);
        if(!strcmp(func->name, func_name)){
            return func;
        }
    }
    return NULL;
}
