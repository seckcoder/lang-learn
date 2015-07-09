
#include "../base.h"




void yoo(vector<int> &tmp) {
  tmp.push_back(3);
}
void bar(vector<int> &&tmp) {
  /* in the function bar, tmp is a lvalue */
  tmp.push_back(1);
  yoo(tmp);
  printVec(tmp);
}

void foo() {
  bar(vector<int>());
}


int main() {
  foo();
  return 0;
}
