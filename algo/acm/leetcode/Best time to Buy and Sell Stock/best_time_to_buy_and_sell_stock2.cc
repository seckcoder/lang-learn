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


class Solution2 {
  public:
    int maxProfit(vector<int> &prices) {
      int n = prices.size();
      if (n == 0) return 0;

      int max_profit_after = 0,
          max_profit_if_sell_now = prices[n-1];

      for (int i = n-2; i>=0; i--) {
        int max_profit_if_buy_now = max_profit_if_sell_now - prices[i];
        if (max_profit_if_buy_now > max_profit_after) max_profit_after = max_profit_if_buy_now;

        if (prices[i] + max_profit_after > max_profit_if_sell_now) max_profit_if_sell_now = prices[i] + max_profit_after;
      }
      return max_profit_after;
    }
};

int main(int argc, const char *argv[])
{

  Solution sol;
  vector<int> prices;
  cout << sol.maxProfit(prices) << endl;
  return 0;
}
