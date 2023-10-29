#include <stdio.h>

int main(int argc, char *argv[])
{
  // @TODO change the data type, e.g. to char, short, int, long, float, double
  int array_size = 8;
  short array[array_size];

  for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
    printf("%d → %d\n", i, &array[i]);
  }

  printf("Notice the jump of %d between every address", sizeof(array[0]));

  return 0;
}
