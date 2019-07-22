#include <stdio.h>

extern int yylex();
extern int yylineno;
extern char* yytext;

int main(){
    int counter = 0;
    int tokenID = yylex();
    while(tokenID){
        counter++;
        // printf("%s", yytext);
        tokenID = yylex();
    }
    printf("%d\n", counter);
    return 0;
}
