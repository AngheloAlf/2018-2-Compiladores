#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <stdbool.h>

bool isStdin = false;

extern FILE *yyin;
extern char *yytext;
extern int yylex();
extern int yyparse();

noreturn void invalid(char *s){
    fprintf(stderr, "\n\t[ERROR] Invalid: '%s'\n\tExiting...\n", s);
    abort();
    exit(-1);
}

FILE *getInputFile(int argc, char **argv){
	FILE *myfile = stdin;
    isStdin = true;
    if(argc > 1){
        myfile = fopen(argv[1], "r");
        isStdin = true;
        if(!myfile){
            fprintf(stderr, "File not found: %s\n", argv[1]);
            exit(-1);
        }
        printf("File: %s\n", argv[1]);
    }
    else{
        printf("File: stdin\n");
    }
    return myfile;
}

void closeInputFile(FILE *file){
    if(!isStdin){
        fclose(file);
    }
}

int main(int argc, char **argv){

	yyin = getInputFile(argc, argv);

	yyparse();
    /*int tokenID = yylex();
    for(; tokenID; tokenID = yylex()){
        
        switch(tokenID){
            case -1:
                printf("KEYWORD: \t");
                break;

            case 1:
                printf("VARIABLE: \t");
                break;
            case 2:
                printf("NUMBER: \t");
                break;

            case 11:
                printf("INT_TYPE: \t");
                break;
            case 12:
                printf("STRING_TYPE: \t");
                break;
            case 13:
                printf("POINTER_TYPE: \t");
                break;
            case 14:
                printf("ARREGLOINDICE: \t");
                break;
            case 15:
                printf("VOID_TYPE: \t");
                break;

            case 21:
                printf("FLOW_CONTROL: \t");
                break;
            case 22:
                printf("LIB_FUNC: \t");
                break;
            case 23:
                printf("RETURN: \t");
                break;

            case 31:
                printf("STRING: \t");
                break;
            case 32:
                printf("ARITMETICA: \t");
                break;
            case 33:
                printf("COMPARADORES: \t");
                break;

            case 41:
                printf("CURLY: \t\t");
                break;
            case 42:
                printf("PAREN: \t\t");
                break;
            case 43:
                printf("SEMICOLON: \t");
                break;
            case 44:
                printf("COMMA: \t\t");
                break;
            case 45:
                printf("ASIGNATION: \t");
                break;

            default:
                printf("tokenID: %i\t", tokenID);
        }
        printf("%s\n", yytext);
    }*/

    closeInputFile(yyin);
    return 0;
}
