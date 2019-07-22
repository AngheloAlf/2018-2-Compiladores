extern void extern_point_int(long *);
extern void extern_point_str(char **);


void pointer_left(long *fdsa){
    long *asdf;
    *fdsa = 5;
    *asdf = 10;
    *fdsa = *fdsa + *asdf;
}

void point(){
    long *a, *b, *c, z;
    z = 85;
    c = &z;
    *a = 42;
    *b = 21;
    *c = *a + *b;
    extern_point_int(c);
    char **d, **f, *g;
    *d = "asdfasdfasdf";
    *f = *d;
    /*g = *d;
    *f = g;*/
    // extern_point_str(d);
}