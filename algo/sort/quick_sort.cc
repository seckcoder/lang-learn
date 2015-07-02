#include <vector>
#include "debug.h"

using namespace std;



// partion vec. return q. 
// vec[p,q-1] <= vec[q] < vec[q+1,r]
template <class T>
inline int partition(vector<T> &vec, int p, int r) {
  T &v = vec[r];
  int i = p-1;
  // loop invariant: [p,i] <= v, [i+1,j) > v
  for (int j = p; j < r; j+= 1) {
    if (vec[j] <= v) {
      i += 1;
      std::swap(vec[i], vec[j]);
    }
  }
  std::swap(vec[r], vec[i+1]);
  return i+1;
}

template <class T>
void qsort1(vector<T> &vec, int p, int r) {
  while (p <= r) {
    int m = partition(vec, p, r);
    if (r - m < m - p) {
      // call qsort on smaller range to reduce stack depth.
      qsort1(vec, m+1, r);
      r = m-1;
    } else {
      qsort1(vec, p, m-1);
      p = m+1;
    }
  }
}

template <class T>
void qsort(vector<T> &vec) {
  qsort1(vec, 0, vec.size() - 1);
}


int main() {
  vector<int> vec { 1,2,3,0,4 };
  qsort(vec);
  debugVec(vec);
  return 0;
}

