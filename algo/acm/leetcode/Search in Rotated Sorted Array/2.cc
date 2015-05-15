#include <iostream>
using namespace std;


bool search(int A[], int n, int target) {
  int p = 0, r = n-1;
  int base = A[r];
  while (p <= r) {
    int m = p + (r-p)/2; // avoid overflow!!!
    if (A[m] == target) return true;
    if (A[m] < base) {
      // mono increasing between [m,r]
      if (A[m] < target && target <= A[r]) {
        p = m + 1;
      } else {
        // A[m] > target or A[r] < target
        r = m - 1;
      }
    } else if (A[m] > base) {
      // mono increasing between [p,m]
      if (A[m] > target && target >= A[p]) {
        r = m - 1;
      } else {
        // A[m] < target or target < A[p]
        p = m + 1;
      }
    } else if (A[m] == base) {
      // when duplicates exist, we do a linear search in [p,r]
      for (int i = p; i <= r; i++) {
        if (A[i] == target) {
          return true;
        }
      }
      return false;
    }
  }
  return false;
}


int main() {
  int A[] = {3,5,1};
  cout << search(A, 3, 3) << endl;
  return 0;
}
