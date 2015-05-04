#include <iostream>
#include <string>
using namespace std;


class Solution {
public:
    int numDecodings(string s) {
        return numDecodings(s, 0);
    }
    int numDecodings(string s, int start) {
        if (start >= s.length()) return 1;
        int s_len = s.length();
        int max_len = std::min(2, s_len - start);
        int num_decodings = 0;
        for (int len = 1; len <= max_len; len++) {
            if (canDecode(s, start, len)) {
                num_decodings += numDecodings(s, start+len);
            }
        }
        return num_decodings;
    }
    bool canDecode(string s, int start, int len) {
        if (s[start] == '0') return false;
        int sum = 0;
        for (int i = start; i < start+len; i++) {
            sum = sum * 10 + (s[i] - '0');
        }
        return 1 <= sum && sum <= 26;
    }
};

int main() {
  cout << Solution().numDecodings("9371597631128776948387197132267188677349946742344217846154932859125134924241649584251978418763151253") << endl;
  return 0;
}
