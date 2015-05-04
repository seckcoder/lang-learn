#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

inline int sign(int v) {
  return (v & (1<<31)) != 0;
}

class Solution {
public:
    bool isPositive(int &numerator, int &denominator) {
      int sign_num = sign(numerator);
      int sign_den = sign(denominator);
      return ((sign_num + sign_den) % 2) != 1;
    }
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) return "0";
        bool positive = isPositive(numerator, denominator);
        long dividend = numerator, divisor = denominator;
        dividend = std::abs(dividend);
        divisor = std::abs(divisor);
        vector<long> fractions;
        typedef unordered_map<long, int> HashMap;
        HashMap dividend_idx_map;
        int idx = 0;
        // simulation of divide procedure
        while (dividend != 0) {
            if (dividend_idx_map.find(dividend) != dividend_idx_map.end()) {
                // we find the same dividend. So fractional part is repeating
                return constructRepeating(positive, fractions, dividend_idx_map[dividend]);
            } else {
                dividend_idx_map[dividend] = idx;
                long quotient = dividend / divisor,
                     remainder = dividend % divisor;
                fractions.push_back(quotient);
                dividend = remainder * 10;
                idx += 1;
            }
        }
        return fractionsToString(positive, fractions);
    }
    string fractionsToString(bool positive, const vector<long> &fractions) {
        string fraction;
        if (!positive) fraction += "-";
        fraction += std::to_string(fractions[0]);
        if (fractions.size() == 1) return fraction;
        fraction += ".";
        for (int i = 1; i < fractions.size(); i++) {
            fraction += std::to_string(fractions[i]);
        }
        return fraction;
    }
    string constructRepeating(bool positive, const vector<long> &fractions, int repeat_idx) {
        string fraction;
        if (!positive) fraction += "-";
        fraction += std::to_string(fractions[0]);
        fraction += ".";
        for (int i = 1; i < repeat_idx; i++) {
            fraction += std::to_string(fractions[i]);
        }
        fraction += "(";
        for (int i = repeat_idx; i < fractions.size(); i++) {
            fraction += std::to_string(fractions[i]);
        }
        fraction += ")";
        return fraction;
    }
};

int main() {
  /* cout << Solution().fractionToDecimal(1, 2) << endl; */
  /* cout << Solution().fractionToDecimal(2, 1) << endl; */
  /* cout << Solution().fractionToDecimal(2, 3) << endl; */
  /* cout << Solution().fractionToDecimal(-2, 3) << endl; */
  cout << Solution().fractionToDecimal(-1, -2147483648) << endl;
  return 0;
}
