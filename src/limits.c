#include <limits.h>
#include <float.h>
#include <stdio.h>

int main(void)
{
  printf("\nLimits of short\n   [%i, %i]", SHRT_MIN, SHRT_MAX);
  printf("\nLimits of int\n   [%i, %i]", INT_MIN, INT_MAX);
  printf("\nLimits of long\n   [%lli, %llu]", LLONG_MIN, LLONG_MAX);

  printf("\nLimits of float\n   [%f, %f]", FLT_MIN, FLT_MAX);
  printf("\nLimits of double\n   [%ff, %ff]", DBL_MIN, DBL_MAX);
  return 0;
}
