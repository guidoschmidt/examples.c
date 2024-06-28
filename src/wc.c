#include <stdio.h>

const int IN = 1;
const int OUT = 0;

int main(int argc, char *argv[])
{
  int c;
  int new_char = 0;
  int new_word = 0;
  int new_line = 0;
  int state;
  state = OUT;
  while(1) {
    ++new_char;
    c = getchar();
    if (c == EOF)
      break;
    if (c == '\n')
      ++new_line;
    if (c == ' ' || c == '\n' || c == '\t')
      state = OUT;
    else if (state == OUT) {
      state = IN;
      ++new_word;
    }
  }
  printf("lines: %d, words: %d, chars: %d\n", new_line, new_word, new_char);
  return 0;
}
