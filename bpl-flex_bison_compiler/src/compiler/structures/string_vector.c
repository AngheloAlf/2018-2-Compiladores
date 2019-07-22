#include "string_vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"

StringData *StringData_init(const char *string_input){
    StringData *sd = malloc(sizeof(StringData));

    sd->string = strdup(string_input);
    sd->written = false;

    return sd;
}

void StringData_free(StringData *sd){
    free(sd->string);
    free(sd);
}

void StringData_print(StringData *sd){
    printf("string: %s\n", sd->string);
    printf("written: %s\n", bool_name(sd->written));
}


void StringVector_clean(StringVector *vec){
    while(StringVector_len(vec)){
        StringData *data = StringVector_endpop(vec);
        // StringData_print(data);
        StringData_free(data);
    }
}

void StringVector_print(StringVector *vec){
    for(int i = 0; i < StringVector_len(vec); ++i){
        printf("%i ", i);
        StringData *data = StringVector_item(vec, i);
        StringData_print(data);
    }
}

StringData *StringVector_search(StringVector *vec, const char *str){
    for(int i = 0; i < StringVector_len(vec); ++i){
        StringData *data = StringVector_item(vec, i);
        if(!strcmp(data->string, str)){
            return data;
        }
    }
    return NULL;
}
