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

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif
  
  int n, v;
  scanf("%d %d", &n, &v);
  vector<int> sellers;
  for (int i = 0; i < n; i++) {
    int ki;
    scanf("%d", &ki);
    bool added = false;
    for (int j = 0; j < ki; j++) {
      int si;
      scanf("%d", &si);
      if (si < v && !added) {
        added = true;
        sellers.push_back(i+1);
      }
    }
  }

  cout << sellers.size() << "\n";
  if (sellers.size() > 0) {
    cout << sellers[0];
  }
  //printf("%u\n", sellers.size());
  for (int i = 1; i < sellers.size(); i++) {
    printf(" %d", sellers[i]);
  }
  cout << endl;

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
