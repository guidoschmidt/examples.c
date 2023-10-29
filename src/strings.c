#include <stdio.h>

int main(int argc, char *argv[])
{
  char string[] = "a string is a sequenc of chars!";
  for (int i = 0; i < sizeof(string) / sizeof(char); i++) {
    printf("string[%*i] → %c\n", 2, i, string[i]);
  }

  printf("Please give me your name...\nEnter name: ");
  char name[100];
  scanf("%s", name);

  printf("3rd character in your name is %c", name[3]);

  return 0;
}
