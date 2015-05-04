#include <iostream>
using namespace std;

/*
 * Basic idea:
 * Use << operator.
 *
 * a * (2^k) = a * (1<<k) = a<<k
 * Also, a * (x1 + x2) = a*x1 + a * x2
 * So, we can formulate it as follows:
 *
 * Suppose a / d = q. and d = 2^x0 + 2^x1 + 2^x2 + ... with x0 > x1 > x2 > ...
 * Let a' = d * q. Then a >= a' and a-a' < d.
 * also a' = d * 2^x0 + d * 2^x1 + ....
 * Apparently, x0 is largest integer, such that d * 2^x0 <= a. Also, 0<= x0 <= 32 based on the
 * input integer range.
 * 
 */
class Solution {
public:
    int divide(int dividend, int divisor) {
        if (divisor == 0) return INT_MAX;
        bool positive = false;
        if ((dividend > 0 && divisor > 0 ) ||
            (dividend < 0 && divisor < 0)) {
                positive = true;
            }
        
        // use long long int to avoid overflow here.
        long long int abs_dividend = dividend;
        abs_dividend = std::abs(abs_dividend);
        long long int abs_divisor = divisor;
        abs_divisor = std::abs(abs_divisor);

        long long int quotient = 0;
        // use one here to replace 1. 1 << le may overflow.
        long long int one = 1;

        // if abs_dividend < abs_divisor, then quotient = 0
        while (abs_dividend >= abs_divisor) {
          // first largest integer, such that abs_dividend >= abs_divisor * (2 ^ le).
          int le = findLargestLessEqual(abs_dividend, abs_divisor);
          // Note: we need to cast 1 to int64 here to avoid possible overflow
          quotient += one << le;
          abs_dividend -= abs_divisor << le;
        }
        // check whether overflow happens.
        if ((positive && quotient > (long long int)INT_MAX) || 
            (!positive && -quotient < (long long int)INT_MIN)) {
          return INT_MAX;
        }
        if (positive) return quotient;
        else return -quotient;
    }
    // we can use binary search here. But it's not necessary since it's already
    // very fast here.
    int findLargestLessEqual(long long int dividend, long long int divisor) {
      for (int i = 31; i >= 0; i--) {
        if ((divisor << i) <= dividend) {
          return i;
        }
      }
      return 0; // make compiler happy.
    }
};


int main() {
  Solution sol;
  cout << sol.divide(-2147483648, -1) << endl;
  return 0;
}
