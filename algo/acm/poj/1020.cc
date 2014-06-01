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

#define SQUARE(k) ((k)*(k))

#define N 16
#define MAX_SUB_S 10
#define MAX_S 40

int S;
int n;
int max_s;

int sub_cakes[MAX_SUB_S+1];
int hist[MAX_S+1];

int findConvexLeft() {
  int min_hist = S + 1;
  int x = 0;
  for (int i = 1; i <= S; i++) {
    if (hist[i] < min_hist) {
      min_hist = hist[i];
      x = i;
    }
  }
  return x;
}

int findConvexRight(int x1) {
  int x2 = x1+1;
  while (x2 <= S && hist[x2] == hist[x1]) {
    x2 += 1;
  }
  return x2 - 1;
}

void fillHist(int x, int size) {
  for (int i = x; i <= x + size - 1; i++) {
    hist[i] += size;
  }
}

void recoverHist(int x, int size) {
  for (int i = x; i <= x + size - 1; i++) {
    hist[i] -= size;
  }
}

bool dfs(int k) {
  if (k < n) {
    int x1 = findConvexLeft();
    int x2 = findConvexRight(x1);
    for (int size = max_s; size >= 1; size--) {
      if (sub_cakes[size] > 0 && x1 + size - 1 <= x2 && hist[x1] + size <= S) {
        sub_cakes[size] -= 1;
        fillHist(x1, size);
        if (dfs(k+1)) {
          return true;
        } else {
          recoverHist(x1, size);
          sub_cakes[size] += 1;
        }
      }
    }
    return false;
  } else {
    return true;
  }
}


int main(int argc, const char *argv[]) {
  //freopen("test.in", "r", stdin);
  int t;
  scanf("%d", &t);
  while (t>=1) {
    scanf("%d %d", &S, &n);
    int area_sum = 0;
    memset(sub_cakes, 0, sizeof(sub_cakes));
    memset(hist, 0, sizeof(hist));
    max_s = -1;
    for (int i = 0; i < n; i++) {
      int s;
      scanf("%d", &s);
      max_s = std::max(s, max_s);
      sub_cakes[s] += 1;
      area_sum += SQUARE(s);
    }
    if (area_sum != SQUARE(S)) {
      printf("HUTUTU!\n");
    } else {
      if (dfs(0)) {
        printf("KHOOOOB!\n");
      } else {
        printf("HUTUTU!\n");
      }
    }
    t -= 1;
  }
  return 0;
}
