#include <iostream>
using namespace std;

int bin_search1(int A[], int p, int r, int val) {
  p -= 1;
  r += 1;
  int mark = r;
  while (p + 1 < r) {
    int mid = (p+r)>>1;
    if (A[mid] < val) p = mid;
    else if (A[mid] > val) r = mid;
    else {
      mark = mid;
      r = mid;
    }
  }
  return mark;
}

int bin_search2(int A[], int p, int r, int val) {
  p -= 1;
  r += 1;
  int mark = r;
  while (p + 1 < r) {
    int mid = (p+r) >> 1;
    if (A[mid] < val) p = mid;
    else if (A[mid] > val) r = mid;
    else {
      p = mid;
      mark = mid;
    }
  }
  return mark;
}

int n;
int val;
int *a;
void input() {
  freopen("test.in", "r", stdin);
  scanf("%d %d", &n, &val);
  a = new int[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
}

int main() {
  input();
  cout << bin_search1(a, 0, n-1, val) << endl;
  cout << bin_search2(a, 0, n-1, val) << endl;
  delete [] a;
  return 0;
}
