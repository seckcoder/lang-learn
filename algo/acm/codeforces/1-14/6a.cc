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


int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  const int n = 4;
  int a[n];
  const char* res[] = {"IMPOSSIBLE", "SEGMENT", "TRIANGLE"};
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  std::sort(a, a+n);
  int ans = 0;
  for (int i = 0; i < n - 2; i++) {
    if (a[i] + a[i+1] > a[i+2] && ans < 2) {
      ans = 2;
    } else if (a[i] + a[i+1] == a[i+2] && ans < 1) {
      ans = 1;
    }
  }
  cout << res[ans] << endl;

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}