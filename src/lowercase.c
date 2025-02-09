#include <stddef.h>
#include <stdio.h>
int lower(int c)
{
  if (c >= 'A' && c <= 'Z')
    return c + 'a' - 'A';
  else
    return c;
}

int main(int argc, char *argv[])
{
  char uppercase[] = {'B', 'X', 'Z', 'I', 'G'};
  for (size_t i = 0; i < sizeof(uppercase) / sizeof(char); ++i) {
    printf("\n%c → %c", uppercase[i], lower(uppercase[i]));
  }
  return 0;
}
