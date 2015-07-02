#include <iostream>
using namespace std;


int T(int m, int n) {
  if (n == 0) return 1;
  if (m == 0) return 1;

  return T(m-1,n) + T(m, n-1);
}



int main() {
  cout << T(10,3) << endl;
  return 0;
}
