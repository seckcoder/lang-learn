#include <string>
#include <iostream>
using namespace std;

#define M 1000

bool is_palindrome[M][M];
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        if (n == 0) return "";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                is_palindrome[i][j] = false;
            }
        }
        
        for (int i = 0; i < n; i++) {
            is_palindrome[i][i] = true;
        }
        
        // len = 2
        
        for (int i = 0; i + 1 < n; i++) {
            if (s[i] == s[i+1]) {
                is_palindrome[i][i+1] = true;
            }
        }
        
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                if (s[i] == s[i+len-1] && is_palindrome[i+1][i+len-2]) {
                    is_palindrome[i][i+len-1] = true;
                }
            }
        }
        
        for (int len = n; len >= 1; len--) {
            for (int i = 0; i + len - 1 < n; i++) {
                if (is_palindrome[i][i+len-1]) {
                    return s.substr(i, len);
                }
            }
        }
        return ""; // just make compiler happy
    }
};

int main() {
  Solution sol;
  cout << sol.longestPalindrome("aaaaaaaa") << endl;
  return 0;
}
