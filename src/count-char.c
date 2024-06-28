#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("Need an argument! Use like 'count-char x'");
    exit(0);
  }

  char search_for = (char)*argv[1];
  int count = 0;
  int c;
  printf("\nLooking for %c\n", search_for);
  while (1) {
    c = getchar();
    if (c == EOF)
      break;
    if (c == search_for)
      ++count;
    putchar(c);
  }
  printf("\nFound %i ⋇ %c", count, search_for);
  return 0;
}
