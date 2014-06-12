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

using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::cin;
using std::string;
using std::map;


#define PI 3.14159265359

#define N 100
int n, d;
//int t[N];
int main(int argc, const char *argv[])
{
  
  //freopen("test.in", "r", stdin);
  scanf("%d %d", &n, &d);
  int sum_song_time = 0;
  for (int i = 0; i < n; i++) {
    int t;
    scanf("%d", &t);
    sum_song_time += t;
  }
  if (sum_song_time + (n-1)*10 <= d) {
    printf("%d\n", 2*(n-1) + (d - (sum_song_time + (n-1)*10)) / 5);
  } else {
    printf("-1\n");
  }
  return 0;
}
