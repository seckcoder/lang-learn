#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


class Bucket {
  public:
    int maxv, minv;
    Bucket() {
      maxv = -1;
      minv = INT_MAX;
    }
    bool empty() {
      return maxv < minv;
    }
    void add(int v) {
      maxv = std::max(v, maxv);
      minv = std::min(v, minv);
    }
};

class Solution {
public:
    int maximumGap(vector<int> &num) {
      int n = num.size();
      if (n <= 1) return 0;
      vector<Bucket> buckets(n); // n buckets
      int minv = *std::min_element(num.begin(), num.end());
      int maxv = *std::max_element(num.begin(), num.end());
      if (maxv == minv) return 0;
      buckets[n-1].add(maxv);
      float d =  float(n-1) / float(maxv - minv);
      for (int i = 0; i < n; i++) {
        if (num[i] != maxv) {
          int bucket_idx = std::floor((num[i] - minv) * d);
          buckets[bucket_idx].add(num[i]);
        }
      }
      int ans = 0;
      for (int i = 0; i < n;) {
        int start_value = buckets[i].maxv;
        int j = i+1;
        while (j < n && buckets[j].empty()) {
          j += 1;
        }
        if (j < n) {
          int end_value = buckets[j].minv;
          ans = std::max(ans, end_value - start_value);
        }
        i = j;
      }
      return ans;
    }
};


int main() {
  Solution sol;
  vector<int> num {100,3,2,1};
  cout << sol.maximumGap(num) << endl;;
}
