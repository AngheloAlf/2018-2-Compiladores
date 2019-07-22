
int scope(int par1, int *par2, int par3, int par4, int par5, int par6, int par7, int par8, int par9, int par10){
    int scope1_variable1;
    int scope1_variable2;
    int scope1_variable3;
    int scope1_variable4;

    {
        int scope2_variable1;
        {
            int scope3_variable1;
            int scope3_variable2;
        }
        {
            int scope4_variable1;
            int scope4_variable2;
            {
                int scope5_variable1;
                int scope5_variable2;
                int scope5_variable3;
            }
            {
                int scope6_variable1;
                int scope6_variable2;
                int scope6_variable3;
            }
        }
    }

    {
        int scope7_variable1;
        int scope7_variable2;
        {
            int scope8_variable1;
            int scope8_variable2;
        }
        {
            int scope9_variable1;
            int scope9_variable2;
            {
                int scope10_variable1;
                int scope10_variable2;
            }
        }
        {
            int scope11_variable1;
            int scope11_variable2;
            {
                int scope12_variable1;
                int scope12_variable2;
                int scope12_variable3;
            }
            {
                int scope13_variable1;
                int scope13_variable2;
                int scope13_variable3;
            }
        }
    }
    
    return par1 + *par2;
}

int read_mult_param(int num){
    return num * read();
}

void set_arr(int arr[]){
    int i;
    i = 0;
    while(i < 16){
        arr[i] = i*i * ((i - 15) % 7);
        i = i + 1;
    }
}

void main(void){
  int x;
  int arr[16];
  int *pointer;
  x = 1;
  *pointer = 951;
  write(scope(x, &x, x, x, x, x, read_mult_param(read_mult_param(read())), x, *pointer, x));
}
