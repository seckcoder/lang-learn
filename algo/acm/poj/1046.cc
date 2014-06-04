
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

#define SQUARE(k) ((k)*(k))

class Color {
 public:
  int r,g,b;
  Color() {}
  Color(int hr, int hg, int hb):r(hr), g(hg), b(hb) {}
  int dis2(const Color &c) const {
    return SQUARE(r - c.r) + SQUARE(g - c.g) + SQUARE(b - c.b);
  }
};

Color dataSets[16];

int searchForData(const Color &c) {
  int res = -1;
  int min_dis2 = INT_MAX;
  for (int i = 0; i < 16; i++) {
    int new_dis2 = dataSets[i].dis2(c);
    if (new_dis2 < min_dis2) {
      res = i;
      min_dis2 = new_dis2;
    }
  }
  return res;
}

int main(int argc, const char *argv[])
{
  //freopen("test.in", "r", stdin);

  for (int i = 0; i < 16; i++) {
    scanf("%d %d %d", &dataSets[i].r, &dataSets[i].g, &dataSets[i].b);
  }
  int r, g, b;
  scanf("%d %d %d", &r, &g, &b);
  while ((r != -1) ||
         (g != -1) ||
         (b != -1)) {
    int i = searchForData(Color(r, g, b));
    printf("(%d,%d,%d) maps to (%d,%d,%d)\n",
           r, g, b,
           dataSets[i].r, dataSets[i].g, dataSets[i].b);
    scanf("%d %d %d", &r, &g, &b);
  }
  return 0;
}
