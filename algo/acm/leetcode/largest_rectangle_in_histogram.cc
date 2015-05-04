#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
  public:
    int largestRectangleArea(vector<int> &height) {
      int area_of_largest_rect = 0;
      stack<int> partial_hist;
      int i = 0;
      int ans = 0;
      while (i < height.size()) {
        if (partial_hist.empty() || height[partial_hist.top()] <= height[i]) {
          partial_hist.push(i);
          i += 1;
        } else {
          int base_i = partial_hist.top(); // index basic histogram height
          partial_hist.pop();
          ans = std::max(
              ans,
              height[base_i] * (partial_hist.empty()?i:(i-partial_hist.top()-1))
              );
        }
      }
      while (!partial_hist.empty()) {
          int base_i = partial_hist.top();
          partial_hist.pop();
          ans = std::max(
              ans,
              height[base_i] * (partial_hist.empty()?i:(i-partial_hist.top()-1))
              );
      }
      return ans;
    }
};


int main() {
  vector<int> height {2,1,5,6,2,3};
  Solution sol;
  cout << sol.largestRectangleArea(height) << endl;
  return 0;
}
