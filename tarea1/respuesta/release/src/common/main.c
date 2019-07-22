#include <stdio.h>
#include <stdbool.h>

extern int c;

extern void getFile(int argc, char **argv);

extern void closeFile(void);

extern int getCharacter();


/** 
 * Returns true if character is a letter.
 */
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
 * Returns false if EOF is found.
*/
bool scan(){
    for(; !isValidChar(c) && c != EOF; c = getCharacter());
    return c != EOF;
}

/**
 * Reads until a space, newline, or any other non valid character (for a word) is found.
 * Returns true if the readed word is a valid word.
 */
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
