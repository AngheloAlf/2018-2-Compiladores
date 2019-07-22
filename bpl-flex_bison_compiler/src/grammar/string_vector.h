#ifndef STRING_VECTOR_H
#define STRING_VECTOR_H

#include <stdbool.h>

#include "cadts_vector.h"

typedef struct{
    char *string;

    bool written;
    int str_id;
} StringData;
CADTS_VECTOR(StringVector, StringData*)

StringData *StringData_init(const char *string_input);
void StringData_free(StringData *sd);
void StringData_print(StringData *sd);

void StringVector_clean(StringVector *vec);
void StringVector_print(StringVector *vec);
StringData *StringVector_search(StringVector *vec, const char *str);

#endif /* STRING_VECTOR_H */
