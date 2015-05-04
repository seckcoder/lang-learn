#include <vector>
#include <stack>
#include <list>
using namespace std;


class Solution {
  public:
    int maximalRectangle(vector<vector<char> > &matrix) {
      if (matrix.size() == 0) return 0;
      if (matrix[0].size() == 0) return 0;
      int m = matrix.size(),
          n = matrix[0].size();
      vector<int> hist(n+2, 0);
      hist.front() = -1;
      hist.back() = -1;
      for (int i = 0; i < n; i++) {
        if (matrix[0][i] == '1') {
          hist[i+1] += 1;
        }
      }
      int max_area = maxHistArea(hist);
      for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
          if (matrix[i][j] == '1') {
            hist[j+1] += 1;
          } else {
            hist[j+1] = 0;
          }
        }
        max_area = std::max(maxHistArea(hist), max_area);
      }
      return max_area;
    }
    // assume hist[0] < hist[1..] > hist[-1]
    int maxHistArea(const vector<int> &hist) {
      stack<int> partial_hist;
      partial_hist.push(0); // 0 is the smallest element
      int max_area = 0;
      for (int i = 1; i < hist.size(); ) {
        int m = partial_hist.top(); // we can be sure that currently partial_hist is not empty. Since hist[1..] >= hist[0], so 0 is always in the stack
        if (hist[m] <= hist[i]) {
          partial_hist.push(i);
          i += 1;
        } else {
          partial_hist.pop();
          int l = partial_hist.top(); // hist[m] > hist[i], this means m != 0. So partial_hist contains at least one element at this time.
          max_area = std::max(max_area, (i-l-1)*hist[m]);
        }
      }
      // after the loop, partial_hist only contains two elements, 0 and (hist.size()-1)
      return max_area;
    }
};
