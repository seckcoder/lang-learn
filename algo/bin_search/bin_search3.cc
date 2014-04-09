#include <iostream>
#include <cassert>

using namespace std;


void err_sys(const char *msg) {
  cout << msg << endl;
  //cout << "something wrong with the format of vector A" << endl;
  //exit(-1);
}

// B is a sorted(assending, no equal element) list.
// truncate B into two parts at some position, and reverse append the two sub
// vector into A. That's the definition of A
// binsearch is used to find the truncated position
int binsearch(int A[], int size) {
  assert(size>=2);
  int p = 0, q = size-1;
  // loop invariant: p + 1 <= q, truncated position in p-q.

  const char *format_msg = "something wrong with the format of vector A";
  while (true) {
    if (p+1 > q) {
      err_sys(format_msg);
      return -1;
    } else if (p+1 == q) {
      if (A[p] > A[q]) {
        return p;
      } else {
        err_sys(format_msg);
        return -1;
      }
    } else {
      int mid = (p+q) >> 1;
      if (A[mid] > A[0]) {
        p = mid; // check p+1 == q
      } else if (A[mid] < A[0]) {
        q = mid;
      } else {
        err_sys(format_msg);
        return -1;
      }
    }
  }
}


int main() {
  int A[] = {6,7,3,4,5};
  cout << binsearch(A, 5) << endl;
  int B[] = {1,2,3,4,5};
  cout << binsearch(B, 5) << endl;
  return 0;
}
