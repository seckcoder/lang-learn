#include <iostream>
using namespace std;

class Solution {
public:
    int trap(int A[], int n) {
      return recur(A, 0, n-1);
    }
    // A[p-r] forms a U shape
    int U(int A[], int p, int r) {
      int base_height = std::min(A[p], A[r]);
      int area = 0;
      for (int i = p+1; i < r; i++) {
        area += std::max(0, base_height - A[i]);
      }
      return area;
    }
    int recur(int A[], int p, int r) {
      if (p >= r) return 0;
      //if (A[p] <= A[p+1]) return recur(A, p+1, r);

      // get to the left point
      while (p < r && A[p] <= A[p+1]) {
        p += 1;
      }

      if (p >= r) return 0;

      int left = p;

      // get to the middle point
      while (p < r && A[p] >= A[p+1]) {
        p += 1;
      }
      if (p >= r) return 0;

      // get to the right point
      while (p < r && A[p] <= A[p+1]) {
        p += 1;
      }
      cout << left << " " << p << endl;
      return U(A, left, p) + recur(A, p, r);
    }
};

int main() {
  int A[] = {0,1,0,2,1,0,1,3,2,1,2,1};
  cout << Solution().trap(A, 12) << endl;
  return 0;
}
