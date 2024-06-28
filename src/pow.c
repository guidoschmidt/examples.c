#include <stdio.h>

int power(int base, int exp);

int main(int argc, char *argv[])
{
  int base = *argv[1] - '0';
  int exp = *argv[2] - '0';
  printf("%d to the power of %d = %d", base, exp, power(base, exp));
  return 0;
}

int power(int base, int exp) {
  int p = 1;
  for (int i = 0; i < exp; ++i) {
    p = p * base;
  }
  return p;
}
