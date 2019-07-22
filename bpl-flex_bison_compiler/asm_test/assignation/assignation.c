long global_long;
long *global_pointer;
char *global_string;
long global_arr[10];

void long_add(long *asdf){
    long aux;
    aux = global_long;
    *asdf += aux;
    *asdf += 42;
}

void long_pointer(long *asdf){
    long aux;
    aux = *global_pointer;
    *asdf += aux;
    *asdf += 42;
}

void long_ampesand(long *asdf){
    long aux;
    long *aux_global;
    aux_global = &global_long;
    aux = *global_pointer;
    *asdf += aux;
    *asdf += *aux_global;
    *asdf += 42;
}

void long_arr(long *asdf){
    long aux;
    aux = global_arr[3];
    *asdf = *asdf + aux;
}

void long_arr_ampersand(long *asdf){
    long *aux;
    aux = &global_arr[7];
    *asdf = *asdf + aux[1];
}

void long_arr_par(long asdf[5]){
    long number = 24;
    asdf[2] = number;
}

long main(void){
    long var;
    long aux;
    global_long = 99;
    global_string = "99";
    var = 42;
    aux = var;
    long_add(&var);
    long_add(&aux);
    return var;
}