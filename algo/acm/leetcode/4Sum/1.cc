
#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    vector<vector<int> > fourSum(vector<int> &num, int target) {
      std::sort(num.begin(), num.end());
      vector<vector<int> > quads;
      int n = num.size();
      if (n == 0) return quads;
      int prev_a = num[0] - 1;
      for (int a = 0; a < n; a++) {
        if (num[a] == prev_a) {
          continue;
        }
        prev_a = num[a];
        int prev_b = num[0] - 1;
        for (int b = a+1; b < n; b++) {
          if (num[b] == prev_b) {
            continue;
          }
          prev_b = num[b];
          twoSum(num, b+1, target - num[a] - num[b],
              num[a], num[b],
              quads);
        }
      }
      return quads;
    }
    void twoSum(vector<int> &num, int start_idx, int target,
        int a, int b, vector<vector<int> > &quads) {
      int n = num.size();
      int p = start_idx, r = n-1;
      while (p < r) {
        int cur_sum_v = num[p] + num[r];
        if (cur_sum_v == target) {
          addOneQuad(a,b,num[p],num[r], quads);
          p += 1;
          r -= 1;
        } else if (cur_sum_v < target) {
          p += 1;
        } else {
          r -= 1;
        }
      }
    }
    void addOneQuad(int a, int b, int c, int d, vector<vector<int> > &quads) {
      if (quads.empty()) {
        quads.push_back({a,b,c,d});
      } else {
        vector<int> top = quads.back();
        if (!(top[0] == a && top[1] == b && top[2] == c && top[3] == d)) {
          quads.push_back({a,b,c,d});
        }
      }
    }
};

int main() {
 // vector<int> num = {1,0,-1,0,-2,2};
 //[-7,-5,0,7,1,1,-10,-2,7,7,-2,-6,0,-10,-5,7,-8,5]
  vector<int> num = {5,7,7,7,7};
  auto ans = Solution().fourSum(num, 28);
  for (int i = 0; i < ans.size(); i++) {
    for (int j = 0; j < ans[i].size(); j++) {
      cout << ans[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}
