#include <iostream>
#include <vector>
#include <string>
#include <string>
#include <iomanip>
#include <cmath>
#include <map>
#include <set>

using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::cin;
using std::string;
using std::map;


#define PI 3.14159265359

#define N 1000
#define M 2*N+1
int fact2_min_dp[N][N];
int fact5_min_dp[N][N];


typedef struct Point {
  int x, y;
};


// p is prime
int fact(int v, int p) {
  int c = 0;
  while ( v % p == 0 ) {
    v = v / p;
    c += 1;
  }
  return c;
}
int fact5(int v) {
  return fact(v, 5);
}
int fact2(int v) {
  return fact(v, 2);
}

int calcFact(int A[N][N], int n, int dp[N][N], int prime) {
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      if (i == 0 && j == 0) {
        dp[i][j] = fact(A[i][j], prime);
      } else if (i == 0) {
        dp[i][j] = fact(A[i][j], prime) + dp[i][j-1];
      } else if (j == 0) {
        dp[i][j] = fact(A[i][j], prime) + dp[i-1][j];
      } else {
        dp[i][j] = fact(A[i][j], prime) + std::min(dp[i][j-1], dp[i-1][j]);
      }
    }
  }
  return dp[n-1][n-1];
}


void lookForPath(int dp[N][N], int n, char *path) {
  // look for path
  int x = n-1, y = n-1;
  int path_k = 2*n-3; // 2(n-1) elements + \0
  path[path_k+1] = '\0';
  while (x > 0 && y > 0) {
    //cout << x << " " << y << " " << dp[x-1][y] << " " << dp[x][y-1] << " ";
    if (dp[y-1][x] < dp[y][x-1]) {
      path[path_k] = 'D';
      path_k -= 1;
      y = y-1;
    } else {
      path[path_k] = 'R';
      path_k -= 1;
      x = x - 1;
    }
    //cout << path[path_k+1] << " " << endl;
  }
  while (x > 0) {
    path[path_k] = 'R';
    path_k -= 1;
    x -= 1;
  }
  while (y > 0) {
    path[path_k] = 'D';
    path_k -= 1;
    y -= 1;
  }
}

int calcFactBy2Min(int A[N][N],  int n, int dp[N][N]) {
  return calcFact(A, n, dp, 2);
}

int calcFactBy5Min(int A[N][N], int n, int dp[N][N]) {
  return calcFact(A, n, dp, 5);
}

void pathThroughZero(const Point &zero_pos, int n, char *path) {
  int path_k = 0;
  for(int i = 0; i < zero_pos.x; i++) {
    path[path_k] = 'R';
    path_k += 1;
  }
  for(int i = 0; i < n-1; i++) {
    path[path_k] = 'D';
    path_k += 1;
  }
  for(int i = zero_pos.x; i < n-1; i++) {
    path[path_k] = 'R';
    path_k += 1;
  }
  path[path_k] = '\0';
}

void print_dp(int dp[][N], int n) {
  for(int i = 0 ; i < n ;i++) {
    for(int j = 0 ; j < n ;j++) {
      cout << dp[i][j] << " ";
    }
    cout << endl;
  }
}

void solve(int A[N][N], int n, bool has_zero, const Point &zero_pos) {
  //char fact2_min_path[M], fact5_min_path[M];
  char path[M];
  int least_trailing_zero_num;
  //cout << endl;
  calcFactBy2Min(A, n, fact2_min_dp);
  //print_dp(fact2_min_dp, n);
  //cout << endl;
  calcFactBy5Min(A, n, fact5_min_dp);
  /*print_dp(fact5_min_dp, n);
  cout << endl;*/
  if (fact2_min_dp[n-1][n-1] < fact5_min_dp[n-1][n-1]) {
    lookForPath(fact2_min_dp, n, path);
    least_trailing_zero_num = fact2_min_dp[n-1][n-1];
  } else {
    lookForPath(fact5_min_dp, n, path);
    least_trailing_zero_num = fact5_min_dp[n-1][n-1];
  }
  if (has_zero && least_trailing_zero_num > 1) {
    pathThroughZero(zero_pos, n, path);
    cout << 1 << "\n" << path << endl;
  } else {
    cout << least_trailing_zero_num << "\n" << path << endl;
  }
}

int main(int argc, const char *argv[])
{
  int A[N][N];
  int n;
  cin >> n;
  bool has_zero = false;
  Point zero_pos;
  // ---> x(j:0->n);
  // |
  // |
  // |
  // V  y (i:0->n);
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cin >> A[i][j];
      if (A[i][j] == 0) {
        A[i][j] = 10;
        has_zero = true;
        zero_pos.x = j; 
        zero_pos.y = i;
      }
    }
  }
  solve(A, n, has_zero, zero_pos);
  return 0;
}
