#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

void reconstruct(const char *s) {
  string str(s);
  // move elements in str not equal to * to the end.
  auto it = remove(str.rbegin(), str.rend(), '*');
  // fill begin to it with *
  fill(it, str.rend(), '*');
  cout << str << endl;
}

int main() {
  reconstruct("***abc**d");
  return 0;
}
