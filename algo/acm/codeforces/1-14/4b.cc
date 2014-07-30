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

#define D 31
#define SUMTIME 241

bool dp[D][SUMTIME];
uint8 d, sumtime;
uint8 mint[D];
uint8 maxt[D];
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif
  
  
  cin >> d >> sumtime;
  uint8 sum_mint = 0, sum_maxt = 0;
  //scanf("%d %d", &d, &sumtime);
  for (uint8 i = 1; i <= d; i++) {
    cin >> mint[i] >> maxt[i];
    sum_mint += mint[i];
    sum_maxt += maxt[i];
    //cout << mint[i] << " " << maxt[i] << endl;
    //scanf("%d %d", &mint[i], &maxt[i]);
  }
  if (sumtime < sum_mint ||
      sumtime > sum_maxt) {
    printf("NO\n");
  } else {
    dp[0][0] = true;
    for (uint8 i = 1; i <= d; i++) {
      for (uint8 j = mint[i]; j <= sumtime; j++) {
        for (uint8 t = mint[i]; t <= maxt[i]; t++) {
          //cout << i << " " << j << " " << t << endl;
          if (dp[i-1][j-t]) {
            dp[i][j] = true;
            break;
          }
        }
      }
    }
    if (dp[d][sumtime]) {
      printf("YES\n");
      vector<uint8> hours(d);
      uint8 total = sumtime;
      for (uint8 i = d; i >= 1; i--) {
        for (uint8 t = mint[i]; t <= maxt[i] && t<=total; t++) {
          if (dp[i-1][total-t]) {
            hours[i-1] = t;
            total -= t;
            break;
          }
        }
      }
      for (uint8 i = 0; i < hours.size(); i++) {
        cout << hours[i] << " ";
        //printf("%d ", hours[i]);
      }
    } else {
      printf("NO\n");
    }
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
