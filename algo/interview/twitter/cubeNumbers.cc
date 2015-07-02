#include <iostream>
using namespace std;

inline int cube(int x) {
  return x*x*x;
}

/* inline int cubeMax(int cube_num) { */
/*   int x = 1; */
/*   for (; x <= 47 && cube(x) <= cube_num; x++) {} */
/*   return x-1; */
/* } */


inline int cubeMax(int A, int n) {
  if (A == 1) return 1;
  int v = n / A;
}

int cubeNumbers(int m, int n) {
  m = std::min(m,n);
  n = std::min(m,n);

  for (int A = 1; A <= m; A++) {
    cubeMax(A, n);
  }
}


int main() {
  cout << cubeNumbers(100000, 100000) << endl;
  return 0;
}
