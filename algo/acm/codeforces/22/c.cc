//#define SECK_DEBUG

#include <iostream>
#include <vector>
#include <queue>
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

#define C2(n) (((n)*((n)-1)) >> 1)

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif
  
  int64 n;
  int m,v;
  cin >> n >> m >> v;
  int max_edge_num = 1 + C2(n-1);
  /*cout << max_edge_num << endl;
  return 0;*/
  if (max_edge_num < m || m < n-1) {
    cout << -1 << endl;
  } else {
    int a[N+1];
    int leftn = 2;
    for (int i = 1; i <= n; i++) {
      a[i] = i;
    }
    std::swap(a[v], a[leftn]);
    int edge_num = 0;
#define print_edge(u, v) \
    printf("%d %d\n", (u), (v)); \
    edge_num += 1
    for (int i = 2; i <= n; i++) {
      print_edge(a[i-1], a[i]);
      //printf("%d %d\n", a[i-1], a[i]);
    }
    for (int i = 1; i < leftn && edge_num < m; i++) {
      for (int j = i+2; j <= leftn && edge_num < m; j++) {
        print_edge(a[i], a[j]);
      }
    }
    for (int i = leftn; i < n && edge_num < m; i++) {
      for (int j = i+2; j <= n && edge_num < m; j++) {
        print_edge(a[i], a[j]);
      }
    }
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
