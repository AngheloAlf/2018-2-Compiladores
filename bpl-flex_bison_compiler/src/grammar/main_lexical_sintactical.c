
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

#include "var_vector.h"
#include "func_vector.h"
#include "string_vector.h"

#include "program_flow.h"

#include "assembly_gen.h"

int lineCounter = 1;
int in_line_character_counter = 1;

extern FILE *yyin;
extern char *yytext;
extern int yylex();
extern int yyparse();

extern void free_flex_stack();

FILE *in_file;
FILE *out_file;

void update_new_line(){
    ++lineCounter;
    in_line_character_counter = 1;
}


noreturn void invalid(const char *s){
    fprintf(stderr, "\n\t[ERROR] Invalid: '%s'\n\tExiting...\n", s);
    exit(-1);
}

void parse_arguments(int argc, char **argv){
    if(argc > 2){
        in_file = fopen(argv[1], "r");
        if(!in_file){
            fprintf(stderr, "File not found: %s\n", argv[1]);
            exit(-1);
        }
        out_file = fopen(argv[2], "w");
    }
    else{
        printf("Usage: %s input_file output_file\n", argv[0]);
        exit(-1);
    }
}

void close_files(){
    fclose(in_file);
    fclose(out_file);
}

void file_write(FILE *fp, int how_many, ...){
    va_list args;
    va_start(args, how_many);
    char *str;

    for(int i = 0; i < how_many; ++i){
        str = va_arg(args, char*);
        fwrite(str, 1, strlen(str), fp);
    }

    va_end(args);
}

int main(int argc, char **argv){
	parse_arguments(argc, argv);

    vars_init_and_prepare();

    write_file_header(out_file, argv[1]);

    yyin = in_file;
	int ret = yyparse();
    if(ret){
        printf("ERROR: %i\n", ret);
    }
    else{
        printf("No errors\n");
    }

    write_file_footer(out_file, argv[1]);

    free_flex_stack();
    vars_free();

    close_files();
    return ret;
}
