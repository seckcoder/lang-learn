#include <string>
#include <iostream>
using namespace std;
#define M 100
bool dp[M][M][M];
class Solution {
public:
    bool isScramble(string s1, string s2) {
      // k, s1, s2
      // dp[k][i][j] = (dp[u][i][j] && dp[k-u][i+u][j+u]) || (dp[u][i][j+k-u] && dp[k-u][i+u][j]
     
      if (s1.size() != s2.size()) return false;
      int n = s1.size();
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (s1[i] == s2[j]) dp[1][i][j] = true;
          else dp[1][i][j] = false;
        }
      }
      for (int k = 2; k <= n; k++) {
        for (int i = 0; i < n-k+1; i++) {
          for (int j = 0; j < n-k+1; j++) {
            dp[k][i][j] = false;
            for (int u = 1; u < k; u++) {
              if ((dp[u][i][j] && dp[k-u][i+u][j+u]) ||
                  (dp[u][i][j+k-u] && dp[k-u][i+u][j])) {
                dp[k][i][j] = true;
                break;
              }
            }
          }
        }
      }
      return dp[n][0][0];
    }
};


int main() {
  Solution sol;
  cout << sol.isScramble("a", "b") << endl;
  return 0;
}
