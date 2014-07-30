#include <iostream>
#include <vector>
#include <string>
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
#include <cstring>

using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::cin;
using std::string;
using std::map;


#define PI 3.14159265359
typedef long long int int64;
typedef unsigned char uint8;


#define N 100000
#define BASE 1000000007


int n,f;
int fact[N];
int fact_inv[N];
vector<int> n_div_g_guesses[N+1];
int dp[N+1];
bool inCache[N+1];

int modpow(int a, int b){
    int ans = 1;
    while(b){
        if(b & 1) {
            ans = (ans * int64(a)) % BASE;
        }
        a = (a * int64(a)) % BASE;
        b >>= 1;
    }
    return ans;
}

int rev(int v){
    return modpow(v, BASE - 2);
}

void init() {
  fact[0] = 1;
  for (int i = 1; i < N; i++) {
    int64 tmp = i;
    tmp = tmp * fact[i-1];
    fact[i] = tmp % int64(BASE);
    fact_inv[i] = rev(fact[i]);
  }

  // optmization tips: Calculation of modulo/divide is very expensive.
  // So we cache the calculation in an array. At the same time,
  // instead of guessing g, we guess n_div_g, which also replace the division
  // at function:rec with simple add/sub.
  // 2<=g<=n => 1<=n_div_g<=n/2
  for (int n_div_g = 1; n_div_g <= (N>>1); n_div_g++) {
    int acc = n_div_g*2;
    while (acc <= N) {
      // g = acc / n_div_g;
      n_div_g_guesses[acc].push_back(n_div_g);
      acc += n_div_g;
    }
  }
}

// Combination
int C(int n, int m) {
  int64 ans = fact[n]; // n!
  ans = ans * fact_inv[m];
  ans = ans % BASE;
  ans = ans * fact_inv[n-m];
  ans = ans % BASE;
  return int(ans);
}

int rec(int n, int f) {
  //cout << n << " " << f << endl;
  if (n < f) {
    // ai > 0
    return 0;
  } else if (n == f) {
    // ai = 1
    return 1;
  } else if (f == 1) {
    // exist x = n > 1, x | n;
    return 0;
  } else if (inCache[n]) {
    return dp[n];
  } else {
    int64 ans = C(n-1, f-1);
    for (int i = 0; i < n_div_g_guesses[n].size(); i++) {
      int n_div_g = n_div_g_guesses[n][i];
      // Simple trick. a % b, if a or b is negative, the result is undefined
      // in Standard. So we always add BASE.
      ans = (BASE + ans - int64(rec(n_div_g, f))) % BASE;
    }
    inCache[n] = true;
    dp[n] = int(ans);
    return int(ans);
  }
}

int main(int argc, const char *argv[])
{
  //freopen("test.in", "r", stdin);
  init();
  int q;
  scanf("%d", &q);
  while (q >= 1) {
    q -= 1;
    scanf("%d %d", &n, &f);
    memset(inCache, false, sizeof(inCache));
    printf("%d\n", rec(n, f));
  }
  return 0;
}