#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int c;
FILE *mainFile;

void testError(bool expression, const char *message){
    if(expression){
        fprintf(stderr, "%s\n", message);
        exit(2);
    }
}

/**
 * Tries to open the first argument as a file. If no argument, uses the stdin.
*/
void getFile(int argc, char **argv){
    mainFile = stdin;
    if(argc > 1){
        mainFile = fopen(argv[1], "r");
        testError(!mainFile, "Couldn't find file.\n");
    }
}

void closeFile(void){
    if(mainFile != stdin){
        fclose(mainFile);
    }
}

int getCharacter(){
    return getc(mainFile);
}

