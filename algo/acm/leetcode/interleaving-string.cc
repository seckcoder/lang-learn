 #define N 1000
 class Solution {
  public:
   bool isInterleave(string s1, string s2, string s3) {
     if (s1.length() + s2.length() != s3.length()) return false;
     bool dp[N][N] = {false};
     dp[0][0]
     for (int i = 1; i < s1.length(); i++) {
         for (int j = 0; j < s2.length(); j++) {
             if (s1[i] == s3[i+j+1] && dp[i-1][j]) dp[i][j] = true;
             else if (s2[j] == s3[i+j+1] && dp[i][j-1]) dp[i][j] = true;
         }
     }
   }
 };
