#include <iostream>
#include "memoize.h"
#include "utils.h"
using namespace std;


int slowReturn(int v) {
  wait(1);
  return v;
}
int main() {
  auto slow = memoize(slowReturn);
  cout << slow(10) << endl;
  cout << slow(10) << endl;
  cout << slow(11) << endl;
  return 0;
}
