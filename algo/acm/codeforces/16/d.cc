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

int n;

class Time {
 public:
  uint8 h; // 0-23
  uint8 m; // 0-59
  uint8 d; // 0-99
  void fromString(const string &t_s) {
    h = atoi(t_s.c_str()+1);
    m = atoi(t_s.c_str()+4);
    if (h == 12) h = 0;
    if (t_s[7] == 'p') {
      h = (h+12)%24;
    }
    d = 0;
  }
  bool timeEqual(const Time &t) const {
    return h == t.h && m == t.m;
  }
  bool timeLess(const Time &t) const {
    return h < t.h || (h == t.h && m < t.m);
  }
  friend ostream&operator<<(ostream &os, const Time &t) {
    os << t.h << " " << t.m;
    return os;
  }
};

#define N 100
Time times[N];

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  uint8 n;
  cin >> n;
  std::cin.ignore();
  for (int i = 0; i < n; i++) {
    string t_s;
    std::getline(cin, t_s);
    //cin.getline(t_s);
    //cin >> t_s;
    times[i].fromString(t_s);
    //cout << t_s << " " << times[i] << endl;
  }
  for (int i = 0; i < n-1; ) {
    //cout << i << " " << times[i].h << endl;
    int j = i+1;
    while (j < n && times[j].timeEqual(times[i])) {
      times[j].d = times[i].d + (j-i)/10;
      j += 1;
    }
    i = j - 1; // times[j-1] == times[i]
    if (j < n && times[j].timeLess(times[i])) {
      times[j].d = times[i].d + 1;
    } else if (j < n) { // timeGreater
      times[j].d = times[i].d;
    }
    //cout << i << endl;
    //cout <<  << " " << times[j].d << endl;
    i = j;
  }

  cout << times[n-1].d + 1 << endl;

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
