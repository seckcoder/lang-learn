#include <vector>
using namespace std;


/*
 * max_profit[ONE_TRAN][k] : max profit in one transaction for prices in [k...]
 * max_profit[TWO_TRAN][k] : max profit in two transactions for prices in [k...]
 *
 * max_profit[ONE_TRAN][k] = max(
 *    max_profit[ONE_TRAN][k+1], // not buy
 *    max_price - prices[k]); // buy
 *
 * max_profit[TWO_TRAN][k] = max(
 *    max_profits[TWO_TRAN][k+1],  // not buy
 *    max(max_profit[ONE_TRAN][i] + prices[i] - prices[k], for all i > k) // buy at k and sell at i
 *    );
 *
 * optimization:
 *  
 *    memorize max(max_profit[ONE_TRAN][i] + prices[i], forall i > k) as memorization
 */
class Solution {
public:
    int maxProfit(vector<int> &prices) {
      if (prices.size() == 0) return 0;

      #define TWO_TRAN 1
      #define ONE_TRAN 0
      int n = prices.size();

      int max_profit[2] = {0};

      int max_price = prices[n-1];
      int memorization = max_profit[ONE_TRAN] + prices[n-1];

      for (int i = n-2; i>=0; i--) {
        max_profit[ONE_TRAN] = std::max(
            max_profit[ONE_TRAN], // not buy
            max_price - prices[i]);

        max_profit[TWO_TRAN] = std::max(
            max_profit[TWO_TRAN],
            memorization - prices[i]);

        max_price = std::max(max_price, prices[i]);
        memorization = std::max(memorization, max_profit[ONE_TRAN] + prices[i]);
      }

      return std::max(max_profit[ONE_TRAN], max_profit[TWO_TRAN]);
    }
};


int main(int argc, const char *argv[])
{
  
  return 0;
}
