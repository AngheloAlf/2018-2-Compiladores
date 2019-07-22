#include <stdio.h>

long global_array[10];

long example(long a[], long i){
    long num_aux = i;
    // a[num_aux] = 42;
    long result;
    result = a[num_aux];
    return result;
}

long example3(long i){
    long array[3] = {2,1,0};
    long aux3 = 3;
    long aux = i % aux3;
    example(array, aux);
    return array[i];
}

long example4(long i){
    example(global_array, i);
    long result;
    result = global_array[i];
    return result;
}

long example5(long a[], long i){
    long result;
    long *b;
    b = &a[i];
    result = example(b, i);
    return result;
}

long example6(long i){
    long a[7] = {9, 7, 53, 42, 4,357, 2014};
    long result;
    long *b;
    b = &a[i];
    result = example(b, i);
    return result;
}

long example7(long i){
    long result;
    long *b;
    b = &global_array[i];
    result = example(b, i);
    return result;
}

long example8(long a[], long i){
    a[i] = i;
    long temp = example(a, i);
    return temp;
}

long example9(long i){
    long a[7] = {9, 7, 53, 42, 4,357, 2014};
    a[i] = i;
    long temp = example(a, i);
    return temp;
}

long example10(long i){
    global_array[i] = i;
    long temp = example(global_array, i);
    return temp;
}

void init_global(){
    for(int i = 0; i < 10; ++i){
        printf("%i: %i\n", 9-i, i*i+5);
        global_array[9-i] = i*i+5;
    }
}

long main(){
    init_global();
    long array[7] = {2,1,56, 987,357, 2014,65856};
    long index = 1;
    long other = array[index];
    // long result = example5(array, 2);
    long result;
    result = example9(3);
    printf("%li\n", result);
    result = example10(4);
    printf("%li\n", result);
    result = example8(array, 2);
    printf("%li\n", result);
    return example(array, index);
}

void example2(long a[]){
    a[15] = 42;
}


/*long global_arr[16];

void fdsa(long a[], long i){
    a[i] = 0;
    // a[global_arr[i%16]] = 0;
}

void asdf(long a[]){
    long temp;
    temp = a[2];
    a[2] = a[1];
    a[1] = temp;
    fdsa(a, a[3]);
}

int main(){
    long arr[10];
    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;
    arr[3] = 3;
    arr[4] = 4;
    arr[5] = 5;
    arr[6] = 6;
    arr[7] = 7;
    arr[8] = 8;
    arr[9] = 9;

    long *other;
    other = &arr[4];
    asdf(other);
    long zxcv;
    zxcv = arr[5];
    return zxcv;
}
*/