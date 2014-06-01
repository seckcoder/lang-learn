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
#define MAX_S 10

class Pos{
 public:
  int x, y, s;
  Pos () {}
  Pos(int hx, int hy, int hs):x(hx), y(hy), s(hs) {}
  bool conflict(const Pos &p) {
    int u1 = x, v1 = y;
    int u2 = x + s, v2 = y + s;
    int x1 = p.x, y1 = p.y;
    int x2 = p.x + p.s, y2 = p.y + p.s;
    return
        !((x1 <= u1 && x2 <= u1) ||
          (x1 >= u2 && x2 >= u2) ||
          (y1 <= v1 && y2 <= v1) ||
          (y1 >= v2 && y2 >= v2));
  }
};

int S;
int n;
int max_s;

Pos taken[N];
int sub_cakes[MAX_S+1];


bool canFill(const Pos &pos, int k) {
  for (int i = 0; i < k; i++) {
    if (taken[i].conflict(pos)) {
      return false;
    }
  }
  return true;
}

bool dfs(int k) {
  if (k < n) {
    //cout << k << " " << sub_cakes[k] << endl;
    for (int i = 0; i <= S-sub_cakes[k]; i++) {
      for (int j = 0; j <= S-sub_cakes[k]; j++) {
        Pos pos(i,j,sub_cakes[k]);
        if (canFill(pos, k)) {
          taken[k] = pos;
          if (dfs(k+1)) {
            return true;
          }
        }
      }
    }
    return false;
  } else {
    return true;
  }
}


int main(int argc, const char *argv[])
{
  freopen("test.in", "r", stdin);
  int t;
  scanf("%d", &t);
  while (t>=1) {
    scanf("%d %d", &S, &n);
    int area_sum = 0;
    memset(sub_cakes, 0, sizeof(sub_cakes));
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
      //sort(sub_cakes, sub_cakes+n, greater<int>());
      /*for (int i = 0; i < n; i++) {
        printf("%d ", sub_cakes[i]);
      }
      cout << endl;*/
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
