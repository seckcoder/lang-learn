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

#define N 100
#define M 100
uint8 nprices, nfruits;
uint8 prices[N];
string names[M];

class NameCounter {
 public:
  string s;
  uint8 count;
  NameCounter() {}
  NameCounter(const string &hs, const uint8 c):s(hs), count(c) {}
};
bool cmp_name_counter(const NameCounter &n1,
                      const NameCounter &n2) {
  return n1.count > n2.count;
}

void stat(vector<NameCounter> &nc) {
  for (int i = 0; i < nfruits; i++) {
    bool found = false;
    for (int j = 0; j < nc.size(); j++) {
      if (names[i] == nc[j].s) {
        nc[j].count += 1;
        found = true;
        break;
      }
    }
    if (!found) {
      nc.push_back(NameCounter(names[i], 1));
    }
  }
}
void solve(int &minp, int &maxp) {
  minp = 0;
  maxp = 0;
  vector<NameCounter> name_counters;
  stat(name_counters);
  std::sort(name_counters.begin(),
            name_counters.end(),
            cmp_name_counter);
  std::sort(prices, prices+nprices);
  for (int i = 0; i < name_counters.size(); i++) {
    /*cout << name_counters[i].s << " " << name_counters[i].count << endl;
    cout << prices[i] << " " << prices[n-i-1] << endl;*/
    minp += name_counters[i].count * prices[i];
    maxp += name_counters[i].count * prices[nprices-i-1];
  }
}
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif
  cin >> nprices >> nfruits;
  for (int i = 0; i < nprices; i++) {
    cin >> prices[i];
  }

  for (int i = 0; i < nfruits; i++) {
    cin >> names[i];
  }

  int minp, maxp;
  solve(minp, maxp);
  cout << minp << " " << maxp << endl;

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
