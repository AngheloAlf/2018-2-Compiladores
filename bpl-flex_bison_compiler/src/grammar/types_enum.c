#include <string.h>

#include "types_enum.h"

TypesEnum TypesEnum_init(const char *type, bool pointer, bool array){
    if(!strcmp(type, "int")){
        if(pointer){
            return int_pointer;
        }
        if(array){
            return int_array;
        }
        return int_type;
    }
    if(!strcmp(type, "string")){
        if(pointer){
            return string_pointer;
        }
        if(array){
            return string_array;
        }
        return string_type;
    }
    return void_type;
}

const char *TypesEnum_get_name(TypesEnum type){
    switch(type){
        case void_type:
            return "void";
        case int_type:
            return "int";
        case string_type:
            return "string";
        case int_pointer:
            return "int*";
        case string_pointer:
            return "string*";
        case int_array:
            return "int[]";
        case string_array:
            return "string[]";
    }
    return NULL;
}

bool TypesEnum_is_array(TypesEnum type){
    return type == int_array || type == string_array;
}

bool TypesEnum_is_int(TypesEnum type){
    return type == int_type || type == int_pointer || type == int_array;
}
bool TypesEnum_is_string(TypesEnum type){
    return type == string_type || type == string_pointer || type == string_array;
}
