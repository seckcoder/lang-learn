//#define SECK_DEBUG

#undef NDEBUG
#ifdef SECK_DEBUG
#define _GLIBCXX_DEBUG
#endif


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


#define PI 3.14159265359
#define IS_ODD(v) ((v) & 1)
//#define IS_EVEN(v) (((v) - (((v) >> 1) << 1)) == 0)
typedef long long int int64;
typedef unsigned char uint8;

ostream &operator<<(ostream &os, const uint8 v) {
  os << (int)v;
  return os;
}


int fruits[3001];
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int n, v;
  scanf("%d %d", &n, &v);
  for (int i = 0; i < n; i++) {
    int ai, bi;
    scanf("%d %d", &ai, &bi);
    fruits[ai] += bi;
  }
  int ans = 0;
  int yesterday_fruits = 0;
  for (int i = 0; i <= 3000; i++) {
    if (yesterday_fruits >= v) {
      ans += v;
      yesterday_fruits = fruits[i];
    } else if (yesterday_fruits + fruits[i] >= v) {
      ans += v;
      //yesterday_fruits = yesterday_fruits + fruits[i] - v;
      yesterday_fruits = fruits[i] - (v - yesterday_fruits);
    } else {
      ans += yesterday_fruits + fruits[i];
      yesterday_fruits = 0;
    }
  }
  ans += std::min(v, yesterday_fruits);
  printf("%d\n", ans);
  
#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
