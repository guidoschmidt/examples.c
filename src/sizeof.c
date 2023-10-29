#include <stdio.h>
int main(int argc, char *argv[])
{
  long number = 4096;
  printf("Size of number %d in bytes is %lu", number, sizeof(number));
  return 0;
}
