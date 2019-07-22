#ifndef TYPES_ENUM_H
#define TYPES_ENUM_H

#include <stdbool.h>

typedef enum{void_type, 
              int_type, string_type,
              int_pointer, string_pointer,
              int_array, string_array
            } TypesEnum;

TypesEnum TypesEnum_init(const char *type, bool pointer, bool array);
const char *TypesEnum_get_name(TypesEnum type);
bool TypesEnum_is_array(TypesEnum type);

bool TypesEnum_is_int(TypesEnum type);
bool TypesEnum_is_string(TypesEnum type);

#endif /* TYPES_ENUM_H */