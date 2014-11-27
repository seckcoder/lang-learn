class Solution {
public:
    int numDistinct(string S, string T) {
      int n = S.size(),
          m = T.size();
      if (n == 0) return 0;
      if (m == 0) return 0;
      // initialization
      vector<vector<int> > dp(n, vector<int>(m, 0));
      if (S[n-1] == T[m-1]) dp[n-1][m-1] = 1;

      for (int i = n-2; i >= 0; i--) {
        if (S[i] == T[m-1]) {
          dp[i][m-1] = dp[i+1][m-1] + 1;
        } else {
          dp[i][m-1] = dp[i+1][m-1];
        }
        for (int j = m-2; j >= std::max(0, m-n+i); j--) {
          if (S[i] == T[j]) {
            dp[i][j] = dp[i+1][j] + dp[i+1][j+1];
          } else {
            dp[i][j] = dp[i+1][j];
          }
        }
      }
      return dp[0][0];
    }
};
