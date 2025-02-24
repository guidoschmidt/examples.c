/* removes all c from s */
#include <stdio.h>
void squeeze(char s[], int c)
{
  int i, j;
  for (i = j = 0; s[i] != '\0'; i++) {
    if (s[i] != c)
      s[j++] = s[i];
    s[j] = '\0';
  }
}

int main(int argc, char *argv[])
{
  char input[] = "all your base are belong to us";

  squeeze(input, 'a');
  printf("\nRemoving 'a' → result: %s", input);

  squeeze(input, 'l');
  printf("\nRemoving 'l' → result: %s", input);

  squeeze(input, ' ');
  printf("\nRemoving spaces → result: %s", input);
  return 0;
}
