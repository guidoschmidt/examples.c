#include <stdio.h>
int main(int argc, char *argv[])
{
  int input;
  printf("Please enter a number... ");
  scanf("%d", &input);
  printf("Nice choice %d!", input);

  float a;
  float b;
  printf("\nNow please give two floats... ");
  scanf("%f%f", &a, &b);
  printf("Adding these gives %f", a + b);
  
  return 0;
}
