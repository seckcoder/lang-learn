#include <iostream>
using namespace std;

typedef unsigned char uint8;

uint8 v[10];
void test() {
  int *plen = (int*)&v[0];
  cout << *plen << endl;
}
int main(int argc, const char *argv[])
{
  int *plen = (int*)&v[0];
  *plen = 4;
  *plen += 1;
  test();
  return 0;
}
