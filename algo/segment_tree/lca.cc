

#include "../debug.h"
using namespace std;




class LCA {
  public:
    vector<vector<int>> dp;
    vector<int> levels;
    int n,k,r;
    LCA() {
    }
    void fromParents(const vector<int> &parents) {
      n = parents.size();
      for (k = 0; (1<<k) < n; k++) {}
      /* 1<<k >= n. => k >= max possible levels */
      
      dp.resize(n,
          vector<int>(k+1, -1));
      levels.resize(n,-1);
      
      for (int i = 0; i < n; i++) {
        dp[i][0] = parents[i];
      }
      for (int j = 1; j <= k; j++) {
        for (int i = 0; i < n; i++) {
          if (dp[i][j-1] != -1) {
            dp[i][j] = dp[dp[i][j-1]][j-1];
          }
        }
      }

      r = 0;
      while (parents[r] != -1) {
        r = parents[r];
      }
      levels[r] = 0;
      for (int i = 0; i < n; i++) {
        int h = 0, j = i;
        for (j = i; levels[j] < 0; j = parents[j], h += 1) {
          levels[j] = h;
        }
        h += levels[j];
        for (int x = i; x != j; x = parents[x]) {
          levels[x] = h - levels[x];
        }
      }
    }
    int query(int p, int q) {

      if (levels[p] < levels[q]) std::swap(p,q);
      int x = levels[p] - levels[q];
      /* move p to the same level as q */
      for (int i = 0; i <= k; i++) {
        if (x & (1<<i)) {
          p = dp[p][i];
        }
      }
      
      if (p == q) return p;
      for (int i = k; i > 0; i--) {
        if (dp[p][i] >= 0 && dp[p][i] != dp[q][i]) {
          p = dp[p][i], q = dp[q][i];
        }
      }
      return dp[p][0];
    }
};

int main() {
  vector<int> parents {-1, 0, 0, 0, 2,2,2,5,5,6,6,9,9};
  LCA lca();
  lca.fromParents(parents);
  cout << lca.query(4, 12) << endl;
  return 0;
}
