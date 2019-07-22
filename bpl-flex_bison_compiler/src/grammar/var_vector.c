#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdnoreturn.h>

#include "util.h"

#include "var_vector.h"

#include "error_handler.h"

VarData *VarData_init(TypesEnum type, char *id, int array_size, bool is_func_param, int line, int column){
    VarData *vd = malloc(sizeof(VarData));
    vd->type = type;
    vd->id = strdup(id);
    vd->array_size = array_size;
    vd->used = false;
    vd->get_assigned = vd->is_func_param = is_func_param;
    vd->var_id = 0;
    vd->written = false;
    vd->is_fake_var = false;
    vd->fake_var_id = 0;
    vd->line = line;
    vd->column = column;
    return vd;
}

void VarData_free(VarData *var){
    free(var->id);
    free(var);
}

void VarData_print(VarData *var){
    printf("var:\n");
    printf("\ttype: %s\n", TypesEnum_get_name(var->type));
    
    printf("\tid: %s\n", var->id);

    if(var->type == string_array || var->type == int_array){
        printf("\tarray size: %i\n", var->array_size);
    }

    printf("\tused: %s\n", bool_name(var->used));
    printf("\tget_assigned: %s\n", bool_name(var->get_assigned));
    printf("\tis_func_param: %s\n", bool_name(var->is_func_param));
    printf("\tvar_id: %i\n", var->var_id);

    if(var->is_fake_var){
        printf("\tfake_var_id: %i\n", var->fake_var_id);
    }

    printf("\tline: %i\n", var->line);
    printf("\tcolumn: %i\n", var->column);
}

VarData *VarData_fake_var(ExprData *expr_data, TypesEnum type){
    assert(expr_data && expr_data->has_fake_var);

    int name_size = strlen(expr_data->expr) + 21 + 9 + 1 + 3; // og name + fake_id + "_fake_var" + '\0' + random extra space
    char *fake_name = malloc(sizeof(char) * name_size);
    const char *name_specifier = "%i_%s_fake_var";
    snprintf(fake_name, name_size, name_specifier, expr_data->fake_var_id, expr_data->expr);

    VarData *vd = malloc(sizeof(VarData));
    vd->type = type;
    vd->id = fake_name;
    vd->array_size = 0;
    vd->used = false;
    vd->is_func_param = false;
    vd->get_assigned = true;
    vd->var_id = 0;
    vd->written = false;
    vd->is_fake_var = expr_data->has_fake_var;
    vd->fake_var_id = expr_data->fake_var_id;
    vd->line = expr_data->line;
    vd->column = expr_data->column;
    return vd;
}

void VarVector_clean(VarVector *vec){
    while(VarVector_len(vec)){
        VarData *data = VarVector_endpop(vec);
        VarData_free(data);
    }
}

void VarVector_print(VarVector *vec){
    for(int i = 0; i < VarVector_len(vec); ++i){
        VarData_print(VarVector_item(vec, i));
    }
}


VarData *VarVector_search_var(VarVector *vec, const char *var_name){
    for(int i = 0; i < VarVector_len(vec); ++i){
        VarData *var = VarVector_item(vec, i);
        if(!strcmp(var->id, var_name)){
            return var;
        }
    }
    return NULL;
}

int VarVector_get_variables_size(VarVector *vec){
    int bytes_size = 0;
    int aux_size = 0;
    for(int i = 0; i < VarVector_len(vec); ++i){
        VarData *variable = VarVector_item(vec, i);
        switch(variable->type){
            case int_type:
            case string_type:
            case int_pointer:
            case string_pointer:
                bytes_size += 8;
                break;

            case int_array:
            case string_array:
                aux_size = (variable->is_func_param || variable->array_size<=0 ? 1 : variable->array_size+1);
                aux_size = (aux_size > 0 ? aux_size : 1);
                bytes_size += 8 * aux_size;
                break;

            default:
                error_var("Unsuported type for variable '%s'\n", TypesEnum_get_name(variable->type));
                break;
        }
    }
    return bytes_size;
}
