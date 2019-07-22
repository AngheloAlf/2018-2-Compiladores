#include <stdio.h>

void print_int(long num){
    printf("%li\n", num);
}

void if_test(long num){
    long aux = num > 0;
    if(aux){
        print_int(num);
    }
    else{
        print_int(-num);
    }
}

void while_test(long num){
    while(num){
        print_int(num);
        if(num > 0){
            num -= 1;
        }
        else if(num < 0){
            num += 1;
        }
    }
}
