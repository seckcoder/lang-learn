#include <iostream>
#include <vector>


using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
      if (prices.size() == 0) return 0;
      int cur_max_after = prices[prices.size()-1];
      int max_profits = 0;
      for (int i = prices.size() - 1; i >= 0; i--) {
        max_profits = std::max(max_profits,
                               cur_max_after - prices[i]);
        cur_max_after = std::max(cur_max_after, prices[i]);
      }
      return max_profits;
    }
};

int main(int argc, const char *argv[])
{
  Solution sol;
  return 0;
}
