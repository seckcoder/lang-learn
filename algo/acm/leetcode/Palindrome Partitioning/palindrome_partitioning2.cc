
#include <iostream>
#include <string>
using namespace std;

#define M 2000

bool isPalindrome[M][M];
int dp[M][M];

// O(n^3) solution to get min cut. Optimized considering cache coherence.
// But still too slow...
class Solution1 {
  public:
    int minCut(string s) {
      int n = s.length();

      // construct is palindrome
      
      for (int i = 0; i < n; i++) {
        isPalindrome[0][i] = true;
        isPalindrome[1][i] = true;
        //isPalindrome[i][0] = true;
        //isPalindrome[i][1] = true;
      }
      for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
          //isPalindrome[i][len] = s[i] == s[i+len-1] && isPalindrome[i+1][len-2];
          isPalindrome[len][i] = s[i] == s[i+len-1] && isPalindrome[len-2][i+1];
        }
      }

      for (int i = 0; i < n; i++) {
        dp[1][i] = 0;
        //dp[i][1] = 0;
      }
      
      for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
          if (isPalindrome[len][i]) {
            dp[len][i] = 0;
            //dp[i][len] = 0;
          } else {
            // dp[i][len] = len-1; // cut at very element
            int tmp = len - 1;
            for (int j = i; j < i+len-1; j++) {
              if (isPalindrome[j-i+1][i]) {
                // ... 
                tmp = std::min(tmp, 1+dp[len-(j-i+1)][j+1]);
              }
            }
            dp[len][i] = tmp;
          }
        }
      }
      return dp[n][0];
    }
};


int dp1[M];
// O(n^2) Solution.
// We only need to consider starting index from 0, right?
class Solution {
  public:
    int minCut(string s) {
      int n = s.length();

      // construct is palindrome
      
      for (int i = 0; i < n; i++) {
        isPalindrome[0][i] = true;
        isPalindrome[1][i] = true;
      }
      for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
          isPalindrome[len][i] = s[i] == s[i+len-1] && isPalindrome[len-2][i+1];
        }
      }
      for (int i = 0; i < n; i++) {
        if (isPalindrome[i+1][0]) dp1[i] = 0;
        else {
          dp1[i] = i;
          for (int j = 1; j <= i; j++) {
            if (isPalindrome[i-j+1][j]) {
              dp1[i] = std::min(dp1[i], 1+dp1[j-1]);
            }
          }
        }
      }
      return dp1[n-1];
    }
};

int main() {
  //const string s = "ababbbabbababa";
  const string s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  cout << s.length() << endl;
  cout << Solution().minCut(s) << endl;
  return 0;
}
