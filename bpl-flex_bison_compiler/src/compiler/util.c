#include "util.h"

int get_aligned_stack_size(int size){
    if(size % 16 != 0){
        size += 8;
    }
    return size;
}

const char *bool_name(bool boolean){
    return boolean ? "true" : "false";
}
