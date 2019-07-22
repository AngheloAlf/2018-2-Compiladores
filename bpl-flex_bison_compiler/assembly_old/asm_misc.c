#include <stdio.h>

void write_file_header(FILE *output_file, const char *file_name){
    fprintf(output_file, "\t.file\t\"%s\"\n", file_name);
}

void write_file_footer(FILE *output_file, const char *file_name){
    fprintf(output_file, "\t#'%s' EOF\n", file_name);
}
