#include <stdio.h>
#include <string.h>

int custom_strlen(char s[])
{
  int i = 0;
  while (s[i] != '\0') i++;
  return i;
}

int main(int argc, char *argv[])
{
  char string[] = "a string is a sequenc of chars!";
  printf("\nLength of string is %i", strlen(string));
  printf("\nCustom length of string is %i", custom_strlen(string));
  return 0;
}
