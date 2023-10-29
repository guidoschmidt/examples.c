#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int n = 0;
  int *ptr = 0;
  int sum = 0;

  printf("Enter number of elements");
  scanf("%d", &n);

  // calloc
  // allocates memory and initialises it with 0
  ptr = (int*)calloc(n, sizeof(int));

  if (ptr == NULL) {
    fprintf(stderr, "Could not allocate memory!");
    return -1;
  }

  printf("Enter elements:\n");
  for (int i = 0; i < n; i++) {
    scanf("%d", ptr + i);
    sum += *(ptr + i);
  }
  printf("Sum of all elements is %d", sum);

  free(ptr);

  return 0;
}
