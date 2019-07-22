void print_int_array(int size, int x[]){
    int i;
    i = 0;
    while(i < size){
        write(x[i]);
        i = i + 1;
    }
    writeln();
}

void print_str_array(int size, string x[]){
    int i;
    i = 0;
    while(i < size){
        write(x[i]);
        i = i + 1;
    }
    writeln();
}

void main(void){
    int x[8];
    string number[10];

    x[0] = 1;
    x[1] = 2;
    x[2] = 3;
    x[3] = 5;
    x[4] = 8;
    x[5] = 13;
    x[6] = 21;
    x[7] = 34;

    print_int_array(8, x);

	number[0] = "zero";
	number[1] = "one";
	number[2] = "two";
	number[3] = "three";
	number[4] = "four";
	number[5] = "five";
	number[6] = "six";
	number[7] = "seven";
	number[8] = "eight";
	number[9] = "nine";

    print_str_array(10, number);
}