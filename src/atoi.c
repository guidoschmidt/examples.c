#include <stdio.h>

int atoi(char s[])
{
  int i, n;
  n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) {
    n = 10 * n + (s[i] - '0');
  }
  return n;
}

int main(int argc, char *argv[])
{
  char text[] = "63655";
  int i; 
  /* for (i = 0; i < sizeof(text); ++i) { */
  printf("\nString: %s  → Integer: %i", text, atoi(text));
  /* } */
  return 0;
}
