class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
      if (triangle.size() == 0) return 0;
      
      int n = triangle.size();
      vector<int> dp(triangle[n-1].begin(),
                     triangle[n-1].end());

      for (int i = triangle.size() - 2; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
          dp[j] = std::max(dp[j+1] + triangle[i][j],
                           dp[j] + triangle[i][j]);
        }
      }
      return dp[0];
    }
};
