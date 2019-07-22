typedef const char* string;

extern void extern_arr_int(long a[]);
// extern void extern_arr_str(string a[]);

long params(long par1[], long par2[], long par3[], long par4[], long par5[], long par6[], long par7[], long par8[]){
    
    extern_arr_int(par7);
    extern_arr_int(par8);

    /*long q = par1[3];
    long w = par2[2];
    long e = par3[1];
    long r = par4[0];
    long t = par5[1];
    long y = par6[2];
    long u = par7[3];

    
    return q+w+e+r+t+y+u;*/
    return 0;
}

extern void multiple_parameter(long par1, long par2, long par3, long par4, long par5, long par6, long par7, long par8, long par9);

extern void few_parameters(long par1, long par2, long par3, long par4);
extern long read();

extern long func1(long some);

long main(){
    // func1(read());
    // few_parameters(func1(read()), func1(read()), func1(read()), func1(read()));
    // few_parameters(read(), read(), read(), read());
    // multiple_parameter(read(), read(), read(), read(), read(), read(), read(), read());
    long number1 = 1;
    long number2 = 2;
    long number3 = 3;
    long number4 = 4;
    multiple_parameter(number1, number2, number3, number4, number1, number2, number3, number4, number1);

    /*long example[4] = {1,2, 3, 4};
    long other = params(example, example, example, example, example, example, example, example);*/
    return 0;
}
