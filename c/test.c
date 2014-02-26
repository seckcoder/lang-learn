











#include <stdio.h>

int foo() {
  int c = 1;
  {
    int c = c;
    printf("%d\n",c);
  }
  return c;
}

int main(int argc, const char *argv[]) {
  foo();
  return 0;
}
