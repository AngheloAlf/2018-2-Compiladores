#include <stdio.h>

void print_int(long num){
    printf("%li\n", num);
}

long leq(long num1, long num2){
    long result = num1 <= num2;
    print_int(result);
    return result;
}

long lss(long num1, long num2){
    long result = num1 < num2;
    print_int(result);
    return result;
}

long equ(long num1, long num2){
    long result = num1 == num2;
    print_int(result);
    return result;
}

long neq(long num1, long num2){
    long result = num1 != num2;
    print_int(result);
    return result;
}

long gtr(long num1, long num2){
    long result = num1 > num2;
    print_int(result);
    return result;
}

long geq(long num1, long num2){
    long result = num1 >= num2;
    print_int(result);
    return result;
}
