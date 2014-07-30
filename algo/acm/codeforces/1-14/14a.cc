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

class Point {
 public:
  int i, j;
};
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int w, l;
  scanf("%d %d", &w, &l);
  vector<string> pic;
  for (int i = 0; i < w; i++) {
    string s;
    cin >> s;
    pic.push_back(s);
  }
  Point ul, lr;
  ul.i = ul.j = INT_MAX;
  lr.i = lr.j = INT_MIN;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < l; j++) {
      if (pic[i][j] == '*') {
        ul.i = std::min(i, ul.i);
        ul.j = std::min(j, ul.j);
        lr.i = std::max(i, lr.i);
        lr.j = std::max(j, lr.j);
      }
    }
  }
  for (int i = ul.i; i <= lr.i; i++) {
    cout << pic[i].substr(ul.j, lr.j-ul.j+1) << endl;
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
