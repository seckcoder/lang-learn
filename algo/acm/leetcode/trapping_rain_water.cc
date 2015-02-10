#include <iostream>
using namespace std;

class Solution {
public:
    int trap(int A[], int n) {
      if (n == 0) return 0;
      int *max_left = (int *)malloc(n*sizeof(int));
      int *max_right = (int *)malloc(n*sizeof(int));
      max_left[0] = 0;
      for (int i = 1; i < n; i++) {
        max_left[i] = std::max(max_left[i-1], A[i-1]);
      }
      max_right[n-1] = 0;
      for (int i = n-2; i >= 0; i--) {
        max_right[i] = std::max(max_right[i+1], A[i+1]);
      }
      int total_trapped_water = 0;
      for (int i = 1; i < n-1; i++) {
        int max_level = std::min(max_left[i], max_right[i]);
        if (max_level > A[i]) {
          total_trapped_water += max_level - A[i];
        }
      }
      free(max_left);
      free(max_right);
      return total_trapped_water;
    }
};

int main() {
  int A[] = {0,1,0,2,1,0,1,3,2,1,2,1};
  cout << Solution().trap(A, 12) << endl;
  return 0;
}
