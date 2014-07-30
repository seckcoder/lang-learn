#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

template <class Function>
void test(const char *fname, Function test_f) {
  freopen(fname, "r", stdin);
  int n;
  scanf("%d", &n);
  int *a = new int[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  test_f(a, n);
  delete [] a;
}

int binSearch(int A[], int first, int last, int val) {
  int p = first, r = last-1;
  while (p <= r) {    
    int mid = (p+r)>>1;
    if (A[mid] < val) p = mid + 1;
    else if (A[mid] > val) r = mid - 1;
    else {
      return mid;
    }
  }
  return last;
}

// smallest index i such that A[i] = val, return last if not exist
int binSearch1(int A[], int first, int last, int val) { 
  int p = first, r = last-1, mark = last;
  // first, last值在之后保持不变

  // 初始时, r = last-1, p = first, 因此i只能取值为last, 循环不变式成立。
  while (p <= r) {
    int mid = (p+r) >> 1;
    if (A[mid] < val) {
      // A[p, mid] < val
      p = mid + 1;
    } else if (A[mid] > val) {
      // A[mid, last) > val。因此循环不变式依然成立。且知，此时一定有mark = last。
      r = mid - 1;
    } else {
      // A[mid] = val. 由于mark>r, 而mid<r, 因此我们可以更新mark。
      mark = mid;
      r = mid - 1;
    }
  }
  // 循环结束后，p > r, [p, r]为空，因此mark = min{i | first<=i<=last且A[i] = val}
  return mark;
}

// largest index i such that A[i] = val, return last if not exist
int binSearch2(int A[], int first, int last, int val) {
  int p = first, r = last-1, mark = last;
  while (p <= r) {
    int mid = (p+r) >> 1;
    if (A[mid] < val) {
      p = mid + 1;
    } else if (A[mid] > val) {
      r = mid - 1;
    } else {
      mark = mid;
      p = mid + 1;
    }
  }
  return mark;
}

// smallest index i such that A[i] >= val. return last if A[] < val
int binSearch3(int A[], int first, int last, int val) {
  int p = first, r = last-1, mark = last;
  while (p <= r) {
    int mid = (p+r) >> 1;
    if (A[mid] >= val) {
      mark = mid;
      r = mid - 1;
    } else {
      p = mid + 1;
    }
  }
  return mark;
}

// smallest index i such that A[i] > val. return last if A[] <= val
int binSearch4(int A[], int first , int last, int val)  {
  int p = first, r = last-1, mark = last;
  while (p <= r) {
    int mid = (p+r)>>1;
    if (A[mid] > val) {
      mark = mid;
      r = mid - 1;
    } else {
      p = mid + 1;
    }
  }
  return mark;
}


#define declare_test(name) \
    void test_ ## name(int *a, int n) { \
      int v, i;\
      while (scanf("%d %d", &v, &i) != EOF) { \
        if (name(a, 0, n, v) != i) { \
          cout << #name << " failed with (" << v << " " << i << ")"<< endl; \
        } \
      } \
    }

declare_test(binSearch);
declare_test(binSearch1);
declare_test(binSearch2);
declare_test(binSearch3);
declare_test(binSearch4);


int main(int argc, const char *argv[])
{
  test("test.in", test_binSearch);
  test("test1.in", test_binSearch1);
  test("test2.in", test_binSearch2);
  test("test3.in", test_binSearch3);
  test("test4.in", test_binSearch4);
  return 0;
}
