#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    // may contain duplicates.
    // Note although the input may contain duplicates, the array
    // is still a rotated array
    int findMin(vector<int> &num) {

      int p = 0, r = num.size()-1, mark = -1, n = num.size();

      while (p <= r) {
        int m = (p+r) / 2;
        if (num[m] < num[n-1]) {
          // right
          mark = m;
          r = m-1;
        } else if (num[m] > num[n-1]) {
          // left
          p = m+1;
        } else {
          // When do we need to deal with duplicates?
          // - When we really find duplicates.
          //
          // Before entering the block, we shrink the range rigorously, i.e., :
          // - if num[m] < num[n-1], then surely, minimum value is in range[p,m-1] if num[m] is not the min value
          // - if num[m] > num[n-1], then surely, minimum value is in range[m+1,r] if num[m] is not the min value.
          // 
          // If we never enter this block of code, then it's possible that
          // the duplicates have no effect in finding the minimum value.
          //
          // If we do enter the block, then the min value surely is in [p,r] or is num[mark].
          if (mark == -1) {
            return *std::min_element(num.begin()+p, num.begin()+r+1);
          } else {
            return std::min(num[mark],
                *std::min_element(num.begin()+p, num.begin()+r+1));
          }
        }
      }
      if (mark == -1) {
        return num.back();
      } else {
        return num[mark];
      }
    }
};


int main() {
  Solution sol;
  vector<int> num = {10,10,1,10,10};
  cout << sol.findMin(num) << endl;
  return 0;
}
