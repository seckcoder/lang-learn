#include <iostream>
#include <cassert>
using namespace std;


// Simple bin search, search val in A
// A:0-(size-1)
int binsearch(int A[], int size, int val) {
  assert(size>=1);
  int p = 0, q = size-1;
  // loop invariant: p <= q and val in A[p-q]
  while (true) {
    if (p > q) {
      // can't find
      return -1;
    } else {
      int mid = (p+q)>>1;
      if (A[mid] == val) {
        return mid;
      } else if (A[mid] < val) {
        p = mid + 1;
      } else {
        q = mid - 1;
      }
    }
  }
}


int main(int argc, const char *argv[])
{
  int A[] = {2,2,4,5};
  cout << binsearch(A, 4, 1) << endl;
  cout << binsearch(A, 4, 2) << endl;
  cout << binsearch(A, 4, 5) << endl;
  cout << binsearch(A, 4, 6) << endl;
  return 0;
}
