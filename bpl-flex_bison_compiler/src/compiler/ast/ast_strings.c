#include "ast_handler.h"

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