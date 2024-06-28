#include <stdio.h>

int main(int argc, char *argv[])
{
  int c;
  int num_whitespace = 0;
  int num_other = 0;

  int num_digits[10];
  for (int i = 0; i < 10; ++i) {
    num_digits[i] = 0;
  }

  while(1) {
    c = getchar();
    if (c == EOF)
      break;
    if (c >= '0' && c <= '9')
      ++num_digits[c - '0'];
    else if (c == ' ' || c == '\n' || c == '\t')
      ++num_whitespace;
    else
      ++num_other;
  }

  printf("\ndigits = ");
  for (int i = 0; i < 10; ++i) {
    printf("\n  %d × %d", i, num_digits[i]);
  }
  printf("\nwhite space = %d", num_whitespace);
  printf("\nother = %d", num_other);

  return 0;
}
