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

int64 ha(int64 v) {
  int64 res = 0;
  for (int i = 0; i < n && a[i] < v; i++) {
    res += v - a[i];
  }
  return res;
}

int64 hb(int64 v) {
  int64 res = 0;
  for (int i = 0; i < m && b[i] > v; i++) {
    res += b[i] - v;
  }
  return res;
}

int64 h(int64 k) {
  return ha(k) + hb(k);
}

int64 tenary_search(int64 p, int64 r) {
  while ( p + 3 <= r ) {
    int64 m1 = p + (r - p) / 3;
    int64 m2 = r - (r - p) / 3;
    int64 hm1 = h(m1);
    int64 hm2 = h(m2);
    if (hm1 < hm2) {
      r = m2;
    } else if (hm1 > hm2) {
      p = m1;
    } else {
      p = m1;
      r = m2 - 1;
    }
  }
  int64 selected = p;
  int64 selected_v = h(selected);
  for (int64 i = p+1; i<=r; i++) {
    int64 hi = h(i);
    if (hi < selected_v) {
      selected = i;
      selected_v = hi;
    }
  }
  return selected;
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
    int64 p = tenary_search(a[0], b[0]);
    cout << h(p) << endl;
    //cout << p << " " << h(p) << endl;
  }
  return 0;
}
