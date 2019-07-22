#include <stdio.h>

void print_int(long num){
    printf("%li\n", num);
}

long addition(long num1, long num2){
    long result = num1 + num2;
    print_int(result);
    return result;
}

long substraction(long num1, long num2){
    long result = num1 - num2;
    print_int(result);
    return result;
}

long mul(long num1, long num2){
    long result = num1 * num2;
    print_int(result);
    return result;
}

long div(long num1, long num2){
    long result = num1 / num2;
    print_int(result);
    return result;
}

long mod(long num1, long num2){
    long result = num1 % num2;
    print_int(result);
    return result;
}

long neg(long num1){
    long result = -num1;
    print_int(result);
    return result;
}
