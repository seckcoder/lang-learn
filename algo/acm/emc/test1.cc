#include <vector>

#include <limits>
#include <cassert>

using std::vector;

bool is_mag_poll(const vector<int> &biggest,
                 const vector<int> &smallest_rev,
                 const vector<int> &A,
                 int i) {
  if (i == 0 && A.size() == 1) {
    return true;
  } else {
    assert(A.size() > 1);
    if (i == 0) {
      return A[i] <= smallest_rev[i+1];
    } else if (i == A.size() - 1) {
      // A.size() > 1
      return A[i] >= biggest[i-1];
    } else {
      return (A[i] <= smallest_rev[i+1]) && (A[i] >= biggest[i-1]);
    }
  }
}


// you can also use includes, for example:
// #include <algorithm>
int solution(const vector<int> &A) {
  if (A.size() == 0) {
    return -1;
  }
  vector<int> biggest(A.size());
  vector<int> smallest_rev(A.size());
  int tmp = std::numeric_limits<int>::min();
  for(int i = 0; i < A.size(); i++) {
    if (A[i] >= tmp) {
      biggest[i] = A[i];
      tmp = A[i];
    } else {
      biggest[i] = tmp;
    }
  }
  tmp = std::numeric_limits<int>::max();
  for(int i = A.size() - 1; i >= 0; i--) {
    if (A[i] <= tmp) {
      smallest_rev[i] = A[i];
      tmp = A[i];
    } else {
      smallest_rev[i] = tmp;
    }
  }
  for(int i = 0; i < A.size(); i++) {
    if (is_mag_poll(biggest, smallest_rev, A, i)) {
      return i;
    }
  }
  return -1;
}


int main(int argc, const char *argv[]) {
  int tmp[1] = {2};
  vector<int> A(tmp, tmp + 1);
  solution(A);
}
