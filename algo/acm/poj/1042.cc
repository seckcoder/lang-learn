// use greedy
// 132K	16MS
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

//int fiAcc[MAX_N][MAX_FM+1];
int fishingTime[MAX_N];
int maxFishNum[MAX_N];

void print_result(int total_fish_num) {
  printf("%d", fishingTime[0]);
  for (int i = 1; i < n; i++) {
    printf(", %d", fishingTime[i]);
  }
  printf("\n");
  printf("Number of fish expected: %d\n\n",
         total_fish_num);
}


int GetMaxFiLakeIdx(int fi[], int k) {
  int max_fi = -1;
  int selected = -1;
  for (int i = 0; i <= k; i++) {
    if (fi[i] > max_fi) {
      selected = i;
      max_fi = fi[i];
    }
  }
  return selected;
}

// [0-k], constrained by fm
int GetMaxFishNum(int k, int fm, int ft[]) {
  memset(ft, 0, (k+1)*sizeof(int));
  int tmp_fi[MAX_N];
  memcpy(tmp_fi, fi, (k+1)*sizeof(int));
  int fish_num = 0;
  /*for (int i = 0; i <= k; i++) {
    cout << tmp_fi[i] << " ";
  }
  cout << endl;*/
  while (fm > 0) {
    int selected = GetMaxFiLakeIdx(tmp_fi, k);
    //cout << selected << " " << tmp_fi[selected] << endl;
    if (tmp_fi[selected] == 0) {
      ft[0] += fm;
      break;
    } else {
      fish_num += tmp_fi[selected];
      tmp_fi[selected] -= std::min(di[selected],
                                   tmp_fi[selected]);
      ft[selected] += 1;
      fm -= 1;
    }
  }
  return fish_num;
}

int greedy() {
  int ti_acc = 0;
  int tmpFishingTime[MAX_N];
  int max_fish_num = -1;
  int stop_at = 0;
  int fm;
  for (int i = 0; i < n; i++) {
    fm = max_fm - ti_acc;
    maxFishNum[i] = GetMaxFishNum(i, fm, tmpFishingTime);
    //cout << maxFishNum[i] << " " << endl;
    if (maxFishNum[i] > max_fish_num) {
      stop_at = i;
      max_fish_num = maxFishNum[i];
      memcpy(fishingTime, tmpFishingTime, (stop_at+1)*sizeof(int));
    }
    ti_acc += ti[i];
  }
  for (int i = 0; i <= stop_at; i++) {
    fishingTime[i] *= 5;
  }
  for (int i = stop_at+1; i < n; i++) {
    fishingTime[i] = 0;
  }
  return maxFishNum[stop_at];
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
    int fish_num = greedy();
    print_result(fish_num);
    scanf("%d", &n);
  }
  return 0;
}
