#include <vector>
using namespace std;

class Solution1 {
public:
    void calcMaxProfitInOneTrans(const vector<int> &prices,
            int *max_profit_in_trans,
            int *max_profit_if_sell_after) {
        int n = prices.size(); // n > 0 for sure
        max_profit_in_trans[n-1] = 0;
        max_profit_if_sell_after[n-1] = prices[n-1];
        for (int i = n-2; i >= 0; i--) {
            max_profit_in_trans[i] = std::max(
                max_profit_in_trans[i+1], // not buy at i
                max_profit_if_sell_after[i+1] - prices[i] // if buy at i
                );
            max_profit_if_sell_after[i] = max(
                max_profit_if_sell_after[i+1], // if not sell at i
                prices[i] // if sell at i. Since we have only one transaction, so it's the current price.
                );
        }
    }
    int maxProfit(int k, vector<int> &prices) {
        int n = prices.size();
        if (n == 0 || k == 0) return 0;
        
        int *max_profit_in_trans[2];
        int *max_profit_if_sell_after[2];
        max_profit_in_trans[0] = new int[n];
        max_profit_in_trans[1] = new int[n];
        max_profit_if_sell_after[0] = new int[n];
        max_profit_if_sell_after[1] = new int[n];
        
        calcMaxProfitInOneTrans(prices, max_profit_in_trans[0], max_profit_if_sell_after[0]);
        
        int max_profit = max_profit_in_trans[0][n-1]; // initialize with only 1 trans
        
        for (int trans = 1; trans < k; trans++) {
            int cur_trans = trans % 2,
                prev_trans = (trans-1) % 2;
            max_profit_in_trans[cur_trans][n-1] = 0;
            
            for (int i = n-2; i>=0; i--) {
                max_profit_in_trans[cur_trans][i] = std::max(
                    max_profit_in_trans[cur_trans][i+1], // if not buy at i
                    max_profit_if_sell_after[prev_trans][i] - prices[i] // if buy at i
                    );
                max_profit_if_sell_after[cur_trans][i] = std::max(
                    max_profit_if_sell_after[cur_trans][i+1], // if not sell at i
                    max_profit_in_trans[prev_trans][i] + prices[i] // if sell at i
                    );
            }
            
            max_profit = std::max(max_profit, max_profit_in_trans[cur_trans][n-1]);
        }
        
        delete [] max_profit_in_trans[0];
        delete [] max_profit_in_trans[1];
        delete [] max_profit_if_sell_after[0];
        delete [] max_profit_if_sell_after[1];
        return max_profit;
    }
};
