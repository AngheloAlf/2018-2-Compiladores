#ifndef VAR_VECTOR_H
#define VAR_VECTOR_H

#include "cadts_vector.h"

#include "types_enum.h"
#include "string_vector.h"

#define IS_WHATEVER                 (0)
#define NOT_POINTER_NOT_ARRAY       (1<<0)
#define IS_POINTER                  (1<<1)
#define IS_ARRAY                    (1<<2)

typedef struct{
    TypesEnum type;
    char *id;
    int array_size;

    bool used;

    bool get_assigned;
    bool is_func_param;

    int var_id;
    bool written;

    bool is_fake_var;
    int fake_var_id;

    int line;
    int column;
} VarData;
CADTS_VECTOR(VarVector, VarData*)

#include "expr_vector.h"

VarData *VarData_init(TypesEnum type, char *id, int array_size, bool is_func_param, int line, int column);
void VarData_free(VarData *var);
void VarData_print(VarData *var);
VarData *VarData_fake_var(ExprData *expr_data, TypesEnum type);

void VarVector_clean(VarVector *vec);
void VarVector_print(VarVector *vec);
VarData *VarVector_search_var(VarVector *vec, const char *var_name);
int VarVector_get_variables_size(VarVector *vec);

#endif /* VAR_VECTOR_H */
