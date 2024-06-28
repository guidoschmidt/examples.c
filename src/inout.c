#include <stdio.h>
int main(int argc, char *argv[])
{
  char c = getchar();
  printf("\nFirst char was %c", c);
  putchar('\n');
  putchar(c);

  int input;
  printf("\nPlease enter a number... ");
  scanf("%d", &input);
  printf("Nice choice %d!", input);

  float a;
  float b;
  printf("\nNow please give two floats... ");
  scanf("%f%f", &a, &b);
  printf("Adding %f and %f we get %f", a, b, a + b);
  
  return 0;
}
