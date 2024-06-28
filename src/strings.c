#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char string[] = "a string is a sequenc of chars!";
  for (int i = 0; i < sizeof(string) / sizeof(char); i++) {
    printf("string[%*i] → %c\n", 2, i, string[i]);
  }

  /* printf("Please give me your name...\nEnter name: "); */
  /* char name[100]; */
  /* scanf("%s", name); */
  /* printf("3rd character in your name is %c", name[3]); */

  // Comparing strings
  char find_path[] = "/index.html";
  char test_path[] = "           ";
  printf("\nLooking for %s", find_path);
  int comparison = strcmp(find_path, test_path);
  printf("\nCompared value: %i", comparison);
  while (comparison != 0) {
    printf("\nNext guess: ");
    scanf("%s", test_path);
    comparison = strcmp(find_path, test_path);
    printf("\nCompared value: %s %s → %i", find_path, test_path, comparison);
  }

  char path_buf[256] = "/";
  char test_buf[256] = "/";
  int compared = strcmp("/", path_buf);
  printf("\nComparison %i", compared);
  
  return 0;
}
