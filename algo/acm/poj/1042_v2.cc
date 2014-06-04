
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

#define MAX_H 16
#define MAX_N 25
#define MAX_FM (MAX_H*12)

int h, n, max_fm;
int ti[MAX_N]; // 0 -> max_n-2
//int acc_ti[MAX_N]; // 0 -> max_n-2
int fi[MAX_N]; // 0 -> max_n-1
int di[MAX_N]; // 0 -> max_n-1
int dp[MAX_N][MAX_FM+1];  // (0 -> max_n-1) X (0 -> (max_h*12))

class LakeStat {
 public:
  int fish;
  int time;
  LakeStat():fish(0),time(0) {}
  LakeStat(int hf, int ht):fish(hf), time(ht) {}
  void init() {
    fish = 0;
    time = 0;
  }
};

int fishNumBuffer[MAX_N][MAX_FM+1];
LakeStat fishingStats[MAX_N][MAX_FM+1];
int fishingTime[MAX_N];

//#define FISH_TIME(i, t) (((t) + 1) * fi[(i)] - ((di[(i)] * ((t)+1) * (t)) >> 1))
#define FISH_TIME(i, t) (((t) * fi[(i)]) - ((di[(i)] * ((t)-1) * (t)) >> 1))

// fm >= 1
int fishat(int i, int fm) {
  if (di[i] == 0) {
    return fm * fi[i];
  } else {
    int p = int(fi[i]/di[i]) + 1;
    if (fm <= p) {
      return FISH_TIME(i, fm);
    } else {
      return FISH_TIME(i, p);
    }
  }
}

// return max expected fish num
int dfs() {
  // dp[i][fm]: if we stop at the ith lake within fm fishing time,
  // what's the maximum number of fish we can get
  dp[0][0] = 0;
  //cout << fishat(1, max_fm) << endl;
  for (int fm = 1; fm <= max_fm; fm++) {
    int fish_num = fishNumBuffer[0][fm];
    dp[0][fm] = fish_num;
    fishingStats[0][fm].time = fm;
    fishingStats[0][fm].fish = fish_num;
  }
  //cout << fishat(0, 1) << endl;
  for (int i = 1; i < n; i++) {
    dp[i][0] = -1; // ti>0
    for (int fm = 1; fm <= max_fm; fm++) {
      dp[i][fm] = -1; // init
      LakeStat &cur_stat = fishingStats[i][fm];
      for (int k = 0; k <= fm - ti[i-1]; k++)  {
        if (dp[i-1][fm-k-ti[i-1]] >= 0) {
          //int fish_num = fishat(i, k);
          int fish_num = fishNumBuffer[i][k];
          // not >=, for the same number of fish, smaller the k, the better.
          if (dp[i-1][fm-k-ti[i-1]] + fish_num > dp[i][fm]) {
            //cout << dp[i-1][fm-k-ti[i-1]] << " " << k << " " << fish_num << endl;
            dp[i][fm] = dp[i-1][fm-k-ti[i-1]] + fish_num;
            cur_stat.time = k;
            cur_stat.fish = fish_num;
          }
        }
      }
    }
  }
  int stop_at = 0;
  for (int i = 1; i < n; i++) {
    if (dp[i][max_fm] > dp[stop_at][max_fm]) {
      stop_at = i;
    }
  }
  int fm = max_fm;
  for (int i = stop_at; i >= 0; i--) {
    //cout << "here " << fishingStats[i][fm].time << " " << fishingStats[i][fm].fish << endl;
    fishingTime[i] = fishingStats[i][fm].time * 5;
    fm -= fishingStats[i][fm].time;
    if (i > 0) {
      fm -= ti[i-1];
    }
  }
  for (int i = stop_at+1; i < n; i++) {
    fishingTime[i] = 0;
  }
  return dp[stop_at][max_fm];
}

void print_result(int total_fish_num) {
  printf("%d", fishingTime[0]);
  for (int i = 1; i < n; i++) {
    printf(", %d", fishingTime[i]);
  }
  printf("\n");
  printf("Number of fish expected: %d\n\n",
         total_fish_num);
}

int main(int argc, const char *argv[])
{
  //freopen("test.in", "r", stdin);
  scanf("%d", &n);
  while (n > 0) {
    scanf("%d", &h);
    max_fm = h * 12;
    for (int i = 0; i < n; i++) {
      scanf("%d", &fi[i]);
    }
    for (int i = 0; i < n; i++) {
      scanf("%d", &di[i]);
    }
    for (int i = 0; i < n-1; i++) {
      scanf("%d", &ti[i]);
    }
    /*acc_ti[0] = ti[0];
    for (int i = 1; i < n-1; i++) {
      acc_ti[i] += acc_ti[i-1];
    }*/
    for (int i = 0; i < n; i++) {
      int fish_num = fi[i];
      fishNumBuffer[i][0] = 0;
      for (int fm = 1; fm <= max_fm; fm++) {
        fishNumBuffer[i][fm] = fishNumBuffer[i][fm-1] + fish_num;
        fish_num = std::max(0, fish_num - di[i]);
      }
    }
    int fish_num = dfs();
    print_result(fish_num);
    scanf("%d", &n);
  }
  return 0;
}
