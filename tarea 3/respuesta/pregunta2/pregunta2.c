#include<stdio.h>
#include<stdlib.h>
#include "pregunta2.h"

int square(char *x){
    return x!=NULL ? x[0] + x[1] - x[2] : 0;
}


// int square_pure(int x) __attribute__((pure));

int __attribute__((pure)) square_pure(char *x){
    return x!=NULL ? x[0] + x[1] - x[2] : 0;
}


int main(int argc, char **argv){
    int i, j;
    char coso[100];

    scanf("%s", coso);

    /*
    i = square(5);
    int j = square(5);

    printf("%i", i+j);*/

    i = square_pure(coso);
    j = square_pure(coso);

    printf("%i", i+j);

    // int x = MAX(i++,j++);

    return 0;
}