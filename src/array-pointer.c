

#include <stdio.h>
int main(int argc, char *argv[])
{
  int array_length = 4;
  float array[array_length];
  for (int i = 0; i < array_length; i++) {
    array[i] = (float)(i * 100);
  }

  float* index_ptr = &array[0];

  for (int i = 0; i < array_length; i++) {
    float element = *index_ptr;
    printf("Element of index_ptr: %f, array[%d] → %f\n", *index_ptr, i, array[i]);
    index_ptr++;
  }

  return 0;
}
