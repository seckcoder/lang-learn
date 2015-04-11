#include <stdio.h>


#define SET(p, v) (*p = v)
#define SET(p, v1,v2) (*p = v1 | v2)

int main ()
{
  int x;
  int *px = &x;
  SET(px, 4);
  return 0;
}
