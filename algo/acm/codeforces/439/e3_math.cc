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

#define N 100000
#define BASE 1000000007

int fact[N];
int fact_inv[N];
int mu[N+1];
//vector<int> gcd_guesses[N+1];
vector<int> ds[N+1];
bool prime[N+1];
bool sqr_bound[N+1];

int euclid_ext(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  } else {
    int hx, hy;
    int g = euclid_ext(b, a%b, hx, hy);
    x = hy;
    y = hx - (a / b) * hy;
    return g;
  }
}

int pmod(int a, int b) {
  if (b < 0) {
    return pmod(-a, -b);
  }
  int ret = a % b;
  if (ret < 0) ret += b;
  return ret;
}

int modinv(int a, int n) {
  int x, y;
  //x*a + y * n = 1
  euclid_ext(a, n, x, y);
  return pmod(x, n);
}

void init() {
  // fact and fact_inv
  fact[0] = 1;
  fact_inv[0] = 0; // no inv for zero. [0]n is not in group Z*
  for (int i = 1; i < N; i++) {
    int64 tmp = fact[i-1];
    tmp *= i;
    fact[i] = tmp % BASE;
    fact_inv[i] = modinv(fact[i], BASE);
  }

  // Time Complexity?
  /*for (int g = 1; g <= N; g++) {
    for (int i = g; i <= N; i+=g) {
      gcd_guesses[i].push_back(g);
    }
  }*/

  for (int d = 1; d <= N; d++) {
    for (int i = d; i <= N; i+=d) {
      ds[i].push_back(d);
    }
  }

  // record
  memset(prime, true, sizeof(prime));
  prime[0] = false;
  prime[1] = false;
  // [0-i] is right.
  // [i+1-N] composite of [0-i] is right
  // [i+1-N] prime is right.
  for (int i = 2; i<= N; i++) {
    if (prime[i]) {
      // j = k*i, k>=2
      for (int j = i+i; j <= N; j += i) {
        prime[j] = false;
      }
    }
  }

  // square-bound: not square-free
  // pick out the square-bound number.
  sqr_bound[0] = false;
  sqr_bound[1] = false;
  for (int i = 2; i*i <= N; i++) {
    if (prime[i]) {
      int p2 = i*i;
      // k*p2
      for (int j = p2; j <= N; j += p2) {
        sqr_bound[j] = true;
      }
    }
  }
  
  // v*v, k*v*v
  
  mu[1] = 1; // 0 prime
  for (int i = 2; i <= N; i++) {
    if (!sqr_bound[i]) {
      int prime_num = 0;
      for (int j = 0; j < ds[i].size(); j++) {
        int d = ds[i][j];
        prime_num += int(prime[d]);
      }
      //cout << i << " " << prime_num << endl;
      if (IS_ODD(prime_num)) {
        mu[i] = -1;
      } else {
        mu[i] = 1;
      }
    }
  }
}

int C(int n, int m) {
  if (n < m) {
    return 0;
  } else if (n == m) {
    return 1;
  } else {
    // n-m >= 1, m >= 1.
    // fact_inv[0] is undefined!
    int64 ans = fact[n];
    ans = (ans * int64(fact_inv[m])) % BASE;
    ans = (ans * int64(fact_inv[n-m])) % BASE;
    return int(ans);
  }
}

int solve(int n, int f) {
  if (n == f) {
    return 1; 
  } else if (n < f) {
    return 0;
  } else if (f == 1) {
    return 0;
  }
  // n > f > 1;
  int64 ans = 0;
  for (int i = 0; i < ds[n].size(); i++) {
    int d = ds[n][i];
    ans = (ans + mu[d] * C(n/d-1, f-1)) % BASE;
    if (ans < 0) ans += BASE;
  }
  return int(ans);
}

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  init();
  int q;
  scanf("%d", &q);
  while (q>=1) {
    q -= 1;
    int n,f;
    scanf("%d %d", &n, &f);
    printf("%d\n", solve(n, f));
  }


#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
