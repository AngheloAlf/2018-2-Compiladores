#ifndef ASSEMBLY_GEN_H
#define ASSEMBLY_GEN_H

#include <stdio.h>

#include "function.h"


typedef struct{
    FILE *out_file;
    FuncData *function;
    ScopeData *scope;
    ExprVector *exprs_stack;
} ExprContainer;


void write_file_header(FILE *out_file, const char *file_name);

void write_function(FILE *out_file, FuncData *function);

void write_file_footer(FILE *out_file, const char *file_name);

#endif /* ASSEMBLY_GEN_H */
