#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
      if (prices.size() == 0) return 0;

      #define TWO_TRAN 1
      #define ONE_TRAN 0
      int n = prices.size();
      int dp[2] = {0}; // dp[n-1] = 0
      int max_prev_dp[2] = {0}; // 
      int max_partial = prices[n-1];
      int max_prev_prices = prices[n-1];
  
      for (int i = n-2; i >= 0; i--) {
        dp[TWO_TRAN] = std::max(dp[TWO_TRAN],
                                max_partial - prices[i]);
        dp[ONE_TRAN] = std::max(dp[ONE_TRAN],
                                max_prev_prices - prices[i]);
        max_partial = std::max(max_partial,
                               dp[ONE_TRAN] + prices[i]);
        max_prev_prices = std::max(max_prev_prices,
                                   prices[i]);
      }
      return std::max(dp[ONE_TRAN], dp[TWO_TRAN]);
    }
};


int main(int argc, const char *argv[])
{
  
  return 0;
}
