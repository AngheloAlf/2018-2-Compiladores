#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int c;
FILE *mainFile;

/**
 * Tries to open the first argument as a file. If no argument, uses the stdin.
*/
void getFile(int argc, char **argv){
    mainFile = stdin;
    if(argc > 1){
        mainFile = fopen(argv[1], "r");
        if(!mainFile){
            fprintf(stderr, "Couldn't find file.\n");
            exit(1);
        }
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
