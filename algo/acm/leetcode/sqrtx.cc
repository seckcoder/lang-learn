#include <iostream>

using namespace std;
class Solution {
public:
    int sqrt(int x) {
      if (x <= 1) return x;
      int p = 1, r = std::min(x >> 1, 46340), mark = -1;
      while (p <= r) {
        int m = (p+r) >> 1;
        int val = m * m;
        if (val <= x) {
          mark = m;
          p = m + 1;
        } else if (val > x) {
          r = m - 1;
        }
      }
      return mark;
    }
};


int main() {
  Solution sol;
  cout << sol.sqrt(2147395599) << endl;
  return 0;
}
