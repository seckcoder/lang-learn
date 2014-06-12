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

using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::cin;
using std::string;
using std::map;


#define PI 3.14159265359
#define int64 long long int

#define N 100000
int n;
int64 x;
int64 c[N];
int main(int argc, const char *argv[])
{
  
  //freopen("test.in", "r", stdin);
  //scanf("%d %I64d", &n, &x);
  cin >> n >> x;
  for (int i = 0; i < n; i++) {
    cin >> c[i];
  }
  std::sort(c, c+n);
  int64 ans = 0;
  cin >> ans;
  for (int i = 0; i < n; i++) {
    ans += x * c[i];
    if (x - 1 < 1) {
      x = 1;
    } else {
      x = x - 1;
    }
  }
  cout << ans << endl;
  //printf("%I64d\n", ans);
  return 0;
}
