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

#define N 100
#define BASE 10000
#define M (BASE<<1)+1

uint8 idx[M];
int x[N];
int d[N];

bool solve() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d %d", &x[i], &d[i]);
    idx[x[i]+BASE] = i+1;
  }
  for (int i = 0; i < n; i++) {
    int new_x = x[i] + d[i];
    if (new_x <=BASE && new_x >= -BASE) {
      int j = idx[new_x+BASE];
      if (j > 0 && x[j-1] + d[j-1] == x[i]) {
        return true;
      }
    }
  }
  return false;
}
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  if (solve()) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
