
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


int D[N];
int P[N];
int dp[M][MAX_SUB_V];
int jurors[M][MAX_SUB_V];
int n, m;

void GetResult(int sub_v, Result &res) {
  res.prosecution = 0;
  res.defence = 0;
  int counter = 0;
  int i = m;
  while (i >= 1) {
    int juror_num = jurors[i][sub_v];
    res.jurors[i-1] = juror_num;
    res.prosecution += P[juror_num];
    res.defence += D[juror_num];
    sub_v = sub_v - (D[juror_num] - P[juror_num]);
    i -= 1;
  }
  sort(res.jurors, res.jurors + m);
}

bool selected(int j, int i, int sub_v) {
  while (i >= 1 && jurors[i][sub_v] != j) {
    int juror_num = jurors[i][sub_v];
    sub_v = sub_v - (D[juror_num] - P[juror_num]);
    i -= 1;
  }
  if (jurors[i][sub_v] == j) {
    return true;
  } else {
    return false;
  }
}

void solve(Result &res) {
  int max_sub_v = m * 40;
  // init
  for (int i = 0; i <= m; i++) {
    for (int sub_v = 0; sub_v <= max_sub_v; sub_v += 1) {
      dp[i][sub_v] = -1;
      jurors[i][sub_v] = 0;
    }
  }
  dp[0][m*20] = 0;
  for (int i = 0; i < m; i++) {
    for (int sub_v = 0; sub_v <= max_sub_v; sub_v += 1) {
      if (dp[i][sub_v] >= 0) {
        for (int j = 1; j <= n; j++) {
          int d_minus_p = D[j] - P[j];
          int new_sub_v = sub_v + d_minus_p;
          if (new_sub_v >= 0 && new_sub_v <= max_sub_v && !selected(j, i, sub_v)) {
            int d_plus_p = D[j] + P[j];
            if (dp[i][sub_v] + d_plus_p >= dp[i+1][new_sub_v]) {
              // we can include j
              dp[i+1][new_sub_v] = dp[i][sub_v] + d_plus_p;
              jurors[i+1][new_sub_v] = j;
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
        GetResult(sub_v1, res);
        return ;
      } else {
        GetResult(sub_v2, res);
        return ;
      }
    } else if (dp[m][sub_v1] >= 0) {
      GetResult(sub_v1, res);
      return ;
    } else if (dp[m][sub_v2] >= 0) {
      GetResult(sub_v2, res);
      return ;
    }
  }
}

int main(int argc, const char *argv[])
{
  //freopen("test.in", "r", stdin);
  int counter = 1;
  scanf("%d %d", &n, &m);
  while (n != 0 && m != 0) {
    for(int i = 1; i <= n; i++) {
      scanf("%d %d", &P[i], &D[i]);
    };
    Result res;
    solve(res);
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
