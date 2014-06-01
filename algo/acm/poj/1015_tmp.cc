
// This version TLEed. There should be something wrong with the implementation
// of Set
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <set>
#include <cstdio>
#include <algorithm>


using namespace std;

#define N 201
#define M 21
#define MAX_SUB_V 801

struct Result {
  int prosecution, defence;
  int jurors[M];
  int dp_v;
};


void GetResult(const int D[], const int P[], const set<int> &jury, Result &res) {
  res.prosecution = 0;
  res.defence = 0;
  int counter = 0;
  for (set<int>::const_iterator it = jury.begin(); it != jury.end(); it++) {
    res.prosecution += P[*it];
    res.defence += D[*it];
    res.jurors[counter] = *it;
    counter += 1;
  }
}

void solve(const int D[], const int P[], const set<int> &U, int n, int m, Result &res) {
  int dp[M][MAX_SUB_V];
  set<int> jurors[M][MAX_SUB_V];
  int max_sub_v = m * 40;
  // init
  for (int i = 0; i <= m; i++) {
    for (int sub_v = 0; sub_v <= max_sub_v; sub_v += 1) {
      dp[i][sub_v] = -1;
    }
  }
  dp[0][m*20] = 0;
  jurors[0][m*20].clear();

  for (int i = 0; i < m; i++) {
    for (int sub_v = 0; sub_v <= max_sub_v; sub_v += 1) {
      if (dp[i][sub_v] >= 0) {
        vector<int> diff(n);
        vector<int>::iterator diff_end = set_difference(U.begin(), U.end(),
                                                        jurors[i][sub_v].begin(), jurors[i][sub_v].end(),
                                                        diff.begin());
        for (vector<int>::iterator it = diff.begin();
             it != diff_end; it++) {
          int j = *it;
          int d_minus_p = D[j] - P[j];
          int new_sub_v = sub_v + d_minus_p;
          if (new_sub_v >= 0 && new_sub_v <= max_sub_v) {
            int d_plus_p = D[j] + P[j];
            if (dp[i][sub_v] + d_plus_p >= dp[i+1][new_sub_v]) {
              //cout << i << " " << sub_v << " " << new_sub_v << endl;
              // we can include j
              dp[i+1][new_sub_v] = dp[i][sub_v] + d_plus_p;
              jurors[i+1][new_sub_v] = jurors[i][sub_v];
              jurors[i+1][new_sub_v].insert(j); // add j to jurors
            }
          }
        }
      }
    }
  }
  for (int sub_v = max_sub_v / 2; sub_v <= max_sub_v; sub_v += 1) {
    int sub_v1 = sub_v;
    int sub_v2 = max_sub_v - sub_v1;
    if (dp[m][sub_v1] >= 0 && dp[m][sub_v2] >= 0) {
      if (dp[m][sub_v1] > dp[m][sub_v2]) {
        GetResult(D, P, jurors[m][sub_v1], res);
        return ;
      } else {
        GetResult(D, P, jurors[m][sub_v2], res);
        return ;
      }
    } else if (dp[m][sub_v1] >= 0) {
      GetResult(D, P, jurors[m][sub_v1], res);
      return ;
    } else if (dp[m][sub_v2] >= 0) {
      GetResult(D, P, jurors[m][sub_v2], res);
      return ;
    }
  }
}

int main(int argc, const char *argv[])
{
  //freopen("test.in", "r", stdin);
  int D[N], P[N];
  int n, m;

  int counter = 1;
  scanf("%d %d", &n, &m);
  //cin >> n >> m;
  while (n != 0 && m != 0) {
    set<int> U;
    for(int i = 1; i <= n; i++) {
      U.insert(i);
      scanf("%d %d", &P[i], &D[i]);
    };
    Result res;
    solve(D, P, U, n, m, res);
    printf("Jury #%d\nBest jury has value %d for prosecution and value %d for defence:\n",
           counter, res.prosecution, res.defence);
    for (int j = 0; j < m; j+=1) {
      printf(" %d", res.jurors[j]);
    }
    printf("\n");
    scanf("%d %d", &n, &m);
    counter += 1;
  }

  return 0;
}
