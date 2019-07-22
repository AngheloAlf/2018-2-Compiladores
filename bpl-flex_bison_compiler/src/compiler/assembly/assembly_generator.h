#ifndef ASSEMBLY_GEN_H
#define ASSEMBLY_GEN_H

#include <stdio.h>

#include "scope.h"
#include "variable.h"
#include "function.h"
#include "expression.h"


typedef struct{
    FILE *out_file;
    FuncData *function;
    ScopeData *scope;
    ExprVector *exprs_stack;
    long stack_size;
} ExprContainer;


void write_file_header(FILE *out_file, const char *file_name);

void parse_expressions(FILE *output_file, FuncData *function, ScopeData *scope);
void write_function(FILE *out_file, FuncData *function);

void write_file_footer(FILE *out_file, const char *file_name);

#endif /* ASSEMBLY_GEN_H */
