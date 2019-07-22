int pow(int b, int n)
{
   int r;

   if (b == 0)
     return 0;

   r = 1;
   while (n > 0) {
     if (n % 2 == 1)
       r = r * b;
     b = b * b;
     n = n / 2;
   }
   return r;
}

void main(void)
{
  int x;

  x = read();
  while(x) {
    int n;

    n = read();
    write(x); write(" to the power "); write(n); write(": "); write(pow(x, n));
    writeln();

    x = read();
  }
}
