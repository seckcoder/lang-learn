#include <cstdlib>
#include <algorithm>
 
class Solution {
public:
    int firstMissingPositive(int A[], int n) {
      int p = partition(A, n);
      return findMissingPositiveInPositveArray(A+p, n-p);
    }
    // return p: [0-p) <= 0, [p, n) > 0
    int partition(int A[], int n) {
      // loop invariant:
      //  [0,i) <= 0, [i,j) > 0
      int i = 0, j = 0;

      for (; j < n; j++) {
        if (A[j] <= 0) {
          std::swap(A[i], A[j]);
          i += 1;
        }
      }
      return i;
    }
    // A[0-n] >= 1, Find the first missing positive in the array
    int findMissingPositiveInPositveArray(int *A, int n) {
      for (int i = 0; i < n; i++) {
        int abs_v = std::abs(A[i]);
        if (abs_v <= n && A[abs_v-1] > 0) {
          A[abs_v-1] = -A[abs_v-1]; // set value of index (abs_v-1) to negative
        }
      }
      for (int i = 0; i < n; i++) {
        if (A[i] > 0) {
          // first missing positive
          return i+1;
        }
      }
      return n+1;
    }
};
