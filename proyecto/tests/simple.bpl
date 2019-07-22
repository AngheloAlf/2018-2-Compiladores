/* A simple program */

int
f(int a)
{
  return a + 1;
}

void
b(int x)
{
  write(x); writeln();
}

void
main(void)
{
  int x;
  x = 1;
  b(f(x));
}
