#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <string>
#include <iomanip>
#include <cmath>
#include <map>
#include <functional>
#include <climits>
#include <cstdio>
#include <cassert>

using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::cin;
using std::string;
using std::map;


#define PI 3.14159265359
#define N 100000

typedef long long int int64;

int n, m;
int64 a[N];
int64 b[N];
int64 a_acc[N];
int64 b_rev_acc[N];

// [p, r)
int searchMaxLess(int64 vec[], int64 v, int p, int r) {
  while (p+1 < r) {
    int mid = (p+r) >> 1;
    if (vec[mid] < v) {
      p = mid;
    } else if (vec[mid] >= v) {
      r = mid;
    }
  }
  return p;
}

int64 fa(int64 k) {
  int u = searchMaxLess(a, k, 0, n);
  int64 res = int64(u+1) * k - a_acc[u];
  return res;
}

// [p, r)
// vec in reverse order
int searchMinGreater(int64 vec[], int64 v, int p, int r){
  while (p+1 < r) {
    int mid = (p+r) >> 1;
    if (vec[mid] > v) {
      p = mid;
    } else if (vec[mid] <= v) {
      r = mid;
    }
  }
  return p;
}

int64 fb(int64 k) {
  int v = searchMinGreater(b, k, 0, m);
  int64 res = b_rev_acc[v] - int64(v+1) * k;
  return res;
}

int64 f(int64 k) {
  return fa(k) + fb(k);
}

int64 tenary_search(int64 p, int64 r) {
  // [p-r]
  while ( p + 3 <= r ) {
    int64 m1 = p + (r - p) / 3;
    int64 m2 = r - (r - p) / 3;
    int64 fm1 = f(m1);
    int64 fm2 = f(m2);
    if (fm1 < fm2) {
      r = m2;
    } else if (fm1 > fm2) {
      p = m1;
    } else {
      p = m1;
      r = m2-1; // we just select p
    }
  }
  int64 selected = p;
  int64 selected_v = f(selected);
  for (int64 i = p+1; i <= r; i++) {
    int64 fi = f(i);
    if (fi < selected_v) {
      selected = i;
      selected_v = fi;
    }
  }
  return selected_v;
}

int main(int argc, const char *argv[])
{
  //freopen("test.in", "r", stdin);
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    //scanf("%d", &a[i]);
  }
  for (int i = 0; i < m; i++) {
    cin >> b[i];
    //scanf("%d", &b[i]);
  }
  std::sort(a, a+n);
  std::sort(b, b+m, std::greater<int64>());
  if (a[0] >= b[0]) {
    cout << 0 << endl;
  } else {
    int64 acc = 0;
    for (int i = 0; i < n; i++) {
      acc += a[i];
      a_acc[i] = acc;
    }
    acc = 0;
    //for (int i=m-1; i>=0; i--) {
    for (int i = 0; i < m; i++) {
      acc += b[i];
      b_rev_acc[i] = acc;
    }
    cout << tenary_search(a[0], b[0]) << endl;
    //cout << p << " " << f(p) << endl;
  }
  return 0;
}
