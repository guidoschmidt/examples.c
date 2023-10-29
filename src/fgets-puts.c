#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{

  char name[30];
  printf("Enter player name: ");
  fgets(name, sizeof(name), stdin);

  printf("\nEnter a text:\n");

  // Read a string
  char text[100];
  fgets(text, sizeof(text), stdin);
  printf("Echo:\n");
  puts(text);

  // Common string functions
  printf("Your text length %lu", strlen(text));

  // Magic word
  char magic_word[] = "Big Whoop";
  int distance = strcmp(magic_word, "Big Whoop");
  printf("\nDistance to magic word: %i\n", distance);
  if (distance == 0) {
    printf("Whoop! You've guessed the magic word");
  }

  char output[100 + 30];
  strcat(output, name);
  strcat(output, " entered ");
  strcat(output, text);
  printf("\n%s", output);

  return 0;
}
