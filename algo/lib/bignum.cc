#include "bignum.h"

#include <iostream>

using namespace std;

int main() {
  Bignum v1;
  v1 += 12345;
  cout << v1 << endl;
  v1 *= 20000;
  cout << v1 << endl;
  Bignum v2;
  v2 += 3224348;
  v1 += v2;
  cout << v1 << endl;
  return 0;
}
