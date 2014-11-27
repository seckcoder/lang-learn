#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProfit(vector<int> &prices) {
    if (prices.size() == 0) return 0;
    int n = prices.size();
    int dp = 0, // dp[n-1] = 0
        partial = prices[n-1];  // partial[n-1]

    for (int i = n-2; i >= 0; i--) {
      dp = std::max(dp, partial - prices[i]);
      partial = std::max(partial, dp + prices[i]);
    }
    return dp;
  }
};

int main(int argc, const char *argv[])
{

  Solution sol;
  vector<int> prices({1, 2, 1, 3});
  cout << sol.maxProfit(prices) << endl;
  return 0;
}
