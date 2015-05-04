
class Solution {
  public:
    int maxSum(int A[], int n) {
      int max_sum = 0;
      int max_until = 0;

      for (int i = 0; i < n; i++) {
        max_until += A[i];
        if (max_until < 0) {
          max_until = 0;
        } else {
          max_sum = std::max(max_sum, max_until);
        }
      }
    }
};
