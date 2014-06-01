#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <set>
#include <cstdio>
#include <climits>


using namespace std;

#define MAX_B 1010
#define N 100
#define M 100

int n; // n devices
struct BPPair {
  int b;
  int p;
};
vector<vector<BPPair> > inputs;
int dp[N][MAX_B];
int max_b;

void init() {
  //cout << sizeof(dp) << " " << N*MAX_B*sizeof(int) << endl;
  //memset(dp, 0, sizeof(dp));
  for (int i = 0; i < inputs.size(); i++) {
    for (int b = 0; b <= max_b; b++) {
      dp[i][b] = INT_MAX;
    }
  }
}

float solve() {
  init();
  
  // set 1

  for (int i = 0; i < inputs[0].size(); i++) {
    dp[0][inputs[0][i].b] = std::min(dp[0][inputs[0][i].b],
                                     inputs[0][i].p);
  }

  // set > 1
  for (int i = 1; i < inputs.size(); i++) {
    for (int b = 0 ; b <= max_b; b++) {
      if (dp[i-1][b] != INT_MAX) {
        for (int j = 0; j < inputs[i].size(); j++) {
          int new_b = std::min(inputs[i][j].b, b);
          dp[i][new_b] = std::min(dp[i][new_b],
                                  dp[i-1][b] + inputs[i][j].p);
        }
      }
    }
  }

  float max_b_div_p = -1;
  for (int b = 0; b <= max_b; b++) {
    if (dp[inputs.size()-1][b] != INT_MAX) {
      max_b_div_p = max(max_b_div_p, (float)b/(float)dp[inputs.size()-1][b]);
    }
  }
  return max_b_div_p;
}

int main(int argc, const char *argv[])
{
  //freopen("test.in", "r", stdin);
  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    scanf("%d", &n);
    inputs.resize(n);
    max_b = -1;
    for (int j = 0; j < n; j++) {
      int mi;
      scanf("%d", &mi);
      inputs[j].resize(mi);
      for (int k = 0; k < mi; k++) {
        scanf("%d %d", &(inputs[j][k].b),
              &(inputs[j][k].p));
        max_b = max(inputs[j][k].b, max_b);
      }
    }
    printf("%.3f\n", solve());
  }
  return 0;
}
