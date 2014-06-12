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

using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::cin;
using std::string;
using std::map;


#define PI 3.14159265359
#define MOD2(v) ((v) - (((v) >> 1) << 1))
#define IS_ODD(v) (MOD2(v) == 1)
#define IS_EVEN(v) !IS_ODD(v)
#define N 100000

int n, k, p;
vector<vector<int> > ans;
vector<int> odds;
vector<int> evens;

bool solve() {
  if ((k-p) <= odds.size() &&
      (odds.size() - (k-p)) % 2 == 0 &&
      (odds.size() - (k-p)) / 2 + evens.size() >= p) {
    for (int i = 0; i < k-p; i++) {
      vector<int> tmp;
      tmp.push_back(odds.back());
      odds.pop_back();
      ans.push_back(tmp);
    }
    while (odds.size() >= 2) {
      vector<int> tmp;
      tmp.push_back(odds[odds.size() - 1]);
      tmp.push_back(odds[odds.size() - 2]);
      odds.pop_back();
      odds.pop_back();
      ans.push_back(tmp);
    }
    for (int i = 0; i < evens.size(); i++) {
      vector<int> tmp;
      tmp.push_back(evens[i]);
      ans.push_back(tmp);
    }
    assert(ans.size() >= k);
    vector<int> last;
    while (ans.size() >= k) {
      for (int i = 0; i < ans.back().size(); i++) {
        last.push_back(ans.back()[i]);
      }
      ans.pop_back();
    }
    ans.push_back(last);
    return true;
  } else {
    return false;
  }
}

int main(int argc, const char *argv[])
{
  //freopen("test.in", "r", stdin);
  scanf("%d %d %d\n",  &n, &k, &p);
  for (int i = 0; i < n; i++) {
    int v;
    scanf("%d", &v);
    if (IS_ODD(v)) {
      odds.push_back(v);
    } else {
      evens.push_back(v);
    }
  }
  if (!solve()) {
    printf("NO\n");
  } else {
    printf("YES\n");
    for (int i = 0; i < ans.size(); i++) {
      cout << ans[i].size();
      //printf("%u", ans[i].size());
      for (int j = 0; j < ans[i].size(); j++) {
        printf(" %d", ans[i][j]);
      }
      printf("\n");
    }
  }
  return 0;
}
