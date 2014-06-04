
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

#define int64 long long int

#define R 100
#define C 100
int r, c;
int height[R][C];
int pathLen[R][C];


int f(int i, int j) {
  if (pathLen[i][j] >= 0) {
    return pathLen[i][j];
  } else {
    int res = 0;
    if (i - 1 >= 0 && height[i][j] > height[i-1][j]) {
      res = std::max(res, f(i-1, j));
    }

    if (i + 1 < r && height[i][j] > height[i+1][j]) {
      res = std::max(res, f(i+1, j));
    }

    if (j - 1 >= 0 && height[i][j] > height[i][j-1]) {
      res = std::max(res, f(i, j-1));
    }

    if (j + 1 < c && height[i][j] > height[i][j+1]) {
      res = std::max(res, f(i, j+1));
    }
    return res + 1;
  }
}

int solve() {
  int max_path_len = -1;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < r; j++) {
      pathLen[i][j] = f(i, j);
      max_path_len = std::max(max_path_len, pathLen[i][j]);
    }
  }
  return max_path_len;
}

int main(int argc, const char *argv[])
{
  //freopen("test.in", "r", stdin);
  scanf("%d %d", &r, &c);
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      scanf("%d", &height[i][j]);
      pathLen[i][j] = -1;
    }
  }
  printf("%d\n", solve());
  return 0;
}
