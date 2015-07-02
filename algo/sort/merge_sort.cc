#include <vector>
#include "debug.h"

using namespace std;



template <class T>
void mergeSortRec(vector<T> &vec, vector<T> &tmp, int p, int r) {
  if (p >= r) return;
  int m = (p+r) / 2;

  mergeSortRec(vec, tmp, p, m);
  mergeSortRec(vec, tmp, m+1, r);

  {
    int i,j,k;
    for (i = p, j = m+1,k = 0; i <= m && j <= r; k += 1) {
      if (vec[i] <= vec[j]) {
        tmp[k] = vec[i];
        i += 1;
      } else {
        tmp[k] = vec[j];
        j += 1;
      }
    }
    while (i <= m) {
      tmp[k] = vec[i];
      i += 1;
      k += 1;
    }
    while (j <= r) {
      tmp[k] = vec[j];
      j += 1;
      k += 1;
    }
  }
  for (int i = 0; i < r-p+1; i++) {
    vec[p+i] = tmp[i];
  }
}

template <class T>
void mergeSort(vector<T> &vec) {
  vector<T> tmp(vec.size());
  mergeSortRec(vec, tmp, 0, vec.size() - 1);
}

int main() {
  vector<int> vec {2,1,0,3,4};
  mergeSort(vec);
  debugVec(vec);
  return 0;
}
