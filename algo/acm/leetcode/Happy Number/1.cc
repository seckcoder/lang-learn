#include <unordered_set>
#include <vector>
using std::unordered_set;
using std::vector;

#define SQUARE(v) ((v)*(v))
class Number {
  public:
    static void toDigits(int n, vector<char> &digits) {
      digits.clear();
      if (n == 0) {
        digits.push_back(n);
        return;
      }
      while (n != 0) {
        digits.push_back(char(n % 10));
        n = n / 10;
      }
    }
    static int fromDigits(const vector<char> &digits) {
      int n = 0;
      for (int i = 0; i < digits.size(); i++) {
        n = n * 10 + int(digits[i]);
      }
      return n;
    }
};

class Solution {
  public:
    bool isHappy(int n) {
      vector<char> digits;
      Number::toDigits(n, digits);
      
      unordered_set<int> visited_num;
      while (1) {
        int cur_v = Number::fromDigits(digits);
        if (cur_v == 1) {
          return true;
        }
        if (visited_num.find(cur_v) != visited_num.end()) {
          return false;
        }
        visited_num.insert(cur_v);
        Number::toDigits(nextNum(digits), digits);
      }
    }

    int nextNum(const vector<char> &digits) {
      int n = 0;
      for (int i = 0; i < digits.size(); i++) {
        n += SQUARE(int(digits[i]));
      }
      return n;
    }
};


#include <iostream>
using namespace std;
int main() {
  Solution sol;
  cout << sol.isHappy(19) << endl;
  cout << sol.isHappy(100) << endl;
  return 0;
}
