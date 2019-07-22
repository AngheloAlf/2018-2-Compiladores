#include <stdio.h>

int main(){
    int x, i;

    x = 0;
    for(i = 0; i < 200; i++){
        x += 4 * i + 15;
    }
    printf("%i\n", x);
    return 0;
}