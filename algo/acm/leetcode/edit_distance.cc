#include <string>
using namespace std;

#define M 1000
int dp[M][M];

int min(int a, int b, int c) {
  return std::min(std::min(a,b), c);
}
class Solution {
public:
    int minDistance(string word1, string word2) {
      if (word1.length() == 0) return word2.length(); // insert
      if (word2.length() == 0) return word1.length(); // insert

      dp[0][0] = 0;
      for (int i = 1; i <= word1.length(); i++) dp[i][0] = i;
      for (int j = 1; j <= word2.length(); j++) dp[0][j] = j;

      for (int i = 1; i <= word1.length(); i++) {
        for (int j = 1; j <= word2.length(); j++) {
          if (word1[i-1] == word2[j-1]) {
            dp[i][j] = min(
                dp[i-1][j-1],
                dp[i][j-1] + 1,
                dp[i-1][j] + 1);
          } else {
            dp[i][j] = min(
                dp[i-1][j-1]+1,
                dp[i][j-1]+1,
                dp[i-1][j]+1);
          }
        }
      }
      return dp[word1.length()][word2.length()];
    }
};
