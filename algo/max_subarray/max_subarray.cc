#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;

// The algorithms listed here is different when dealing with A with size 1.
// This is ok. If the problem claims that we should have at least on element,
// then we should include A[0] when size == 1;
// Else, if we allow sum(A[]) = 0, if A[0] < 0, the max sum should be 0.
struct Return {
  int left, right, sum;
};

void init_ret(Return &ret) {
  ret.left = 0;
  ret.right = -1;
  ret.sum = INT_MIN;
}

bool is_valid_ret(const Return &ret) {
  return ret.left <= ret.right;
}

void update_ret(Return &ret, int left, int right, int sum) {
  ret.left = left;
  ret.right = right;
  ret.sum = sum;
}

void print_ret(const Return &ret) {
  cout << ret.left << " " << ret.right << " " << ret.sum << endl;
}

// input should meet requirement:low<=mid<=high
void divide_conquer_include_mid(const vector<int> &A, int low, int mid,
                                int high, Return &ret) {
  if (low == high) {
    // 1 elem
    ret.left = low;
    ret.right = high;
    ret.sum = A[mid];
  } else if (low +1 == high) {
    // two elem. we must include mid, which equals to low
    if (A[high] < 0) {
      // don't include high
      ret.left = low;
      ret.right = low;
      ret.sum = A[low];
    } else {
      // include high
      ret.left = low;
      ret.right = high;
      ret.sum = A[low] + A[high];
    }
  } else {
    // at least three elements
    // loop invariant: get the subarray sum max of A[low-(mid-1)] and
    // A[(mid+1)-high]; i is the loop counter that points to the current
    // element, with initial value equals to mid-1. v includes A[i], v_hat not
    // includes A[i]. At the beginning of every loop,
    // sum(A[left_idx-(mid-1)]) = v_hat; sum(A[(i+1)-(mid-1)]) = v.
    // init: v = A[mid-1], v_hat = 0. i = mid-1. left_idx = mid. We assume
    // sum(A[]) = 0;
    // maintain: for current i.
    //    update_left_idx if v > v_hat
    //    v_hat = max(v_hat, v).// max of not include i+1 and include i+1.
    //    v = v + A[i].
    //    
    // Terminate: i = low-1. v = sum(A[low-(mid-1)]), v_hat =
    // A[left_idx-(mid-1)].  So we can get max(v, v_hat) as the left max subarry
    // sum.
    // The same goes for right.
    ret.sum = 0;
    // initial:
    int v = A[mid-1]; // include A[mid-1]
    int v_hat = 0; // not include A[mid-1], i.e, nothing to include
    int left_idx = mid;
    for(int i = mid-2; i >= low; i--) {
      if (v_hat > v) {
        v_hat = v_hat;
      } else {
        v_hat = v;
        left_idx = i + 1; // include i+1 but not include i
      }
      // Note this is different from the linear method. Since v has different
      // meaning. Here, v means sum starts from i, ends to mid-1.
      v = v + A[i]; // v include A[i]
    }
    if (v > v_hat) {
      // we should include low
      ret.left = low;
      ret.sum += v;
    } else {
      // not include low
      ret.left = left_idx;
      ret.sum += v_hat;
    }
    //cout << v << " " << v_hat << " " << left_idx << endl;
    v = A[mid+1]; // include A[mid+1]
    v_hat = 0; // not include A[mid+1]
    int right_idx = mid;
    for(int i = mid+2; i <= high; i++) {
      if (v_hat > v) {
        v_hat = v_hat;
      } else {
        v_hat = v;
        right_idx = i - 1; // include i-1 but not include i
      }
      v = v + A[i];
    }
    if (v > v_hat) {
      // we should include high
      ret.right = high;
      ret.sum += v;
    } else {
      ret.right = right_idx;
      ret.sum += v_hat;
    }
    //cout << v << " " << v_hat << " " << right_idx << endl;
    // we must included mid twice.
    ret.sum += A[mid];
  }
}

// assume low + 1 <= high
// Include both mid and mid+1
void divide_conquer_cross_mid(const vector<int> &A, int low, int mid, int high,
                              Return &ret) {
  int sum = 0;
  int left_sum = INT_MIN;
  int max_left;
  // include mid
  for(int i = mid; i >= low; i--) {
    sum += A[i];
    if (sum >= left_sum) {
      left_sum = sum;
      max_left = i;
    }
  }
  sum = 0;
  int right_sum = INT_MIN;
  int max_right;
  for(int i = mid+1; i <= high; i++) {
    sum += A[i];
    if (sum >= right_sum) {
      right_sum = sum;
      max_right = i;
    }
  }
  ret.left = max_left;
  ret.right = max_right;
  ret.sum = left_sum + right_sum;
}

void max_ret(const Return &ret1, Return &ret) {
  if (ret1.sum > ret.sum) {
    ret = ret1;
  }
}

void brute_force(const vector<int> &A, Return &ret) {
  init_ret(ret);
  for(int i = 0; i < A.size(); i++) {
    int sum = 0 ;
    for(int j = i; j < A.size(); j++) {
      sum += A[j];
      if (sum >= ret.sum) {
        update_ret(ret, i, j, sum);
      }
    }
  }
}

void divide_conquer_rec(const vector<int> &A, int low, int high, Return &ret) {
  init_ret(ret);
  if (low > high) {
    return;
  }
  /*else if (high-low+1 <= 10) {
    brute_force(A, ret);
  }*/
  else {
    int mid = (low+high) >> 1;
    Return ret1;
    // not include mid
    divide_conquer_rec(A, low, mid-1, ret1);
    Return ret2;
    // not include mid
    divide_conquer_rec(A, mid+1, high, ret2);
    Return ret3;
    divide_conquer_include_mid(A, low, mid, high, ret3);
    max_ret(ret1, ret);
    max_ret(ret2, ret);
    max_ret(ret3, ret);
    //print_ret(ret);
  }
}

void divide_conquer_mit_rec(const vector<int> &A, int low, int high,
                            Return &ret) {
  init_ret(ret);
  if (low > high) {
    return;
  } else if (low == high) {
    update_ret(ret, low, low, A[low]);
    return;
  } else {
    int mid = (low+high) >> 1;
    Return ret1;
    // may or may not include mid
    divide_conquer_mit_rec(A, low, mid, ret1);
    //print_ret(ret1);
    Return ret2;
    // may or may not include mid+1
    divide_conquer_mit_rec(A, mid+1, high, ret2);
    //print_ret(ret2);
    Return ret3;
    // include both mid and mit+1.
    divide_conquer_cross_mid(A, low, mid, high, ret3);
    //print_ret(ret3);
    max_ret(ret1, ret);
    max_ret(ret2, ret);
    max_ret(ret3, ret);
  }
}
void divide_conquer_mit(const vector<int> &A, Return &ret) {
  divide_conquer_mit_rec(A, 0, A.size() - 1, ret);
}

void divide_conquer(const vector<int> &A, Return &ret) {
  divide_conquer_rec(A, 0, A.size() - 1, ret);
}


// fastest
void linear(const vector<int> &A, Return &ret) {
  init_ret(ret);
  if (A.size() == 0) {
    return;
  } else {
    Return v;
    init_ret(v);
    // It's also ok if we change initial value of v.sum and v_hat.sum to zero.
    // In this case, we allow that no element is chosed. But this case will not
    // work for the problem of the book introduction to algorithm, in which
    // case, at least one element should be included.
    //v.sum = 0;
    Return v_hat;
    init_ret(v_hat);
    //v_hat.sum = 0;
    for(int i = 0; i < A.size(); i++) {
      if (v_hat.sum < v.sum) {
        v_hat = v;
      }
      if (v.sum <= 0) {
        v.sum = A[i];
        v.left = i;
        v.right = i;
      } else {
        v.sum = v.sum + A[i];
        v.right = i;
      }
    }
    if (v.sum > v_hat.sum) {
      ret = v;
    } else {
      ret = v_hat;
    }
  } 
}



int c_A [] = {13, -3, -25, 20, -3, -16, -23, 18, 20,-7,12,-5,-22,15,-4,7};
int n = 16;
int c_A1[] = {-2, -3, -1, -4, -5};
int n1 = 5;
int c_A2[] = {18, 20, -7, 12};
int n2 = 4;
int c_A3[] = {-2, -1, -4};
int n3 = 3;
void test_brute_force() {
  vector<int> A(c_A, c_A + n);
  Return ret;
  brute_force(A, ret);
  print_ret(ret);
  vector<int> A1(c_A1, c_A1 + n1);
  brute_force(A1, ret);
  print_ret(ret);
}

void test_divide_conquer() {
  vector<int> A(c_A, c_A + n);
  //vector<int> A(c_A3, c_A3 + n3);
  Return ret;
  divide_conquer(A, ret);
  print_ret(ret);
  vector<int> A1(c_A1, c_A1 + n1);
  divide_conquer(A1, ret);
  print_ret(ret);
}

void test_divide_conquer_mit() {
  vector<int> A(c_A, c_A + n);
  Return ret;
  divide_conquer_mit(A, ret);
  print_ret(ret);
  vector<int> A1(c_A1, c_A1 + n1);
  divide_conquer_mit(A1, ret);
  print_ret(ret);
}

void test_linear() {
  vector<int> A(c_A, c_A + n);
  Return ret;
  linear(A, ret);
  print_ret(ret);
  vector<int> A1(c_A1, c_A1 + n1);
  linear(A1, ret);
  print_ret(ret);
}

#include <chrono>

using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::steady_clock;

void test_perf(void(*f)(const vector<int> &, Return &),
               const vector<int> &A,
               Return &ret) {
  steady_clock::time_point start = steady_clock::now();
  const int times = 100000;
  for(int i = 1; i <= times; i++) {
    f(A, ret);
  }
  steady_clock::time_point end = steady_clock::now();
  cout << "took " << duration_cast<microseconds>(end - start).count()
      << "us.\n";
}

#include <random>
#include <fstream>
using std::ifstream;
using std::cerr;

void test_performance() {
  int n = 10;
  vector<int> A(n, 0);
  ifstream ifs("test.dat");
  for(int i = 0; i < n; i++) {
    ifs >> A[i];
    if (ifs.eof()) {
      cerr << "input data is not enough" << endl;
    }
  }
  Return ret;
  test_perf(divide_conquer, A, ret);
}

int main(int argc, const char *argv[])
{
  //test_brute_force();
  //test_divide_conquer();
  //test_divide_conquer_mit();
  /*vector<int> A(c_A3, c_A3 + n3);
  Return ret;
  divide_conquer_include_mid(A, 0, 1, 2, ret);
  print_ret(ret);*/
  //test_performance();
  test_linear();
  return 0;
}
