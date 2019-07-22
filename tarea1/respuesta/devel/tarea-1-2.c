#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h> 
#include <fcntl.h>
#include <unistd.h>

int c;
int mainFile;
char *fullFile;
long sz;

/**
 * Tries to open the first argument as a file. If no argument, uses the stdin.
*/
void getFile(int argc, char **argv){
    mainFile = 0; // stdin;
    if(argc > 1){
        mainFile = open(argv[1], O_RDONLY);
        if(mainFile < 0){
            fprintf(stderr, "Couldn't find file.\n");
            exit(1);
        }
    }
    else{
        fprintf(stderr, "You must provide a file.\n");
        exit(1);
    }

    sz = lseek(mainFile, 0L, SEEK_END);
    if(sz < 0){
        fprintf(stderr, "Couldn't tell file size.\n");
        exit(1);
    }
    lseek(mainFile, 0L, SEEK_SET);
    
    fullFile = (char *)malloc(sizeof(char) * sz);
    if(read(mainFile, fullFile, sz) < 0){
        fprintf(stderr, "Couldn't read file.\n");
        exit(1);
    }
    
    if(argc > 1){
        if(close(mainFile) < 0){
            fprintf(stderr, "Couldn't close file.\n");
            exit(1);
        }
    }
}

void closeFile(void){
    free(fullFile);
}

int getCharacter(){
    static int position = 0;
    return position < sz ? fullFile[position++] : EOF;
}

bool isLetter(int character){
    bool valid = false;
    valid = valid || (character >= 'A' && character <= 'Z'); // UpperCase letter
    valid = valid || (character >= 'a' && character <= 'z'); // lowercase letter
    return valid;
}

/**
 * return true if the char is valid as part of a word.
*/
bool isValidChar(int character){ // Multi-line for readability.
    bool valid = false; 
    valid = valid || (character >= '0' && character <= '9'); // number
    valid = valid || isLetter(character); // Letter
    valid = valid || character == '-'; // -
    return valid;
}

/**
 * Scans a letter from file. Skips anything that is not a letter, - or number.
 * Returns 0 if EOF is found.
*/
bool scan(){
    while(!isValidChar(c) && c != EOF){
        c = getCharacter();
    }
    return c != EOF;
}

bool readWord(){
    bool hasLetter = false;
    for(; isValidChar(c); c = getCharacter()){
        if(isLetter(c)){
            hasLetter = true;
        }
    }
    return hasLetter;
}

int main(int argc, char **argv){
    getFile(argc, argv);
    c = getCharacter();

    int counter = 0;
    while(scan()){
        counter += readWord()?1:0;
    }
    printf("%i\n", counter);

    closeFile();
    return 0;
}