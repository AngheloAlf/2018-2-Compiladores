#ifndef ASSEMBLY_GEN_H
#define ASSEMBLY_GEN_H

#include <stdio.h>

#include "func_vector.h"

void write_file_header(FILE *out_file, const char *file_name);

void write_function(FuncData *function);

void write_file_footer(FILE *out_file, const char *file_name);

#endif /* ASSEMBLY_GEN_H */
