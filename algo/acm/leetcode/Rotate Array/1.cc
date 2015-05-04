
template <class BidirectionalIterator>
void reverse(BidirectionalIterator begin,
    BidirectionalIterator end) {
  while (begin != end && (begin != --end)) {
    int tmp = *begin;
    *begin = *end;
    *end = tmp;
    ++begin;
  }
}

class Solution {
public:
    void rotate(int nums[], int n, int k) {
        k = k % n;
        int cutoff = n-k;
        reverse(nums, nums+cutoff);
        reverse(nums+cutoff, nums+n);
        reverse(nums, nums+n);
    }
};

#include<iostream>
using namespace std;

int main() {
  int nums[] = {1,2};
  int n = 2;
  Solution().rotate(nums, n, 0);
  for (int i = 0; i < n; i++) {
    cout << nums[i] << " ";
  }
  cout << endl;
  return 0;
}
