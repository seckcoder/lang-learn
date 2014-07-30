#include <stdio.h>


int main(int argc, const char *argv[])
{
  int p1[] = {0,1,2,3,4,5};

  int* p2 = p1 + 2;
  printf("%d %d\n", p1, (int)p2);
  return 0;
}
