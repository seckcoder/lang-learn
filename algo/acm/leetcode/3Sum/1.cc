#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        vector<vector<int> > ans;
        if (num.size() <= 2) return ans;
        std::sort(num.begin(), num.end());
        
        typedef vector<int>::iterator Iter;
        int prev = 1;
        // a <= 0
        for (Iter a = num.begin(); a < num.end()-2 && (*a) <= 0; a++) {
            // makes sure no duplicates in outer loop
            if (*a == prev) continue; // avoid duplicates
            prev = *a;
            for (Iter b = a+1, c = num.end()-1; b < c && (*c) >= 0;) {
                int sum = (*a) + (*b) + (*c);
                if (sum == 0) {
                    // find one
                    addOneAns(ans, *a, *b, *c);
                    b++;
                    c--;
                } else if (sum > 0) {
                    c--;
                } else {
                    b++;
                }
            }
        }
        
        return ans;
    }
    void addOneAns(vector<vector<int> > &ans, int a, int b, int c) {
        if (ans.empty()) {
            ans.push_back({a,b,c});
        } else {
            vector<int> &last = ans.back();
            // avoid duplicates
            // Following code makes sure no duplicates when in inner loop
            if (last[0] == a && last[1] == b && last[2] == c) {
                return;
            } else {
                ans.push_back({a,b,c});
            }
        }
    }
};



int main() {
  Solution sol;
  vector<int> vec = {-2,-2,-2,0,2,2,2, 4,4};
  vector<vector<int> > ans = sol.threeSum(vec);
  for (int i = 0; i < ans.size(); i++) {
    for (int j = 0; j < ans[i].size(); j++) {
      cout << ans[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}
