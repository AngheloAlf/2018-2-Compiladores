#include<stdio.h>


int main(){
    int a = 1;
    printf("Linea que no afecta a la variable a");
    printf("Linea que no afecta a la variable a");
    /*printf("Linea que no afecta a la variable a");
    printf("Linea que no afecta a la variable a");
    printf("Linea que no afecta a la variable a");
    printf("Linea que no afecta a la variable a");
    printf("Linea que no afecta a la variable a");
    printf("Linea que no afecta a la variable a");
    printf("Linea que no afecta a la variable a");*/
    int j = 15;

    if(a != 1){
        printf("no deberia impirmir.");
    }

    printf("el valor de a era %i", a);

    return 0;
}