#include<stdio.h>
#include<stdlib.h>

// inline int sqr(char *x);

static inline int sqr(char *x){
    return x!=NULL ? x[0] + x[1] - x[2] : 0;
}

int main(int argc, char **argv){
    char i[100];

    int retVal = scanf("%s", i);

    int j = sqr(i);

    printf("%i\n", j);

    return 0;
}