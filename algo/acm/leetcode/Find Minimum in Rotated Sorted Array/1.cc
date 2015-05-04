#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    // compare the element with the last element
    // Note we compare it with the last instead of the first element.
    // Since when comparing with the last element, if we are rotating
    // at the end/begining, the mark will never be changed.
    int findMin(vector<int> &num) {
        int n = num.size();
        int p = 0, r = num.size()-1, mark = -1;
        while (p <= r) {
            int m = (p+r)/2;
            if (num[m] < num[n-1]) {
                mark = m;
                r = m - 1;
            } else {
                p = m + 1;
            }
        }
        if (mark == -1) {
          // This is possible when we are rotating the array
          // in the end/beginning. As a result, the array
          // is sorted decreasingly. For this case, mark
          // is never updated. 
          return num.back();
        }
        return num[mark];
    }
};

int main() {
  Solution sol;
  vector<int> num = {2,1};
  cout << sol.findMin(num) << endl;
  return 0;
}
