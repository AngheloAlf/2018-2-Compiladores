#ifndef SCOPE_VECTOR_H
#define SCOPE_VECTOR_H

#include "cadts_vector.h"

#include "variable.h"
#include "expression.h"

typedef struct scope_struct ScopeData;
CADTS_VECTOR(ScopeVector, ScopeData*)

struct scope_struct{
    ScopeVector *scopes;
    VarVector *declared_vars;
    ExprVector *exprs;

    ScopeData *up_scope;
    bool has_ended;
};

ScopeData *ScopeData_init();
void ScopeData_free(ScopeData *scope);
void ScopeData_clean(ScopeData *scope);
void ScopeData_print(ScopeData *scope);
void ScopeData_print_vars(ScopeData *scope);
ScopeData *ScopeData_get_last_not_ended_scope(ScopeData *actual_scope);
VarData *ScopeData_search_var_actual_or_upper_scope(ScopeData *actual_scope, const char *var_name);
VarData *ScopeData_search_var_last_scope(ScopeData *actual_scope, const char *var_name);

void ScopeVector_clean(ScopeVector *scopes);
void ScopeVector_print(ScopeVector *scopes);
void ScopeVector_print_vars(ScopeVector *scopes);
VarData *ScopeVector_search_var_in_last_scope(ScopeVector *vec, char *var_name);
int ScopeVector_get_variables_size(ScopeVector *vec);

#endif /* SCOPE_VECTOR_H */
