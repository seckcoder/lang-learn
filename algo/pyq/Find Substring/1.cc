
/*
 *
 * string s1 = "waeginsapnaabangpisebbasepgnccccapisdnfngaabndlrjngeuiogbbegbuoecccc";
 *
 * string s2 = "a+b+c-";
 *
 * s2的形式是一个字母加上一个符号，正号代表有两个前面的字符，负号代表有四个，也就是
 * 说s2其实是"aabbcccc", 不考虑invalid.
 *
 * 在s1中，找出连续或者不连续的s2，也就是说从s1中找出"aa....bb.....cccc", abc顺序不能变，
 * 但是中间可以有零个或者多个字符，返回工作共有多少个。在上面这个鸽子中，有四个。
 */




/*
 *
 * First we can simplify it to a similar problem
 * 
 *
 * s1 = "abcabc"
 *
 * s2 = "abc".
 *
 * Find number of occurrences of s2 in s1.
 *
 */

#include <vector>
#include <string>
#include <iostream>
using namespace std;

/* 
 * dp[i][j]: numSubstrs(s1[i:], s2[j:])
 * dp[s1.length()][s2.length()] = 1;
 * if (s1[i] == s2[j]) {
 *  dp[i][j] = dp[i+1][j+1] // match i and j
 *        + dp[i+1][j];  // not match i and j
 * } else {
 *  dp[i][j] = dp[i+1][j]
 * }
 * */
int numSubstrs(string s1, string s2) {

  vector<vector<int>> dp(2, vector<int>(s2.length()+1, 0));
  dp[0][s2.length()] = 1;
  dp[1][s2.length()] = 1;

  for (int i = s1.length()-1; i>=0; i--) {
    for (int j = s2.length()-1; j >= 0; j--) {
      if (s1[i] == s2[j]) {
        dp[i%2][j] = dp[(i+1)%2][j+1] + dp[(i+1)%2][j];
      } else {
        dp[i%2][j] = dp[(i+1)%2][j];
      }
      // cout << i << " " << j << " " << dp[i%2][j] << endl;
    }
  }
  return dp[0][0];
}



/*
 * 
 * This question is similar. The only difference is that we need to
 * compare each unit of s2(a+, b+, a-) instead of each character.
 */


inline bool unitEqual(const string &s1, int i, const string &s2, int j) {
  int count = (s2[j+1] == '+')?2:4;
  for (int num = 0; num < count; num++) {
    if (s1[i+num] != s2[j]) return false;
  }
  return true;
}

int numSubstrs1(string s1, string s2) {

  int num_units = s2.length() / 2;
  vector<vector<int>> dp(2, vector<int>(num_units+1, 0));
  dp[0][num_units] = 1;
  dp[1][num_units] = 1;

  for (int i = s1.length() - 2; i >= 0; i -= 1) {
    for (int j = s2.length() - 2; j >= 0; j-=2) {
      int unit_idx = j / 2;
      if (unitEqual(s1, i, s2, j)) {
        dp[i%2][unit_idx] = dp[(i+1)%2][unit_idx+1] + dp[(i+1)%2][unit_idx];
      } else {
        dp[i%2][unit_idx] = dp[(i+1)%2][unit_idx];
      }
    }
  }
  return dp[0][0];
}

int main() {
  cout << numSubstrs1("waeginsapnaabangpisebbasepgnccccapisdnfngaabndlrjngeuiogbbegbuoecccc", "a+b+c-") << endl;
  return 0;
}
