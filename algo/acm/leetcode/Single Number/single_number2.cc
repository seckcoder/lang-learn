#include <cstdio>

typedef unsigned char Byte;
// Note: v should be unsigned int. Otherwise, we can't
// get the 31th bit
inline Byte ithBit(unsigned int v, int i) {
  return (v & (1<<i))>>i;
}
class Solution1 {
  public:
    int singleNumber(int A[], int n) {
      Byte bits[32] = {0};
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < 32; j++) {
          bits[j] += ithBit(A[i], j);
          //printf("%d %d %d\n", A[i], j, bits[j]);
          bits[j] %= 3; // Byte <= 255, so %=3 here.
        }
      }
      int ans = 0;
      for (int j = 0; j < 32; j++) {
        if (bits[j] == 1) {
          ans |= (1<<j);
        }
      }
      return int(ans);
    }
};


// Faster.
class Solution2 {
  public:
    int singleNumber(int A[], int n) {
      Byte bits[32] = {0};
      for (int i = 0; i < n; i++) {
        unsigned int v = A[i];
        int j = 0;
        while (v != 0) {
          bits[j] += v % 2;
          bits[j] %= 3;
          v /= 2;
          j += 1;
        }
      }
      int ans = 0;
      for (int j = 0; j < 32; j++) {
        ans += (bits[j] << j);
      }
      return ans;
    }
};
int main() {
  int A[] = {-2,-2,1,1,-3,1,-3,-3,-4,-2};
  printf("%d\n", Solution().singleNumber(A, 10));
  return 0;
}
