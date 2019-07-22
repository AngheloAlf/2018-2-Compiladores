#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdbool.h>

int c;
int mainFile;
char *fullFile;
long sz;

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
    testError(argc <= 1, "You must provide a file.\n");

    mainFile = open(argv[1], O_RDONLY);
    testError(mainFile < 0, "Couldn't find file.\n");

    sz = lseek(mainFile, 0L, SEEK_END);
    testError(sz < 0, "Couldn't tell file size.\n");
    lseek(mainFile, 0L, SEEK_SET);
    
    fullFile = mmap(NULL, sz, PROT_READ, MAP_SHARED, mainFile, 0);
    testError(fullFile == MAP_FAILED, "mmap failed.\n");
    
    testError(argc > 1 && close(mainFile) < 0, "Couldn't close file.\n");
}

void closeFile(void){
    munmap(fullFile, sz);
}

int getCharacter(){
    static int position = 0;
    return position < sz ? fullFile[position++] : EOF;
}