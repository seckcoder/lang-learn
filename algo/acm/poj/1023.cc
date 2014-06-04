
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <set>
#include <cstdio>
#include <climits>
#include <functional>


using namespace std;

#define MAX_K 64

#define MOD2(a) ((a) - (((a) >> 1) << 1))

#define int64 long long int

int main(int argc, const char *argv[])
{
  //freopen("test.in", "r", stdin);

  int t;
  scanf("%d", &t);
  while (t>=1) {
    int k;
    scanf("%d", &k);
    char repr[MAX_K+1];
    scanf("%s", repr);
    char bits[MAX_K+1];
    int64 v;
    scanf("%lld", &v);
    bits[k] = '\0';
    for (int i = k-1; i >= 0; i--) {
      if (MOD2(v) == 0) {
        bits[i] = '0';
        v = v >> 1;
      } else {
        bits[i] = '1';
        if (repr[i] == 'p') {
          v = (v - 1) >> 1;
        } else {
          v = (v + 1) >> 1;
        }
      }
    }
    if (v != 0) {
      printf("Impossible\n");
    } else {
      printf("%s\n", bits);
    }
    t -= 1;
  }
  return 0;
}
