#include <vector>
#include <iostream>
using namespace std;

// Method 1: O(n*n*lgn)
// Time limit exceeded
class Solution1 {
public:
    int threeSumClosest(vector<int> &num, int target) {
        std::sort(num.begin(), num.end());
        
        int closest_sum = 0;
        int min_dis = INT_MAX;
        for (int i = 0; i < num.size()-2; i++) {
            for (int j = i + 1; j < num.size()-1; j++) {
                // first try target-num[i]-num[j]
                {
                    int k = binSearch(num, j+1, num.size()-1, target - num[i] - num[j]);
                    int sum = num[i] + num[j] + num[k];
                    if (std::abs(target-sum) < min_dis) {
                        min_dis = std::abs(target-sum);
                        closest_sum = sum;
                    }
                }
                // second try num[i]+num[j]-target
                {
                    int k = binSearch(num, j+1, num.size()-1, num[i]+num[j]-target);
                    int sum = num[i] + num[j] + num[k];
                    if (std::abs(target-sum) < min_dis) {
                        min_dis = std::abs(target-sum);
                        closest_sum = sum;
                    }
                }
                if (min_dis == 0) return closest_sum;
            }
        }
        return closest_sum;
    }
    
    // search in [p,r] for the closest value to v
    int binSearch(const vector<int> &num, int p, int r, int v) {
        
        // find the largest value that's <= v
        int mark = -1;
        while (p <= r) {
            int m = (p+r)/2;
            if (num[m] > v) {
                r = m - 1;
            } else if (num[m] < v) {
                p = m + 1;
                mark = m;
            } else {
                return m;
            }
        }
        if (mark == -1) {
            // num[p,r] > v
            
            return p;
        } else if (mark == r) {
            // num[p,r] < v
            return mark;
        } else {
            // num[mark] < v
            // num[mark+1] > v
            // return the one that's closest to v
            
            if (std::abs(num[mark] - v) < std::abs(num[mark+1] - v)) {
                return mark;
            } else {
                return mark + 1;
            }
        }
    }
};

// Method 2: O(n*n);
class Solution {
  public:
    int threeSumClosest(vector<int> &num, int target) {
      typedef vector<int>::const_iterator Iter;
      Iter pa,pb,pc;
      int min_diff = INT_MAX;
      int closest_sum = 0;
      std::sort(num.begin(), num.end());
      for (pa = num.begin(); pa < num.end()-2; pa++) {
        // binary search
        // Suppose range is [p,r]
        // Apparently, num[p]+num[p] <= sum <= num[r]+num[r]
        // So start with some middle value: num[p] + num[r],
        // then change the range dynamically.
        for (pb = pa+1, pc = num.end()-1; pb < pc; ) {
          int sum = *pa + *pb + *pc;
          int cur_diff = std::abs(target - sum);
          if (cur_diff < min_diff) {
            min_diff = cur_diff;
            closest_sum = sum;
          }
          if (min_diff == 0) return closest_sum;

          if (sum < target) {
            pb++;
          } else if (sum > target) {
            pc--;
          } else {
            // impossible to happend
            // TODO: fail with error
          }
        }
      }
      return closest_sum;
    }
};


int main() {
  Solution sol;
  vector<int> num = {-1,2,1,-4};
  cout << sol.threeSumClosest(num, 1) << endl;
  return 0;
}
