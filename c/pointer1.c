#include <stdio.h>


int main(int argc, const char *argv[])
{
  int p[2] = {1, 2};
  int v = *(p+1);
  printf("%u %u\n", p, (p+1));
  char *c = "abcde";
  printf("%u %u\n", c, (c+1));
  /*printf("%u %u\n", (unsigned int)c, (unsigned int)c[0]);*/
  return 0;
}
