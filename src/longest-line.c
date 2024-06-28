#include <stdio.h>
const int MAX_LINE_LENGTH = 1000;

int max_length;
char line[MAX_LINE_LENGTH];
char longest_line[MAX_LINE_LENGTH];

int getline(void);
void copy(void);

int main(int argc, char *argv[])
{
  int length;
  max_length = 0;

  while ((length = getline()) > 0)
    if (length > max_length) {
      max_length = length;
      copy();
    }
  if (max_length > 0)
    printf("%s", longest_line);
  return 0;
}

int getline(void) {
  
}
