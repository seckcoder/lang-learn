#include <inttypes.h>
#include <algorithm>


class Solution1 {
  public:
    uint32_t reverseBits(uint32_t n) {
      char bits[32] = {0};
      intToBits(n, bits);
      std::reverse(bits, bits+32);
      return bitsToInt(bits);
    }
    static void intToBits(uint32_t n, char bits[]) {
      int i = 0;
      while (n != 0) {
        bits[i] = char(n % 2);
        n /= 2;
        i += 1;
      }
    }
    static uint32_t bitsToInt(char bits[]) {
      uint32_t n = 0;
      for (int i = 0; i < 32; i++) {
        if (int(bits[i])) {
          n += 1 << i;
        }
      }
      return n;
    }
};

class Solution {
  public:
    uint32_t reverseBits(uint32_t n) {
      uint32_t ans = 0;
      for (int i = 0; i < 32; i++) {
        if (n & (1 << i)) {
          ans |= (1 << (31-i));
        }
      }
      return ans;
    }
};



#include <iostream>
using namespace std;
int main()
{
  Solution sol;
  cout << sol.reverseBits(43261596) << endl;
  return 0;
}
