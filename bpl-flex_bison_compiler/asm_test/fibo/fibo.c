long __count;


long fibo(long input_number){
    long first_parameter;
    long second_parameter;
    long value1;
    long value2;
    //long result;
    __count += 1;
    if(input_number <= 1){
        // long i = 1;
        return 1;
    }
    first_parameter = input_number - 1;
    second_parameter = input_number - 2;
    value1 = fibo(first_parameter);
    value2 = fibo(second_parameter);
    return value1 + value2;
    //result = value1 + value2;
    //return result;
}
/*
long fibo(long input_number){
    if(input_number <= 1){
        return 1;
    }
    return fibo(input_number-1) + fibo(input_number-2);
}*/