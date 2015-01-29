#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

#define MAX_M 1000
int dp[2][MAX_M];
class Solution {
  public:
    int calculateMinimumHP(vector<vector<int> > &dungeon) {
      int m = dungeon.size(), n = dungeon[0].size();
      int i = (m-1), hi = i % 2;
      int j;
      dp[hi][n-1] = std::max(1,1-dungeon[i][n-1]);
      for (j = n-2; j >= 0; j--) {
        dp[hi][j] = std::max(1, dp[hi][j+1]-dungeon[i][j]);
      }
      for (i = m-2; i >= 0; i--) {
        int hi = i % 2, hi1 = (i+1)%2;
        dp[hi][n-1] = std::max(1, dp[hi1][n-1]-dungeon[i][n-1]);
        for (j = n-2; j >= 0; j--) {
          dp[hi][j] = std::max(1, std::min(dp[hi1][j]-dungeon[i][j],
                                           dp[hi][j+1]-dungeon[i][j]));
        }
      }
      return dp[0][0];
    }
};

int main() {

  Solution sol;

  vector<vector<int> > vec(3);
  vec[0].resize(3);
  vec[0][0] = -2; vec[0][1] = -3; vec[0][2] = 3;
  vec[1].resize(3);
  vec[1][0] = -5; vec[1][1] = -10; vec[1][2] = 1;
  vec[2].resize(3);
  vec[2][0] = 10; vec[2][1] = 30; vec[2][2] = -5;
  cout << sol.calculateMinimumHP(vec) << endl;
  return 0;
}
