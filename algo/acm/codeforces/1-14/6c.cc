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

#define N 100000

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int n;
  int ti[N];
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> ti[i];
  }
  int alice_t = 0, bob_t = 0,
      alice_idx = 0, bob_idx = n-1;

  while (alice_idx <= bob_idx) {
    if (alice_t == bob_t &&
        alice_idx == bob_idx) {
      alice_t += ti[alice_idx];
      alice_idx += 1;
    } else if (alice_t == bob_t) {
      alice_t += ti[alice_idx];
      bob_t += ti[bob_idx];
      alice_idx += 1;
      bob_idx -= 1;
    } else if (alice_t < bob_t) {
      // alice consume
      alice_t += ti[alice_idx];
      alice_idx += 1;
    } else {
      // bob consume
      bob_t += ti[bob_idx];
      bob_idx -= 1;
    }
  }
  cout << alice_idx << " " << (n-1) - bob_idx << endl;

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
