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

inline uint8 min(uint8 a, uint8 b) {
  return (a<b)?a:b;
}
inline uint8 max(uint8 a, uint8 b) {
  return (a>b)?a:b;
}

// a,b could be negative
// it always return positive remainder.
int pmod(int a, int b) {
  if (b < 0) {
    return pmod(-a, -b);
  }
  int ret = a % b;
  if (ret < 0) ret += b;
  return ret;
}

#define N 100000
int mini[N];
int maxi[N];
int a[N];
int n;

void maintainMin(int i, int &cur_minv, int &cur_mini) {
  if (a[i] <= cur_minv) {
    cur_minv = a[i];
    cur_mini = i;
  }

}
void maintainMax(int i, int &cur_maxv, int &cur_maxi) {
  if (a[i] >= cur_maxv) {
    cur_maxv = a[i];
    cur_maxi = i;
  }
}

bool solve(int seq[]) {
  int cur_minv = a[n-1],
      cur_mini = n-1,
      cur_maxv = a[n-1],
      cur_maxi = n-1;
  for (int i = n-2; i >= 1; i--) {
    if (a[i] > cur_minv && a[i] > a[mini[i-1]]) {
      seq[0] = mini[i-1];
      seq[1] = i;
      seq[2] = cur_mini;
      return true;
    }
    if (a[i] < cur_maxv && a[i] < a[maxi[i-1]]) {
      seq[0] = maxi[i-1];
      seq[1] = i;
      seq[2] = cur_maxi;
      return true;
    }
  }
  return false;
}
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  scanf("%d", &n);
  int cur_minv = INT_MAX,
      cur_mini = 0,
      cur_maxv = INT_MIN,
      cur_maxi = 0;
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    maintainMin(i, cur_minv, cur_mini);
    mini[i] = cur_mini;
    maintainMax(i, cur_maxv, cur_maxi);
    maxi[i] = cur_maxi;
  }
  int seq[3];
  if (n<= 2 || !solve(seq)) {
    printf("0\n");
  } else {
    printf("3\n");
    printf("%d %d %d\n", seq[0]+1, seq[1]+1, seq[2]+1);
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
