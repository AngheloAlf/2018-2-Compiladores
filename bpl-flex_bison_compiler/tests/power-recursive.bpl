int pow(int b, int n)
{
   int r;

   if (b == 0)
     return 0;
   else if (n == 0)
     return 1;
   else if (n % 2 == 1)
     return b * pow(b * b, n / 2);
   else
     return pow(b * b, n / 2);
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
