//#define SECK_DEBUG

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
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
#include <cfloat>
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
#define N 100

double dis(int x1, int y1, int x2, int y2) {
  double hx = x1 - x2;
  double hy = y2 - y1;
  return std::sqrt(hx * hx + hy * hy);
}

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int n, vb, vs;
  int x[N];
  scanf("%d %d %d", &n, &vb, &vs);
  for (int i = 0; i < n; i++) {
    scanf("%d", &x[i]);
  }
  int xu, yu;
  scanf("%d %d", &xu, &yu);
  int stop = 1;
  double smallest_t = DBL_MAX;
  double smallest_stop_univ_dis = -1;
  for (int i = 1; i < n; i++) {
    double stop_univ_dis = dis(x[i],0, xu, yu);
    double t = double((x[i] - x[1]) * vs) + stop_univ_dis * (double)vb;
    //cout << i << " " << t << endl;
    if (t < smallest_t) {
      smallest_t = t;
      smallest_stop_univ_dis = stop_univ_dis;
      stop = i;
    } else if (t == smallest_t && stop_univ_dis < smallest_stop_univ_dis) {
      stop = i;
    }
  }
  cout << stop+1 << endl;

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
