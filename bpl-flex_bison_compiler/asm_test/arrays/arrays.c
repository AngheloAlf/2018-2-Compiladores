#include <stdio.h>


long global_arr[10];


void print_num(long num){
    printf("%li\n", num);
}


long local_arr_int_const_index(){
    long example[5] = {9, 45, 34, 64, 82};
    long ret_val = example[3];
    print_num(ret_val);
    return ret_val;
}

long local_arr_int_var_index(){
    long example[5] = {9, 45, 34, 64, 82};
    long index = 2;
    long ret_val = example[index];
    print_num(ret_val);
    return ret_val;
}

long local_arr_int_var_index_param(long index){
    long example[5] = {9, 45, 34, 64, 82};
    long ret_val = example[index];
    print_num(ret_val);
    return ret_val;
}


long param_arr_int_const_index(long example[]){
    long ret_val = example[3];
    print_num(ret_val);
    return ret_val;
}

long param_arr_int_var_index(long example[]){
    long index = 2;
    long ret_val = example[index];
    print_num(ret_val);
    return ret_val;
}

long param_arr_int_var_index_param(long example[], long index){
    long ret_val = example[index];
    print_num(ret_val);
    return ret_val;
}


long global_arr_int_const_index(){
    long ret_val = global_arr[3];
    print_num(ret_val);
    return ret_val;
}

long global_arr_int_var_index(){
    long index = 2;
    long ret_val = global_arr[index];
    print_num(ret_val);
    return ret_val;
}

long global_arr_int_var_index_param(long index){
    long ret_val = global_arr[index];
    print_num(ret_val);
    return ret_val;
}



void print_num_arr(long num[]){
    printf("%li\n", num[0]);
}


long addr_local_arr_int_const_index(){
    long example[5] = {9, 45, 34, 64, 82};
    long *ret_val = &example[3];
    print_num_arr(ret_val);
    return ret_val[0];
}

long addr_local_arr_int_var_index(){
    long example[5] = {9, 45, 34, 64, 82};
    long index = 2;
    long *ret_val = &example[index];
    print_num_arr(ret_val);
    return ret_val[0];
}

long addr_local_arr_int_var_index_param(long index){
    long example[5] = {9, 45, 34, 64, 82};
    long *ret_val = &example[index];
    print_num_arr(ret_val);
    return ret_val[0];
}


long addr_param_arr_int_const_index(long example[]){
    long *ret_val = &example[3];
    print_num_arr(ret_val);
    return ret_val[0];
}

long addr_param_arr_int_var_index(long example[]){
    long index = 2;
    long *ret_val = &example[index];
    print_num_arr(ret_val);
    return ret_val[0];
}

long addr_param_arr_int_var_index_param(long example[], long index){
    long *ret_val = &example[index];
    print_num_arr(ret_val);
    return ret_val[0];
}


long addr_global_arr_int_const_index(){
    long *ret_val = &global_arr[3];
    print_num_arr(ret_val);
    return ret_val[0];
}

long addr_global_arr_int_var_index(){
    long index = 2;
    long *ret_val = &global_arr[index];
    print_num_arr(ret_val);
    return ret_val[0];
}

long addr_global_arr_int_var_index_param(long index){
    long *ret_val = &global_arr[index];
    print_num_arr(ret_val);
    return ret_val[0];
}



void print_arr(long arr[], long len){
    for(long i = 0; i < len; ++i){
        printf("arr[%li] -> %li\n", i, arr[i]);
    }
}


void set_local_arr_int_const_index(long value){
    long example[5] = {9, 45, 34, 64, 82};
    example[3] = value;
    print_arr(example, 5);
}

void set_local_arr_int_var_index(long value){
    long example[5] = {9, 45, 34, 64, 82};
    long index = 2;
    example[index] = value;
    print_arr(example, 5);
}

void set_local_arr_int_var_index_param(long index, long value){
    long example[5] = {9, 45, 34, 64, 82};
    example[index] = value;
    print_arr(example, 5);
}


void set_param_arr_int_const_index(long example[], long value){
    example[3] = value;
    print_arr(example, 5);
}

void set_param_arr_int_var_index(long example[], long value){
    long index = 2;
    example[index] = value;
    print_arr(example, 5);
}

void set_param_arr_int_var_index_param(long example[], long index, long value){
    example[index] = value;
    print_arr(example, 5);
}


void set_global_arr_int_const_index(long value){
    global_arr[3] = value;
    print_arr(global_arr, 5);
}

void set_global_arr_int_var_index(long value){
    long index = 2;
    global_arr[index] = value;
    print_arr(global_arr, 5);
}

void set_global_arr_int_var_index_param(long index, long value){
    global_arr[index] = value;
    print_arr(global_arr, 5);
}


void asdf(long example[5]){
    param_arr_int_var_index(example);
}


long main(){
    long example[5] = {9, 45, 34, 64, 82};
    for(int i = 0; i < 5; ++i){
        global_arr[i+5] = global_arr[i] = example[i];
    }
    param_arr_int_var_index(example);
    addr_param_arr_int_var_index(example);
    addr_global_arr_int_var_index();
    set_param_arr_int_var_index(example, -59);
    return 0;
}
