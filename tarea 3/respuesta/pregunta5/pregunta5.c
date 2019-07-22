#include<stdio.h>


int main(){
    int a[20];
    int x = 5;
    for(int y = 0; y < 10; y++){
        a[y] = x * x + y * y;
    }
    return a[9];
}