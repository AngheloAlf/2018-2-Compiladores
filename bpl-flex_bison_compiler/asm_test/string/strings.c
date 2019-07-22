extern void extern_function(const char *);

const char *global_array[10];

void asdfasdf(){
    const char *test_1 = "un string de prueba";
    const char *test_2 = "otro string";
    //const char *test_3 = "ola k ase?";
    extern_function(test_1);
    extern_function(test_2);
    //extern_function(test_3);
    extern_function(global_array[0]);
}

void other_test_function(){
    const char *test_6 = "lets try out";
    const char *test_8 = "how this works";
    const char *test_9 = "!!!";
    extern_function(test_6);
    extern_function(test_8);
    extern_function(test_9);
    extern_function("this is a parameter");
}