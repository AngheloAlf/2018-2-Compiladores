#include <stdio.h>
#include <stdlib.h>

void check_array_index(long array_len, long index){
    if(index < 0){
        fprintf(stderr, "[ERROR] The given array index (%li) is negative.\nExiting with error code -1\n", index);
        exit(-1);
    }
    if(index >= array_len){
        fprintf(stderr, "[ERROR] The given array index (%li) is equal or greater than the array length (%li).\nExiting with error code -2\n", index, array_len);
        exit(-2);
    }
}
