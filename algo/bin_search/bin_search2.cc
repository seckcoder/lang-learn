#include <iostream>
#include <cassert>
using namespace std;


// bin search range. 
// return number of val in A
int binsearch(int A[], int size, int val) {
  assert(size>=1);
  int p = 0, q = size-1;
  int lower = -1;
  // loop invariant: p <= q, and val in A[p-q]
  while (true) {
    if (p > q) {
      // can't find
      return 0;
    } else if (p == q && A[p] == val) {
      // only 1
      lower = p;
      break;
    } else if (p == q) {
      // can't find
      return 0;
    } else {
      int mid = (p+q) >> 1;
      if (A[mid] == val) {
        q = mid;
      } else if (A[mid] < val) {
        p = mid + 1;
      } else {
        q = mid - 1;
      }
    }
  }

  int higher = size;
  p = 0;
  q = size - 1;
  while (true) {
    if (p > q) {
      // can't find
      return 0;
    } else if (p == q && A[p] == val) {
      // only 1
      higher = p;
      break;
    } else if (p == q) {
      // can't find
      return 0;
    } else if (p + 1 == q) {
      if (A[q] == val) {
        higher = q;
        break;
      } else if (A[p] == val) {
        higher = p;
        break;
      } else {
        return 0;
      }
    } else {
      int mid = (p+q) >> 1;
      if (A[mid] == val) {
        p = mid; // we need to check p+1==q
      } else if (A[mid] < val) {
        p = mid + 1;
      } else {
        q = mid - 1;
      }
    }
  }
  //cout << lower << " " << higher << endl;
  return higher - lower + 1;
}

int main() {
  int A[] = {1, 2, 2, 2, 3, 4, 4, 5, 6, 6};
  cout << binsearch(A, 10, 0) << endl;
  cout << binsearch(A, 10, 1) << endl;
  cout << binsearch(A, 10, 2) << endl;
  cout << binsearch(A, 10, 6) << endl;
  cout << binsearch(A, 10, 7) << endl;
  return 0;
}
