
/*
 *
 * Problem description:
 *
 *  Assume an array of size (n+1), and elements in the array are in range [1..n].
 *  Return the duplicate value.
 *
 * From Mohan Yang.
 *
 */

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;



int findDuplicate(const vector<int> &vec, int p, int r) {
  if (p == r) return vec[p];
  int m = p+(r-p)/2;
  int bucket_left = 0,
      bucket_right = 0;
  for (auto v: vec) {
    if (v <= m) bucket_left++;
    else bucket_right++;
  }

  if (bucket_left >= m-p+1) return findDuplicate(vec, p,m);
  else return findDuplicate(vec, m+1, r);
}

int main() {
  cout << findDuplicate({1,2,2,3}, 1, 3) << endl;
  return 0;
}
