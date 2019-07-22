#ifndef FUNC_VECTOR_H
#define FUNC_VECTOR_H

#include "cadts_vector.h"

#include "types_enum.h"
#include "variable.h"

typedef struct{
    TypesEnum type;
    char *name;
    bool used;

    VarVector *paramList;

    bool has_return;
} FuncData;
CADTS_VECTOR(FuncVector, FuncData*)

FuncData *FuncData_init(TypesEnum type, const char *id);
void FuncData_free(FuncData *func);
void FuncData_print(FuncData *func);

void FuncVector_clean(FuncVector *vec);
void FuncVector_print(FuncVector *vec);
FuncData *FuncVector_search_func(FuncVector *vec, const char *func_name);

#endif /* FUNC_VECTOR_H */
