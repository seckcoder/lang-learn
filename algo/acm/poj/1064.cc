//#define SECK_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <cstdlib>
#include <list>
#include <numeric>
#include <ctime>
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
using std::cerr;
using std::ostream;
using std::istream;

#define PI 3.14159265359
#define IS_ODD(v) ((v) & 1)
//#define IS_EVEN(v) (((v) - (((v) >> 1) << 1)) == 0)
typedef long long int int64;
typedef unsigned char uint8;

ostream &operator<<(ostream &os, const uint8 v) {
  os << (int)v;
  return os;
}

istream &operator>>(istream &is, uint8 &v) {
  int tmp;
  is >> tmp;
  v = (uint8)tmp;
  return is;
}

#define N 10000
#define MAX_LEN 10000001
#define MAX_PIECES 10000
int a[N];
int n, k;
int countPieces(int len) {
  int ans = 0;
  for (int i = 0; i < n && ans <= MAX_PIECES; i++) {
    ans += a[i]/len;
  }
  return ans;
}

int solve(int p, int r) {
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; i++) {
    double l;
    scanf("%lf", &l);
    a[i] = l * 100;
  }
  int cnt = r - p;
  int mark = 0;
  while (cnt > 0) {
    int i = p;
    int step = cnt>>1;
    i += step;
    int pieces = countPieces(i);
    //cout << i << " " << pieces << endl;
    if (pieces >= k) {
      // increase i
      mark = i;
      p = i + 1;
      cnt -= step + 1;
    } else {
      // decrease i
      cnt = step;
    }
  }
  return mark;
}

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  printf("%.2lf\n", double(solve(1, MAX_LEN))/100.0);

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
