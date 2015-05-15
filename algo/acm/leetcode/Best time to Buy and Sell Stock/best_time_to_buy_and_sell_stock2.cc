#include <iostream>
#include <vector>

using namespace std;

class Solution1 {
 public:
  int maxProfit(vector<int> &prices) {
    int ans = 0;
    int n = prices.size();
    for (int i = 0; i < n - 1; i++) {
      if (prices[i+1] > prices[i]) {
        ans += prices[i+1] - prices[i];
      }
    }
    return ans;
  }
};


/* 
 * max_profit[k]:  max_profit we can get for prices [k..]
 *
 * max_profit[k] = std::max(
 *    max_profit[k+1], // not buy
 *    std::max{max_profit[i] + prices[i] - prices[k], forall i > k} // buy
 *    );
 * 
 * optimization:
 *
 * max_profit[k] = std::max(max_profit[k+1],
 *    std::max{max_profit[i] + prices[i], forall i > k} - prices[k])
 * 
 * We can use a single variable to memorize std::max{max_profit[i] + prices[i], forall i > k}
 */

class Solution {
  public:
    int maxProfit(vector<int> &prices) {
      int n = prices.size();
      if (n == 0) return 0;


      int max_profit = 0, // max_profit[n-1]
          memorization = max_profit + prices[n-1]; // max_profit[n-1] + prices[n-1]

      for (int i = n -2; i >= 0; i--) {
        // update max profit
        max_profit = std::max(max_profit,
            memorization - prices[i]);
        // update memorization
        memorization = std::max(memorization, max_profit + prices[i]);
      }
      return max_profit;
    }
};

int main(int argc, const char *argv[])
{

  Solution sol;
  vector<int> prices;
  cout << sol.maxProfit(prices) << endl;
  return 0;
}
