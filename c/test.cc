#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, const char *argv[])
{

  const char *buf = "abc";
  for (int i = 0; buf[i] != '\0'; i++) {
    printf("%c\n", buf[i]);
  }
  return 0;
}
