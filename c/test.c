



#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

int N[1000];
int *bar() {
  return N;
}

int foo() {
  int c = 1;
  {
    int c = c;
    printf("%d\n",c);
  }
  return c;
}

void f(void *p) {
  // p
}

int foo() {
  int v = 4;
  return v;
}

char *f() {
  char *p = (char*)malloc(...);
  return p;
}
char *global = "abc";
char *g() {
  return global;
}

int main(int argc, const char *argv[]) {
}
