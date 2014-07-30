#include "test1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*char *f() {
  char *p = (char*)malloc(10);
  return p;
}*/

void foo(char **pp) {
  *pp = (char*)malloc(10*sizeof(char));
  strcpy(*pp, "abcd");
}

char *global = "abcd";
char *g() {
  return global;
}


/*void h() {
  char *p = "abc";
  free(p);
}*/

void bar(int *pv) {
  *pv = 10;
}

void fxx(int *pa, int *pb) {
  *pa = 0;
  *pb = 1;
}

void demo() {
  char c = 1;
  char str[10];
  for(int i = 0; i < 10; i++) {
    str[i] = (char)1;
  }
  printf("%s\n", str);
}

int main(int argc, const char *argv[])
{
  demo();
  return 0;
}
