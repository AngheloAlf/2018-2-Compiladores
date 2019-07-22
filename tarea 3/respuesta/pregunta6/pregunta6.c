#include<stdbool.h>
#include <stdio.h>


int main(int argc, char **argv){
    double y;
    int x = 32;
    bool flag = argc> 1;



    y = ((3 * x + 20) * x - 135) * x + 42;
    /* Rango de instrucciones que no usan y ni cambian x */
    if(flag)
        printf("y = %lf", y);
    /* Rango de instrucciones que no usan y */

    return 0;
}
