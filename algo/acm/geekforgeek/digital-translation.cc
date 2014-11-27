// http://mp.weixin.qq.com/mp/appmsg/show?__biz=MjM5ODIzNDQ3Mw==&appmsgid=10000256&itemidx=1&sign=46ce0c5f4df00a2651a214d05207fe14

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// char to int: '1' -> 1, '2' -> 2 ...
#define ctoi(c) ((c) - '0')
// int to char: 1 -> 'a', 2 -> 'b', ... 26 -> 'z'
#define itoc(i) ('a' + ((i)-1))


// translate using dp.
namespace dp {

char translate1(const char *s) {
  return itoc((ctoi(s[0])));
}

void translate2(const char *s, vector<string> &str_vec) {
  char c1 = translate1(s);
  char c2 = translate1(&s[1]);
  str_vec.push_back({c1, c2});
  int num = ((ctoi(s[0]) * 10) + ctoi(s[1]));
  if (num >= 1 && num <= 26) {
    str_vec.push_back({itoc(num)});
  }
}

void translate(const char *s, int slen, vector<string> &str_vec) {
  vector<string> dp_vec[3];
  if (slen < 1) return;
  dp_vec[0].push_back({translate1(s)});
  if (slen < 2) {
    str_vec = dp_vec[0];
    return ;
  }
  translate2(s, dp_vec[1]);
  for (int i = 2; i < slen; i++) {
    int cur_i = i % 3;
    int cur_i_1 = (i-1) % 3;
    int cur_i_2 = (i-2) % 3;
    dp_vec[cur_i].clear();
    string s1(1, translate1(&s[i]));
    vector<string> s2;
    translate2(&s[i-1], s2);
    // dp[i] = dp[i-1] + s1
    for (int j = 0; j < dp_vec[cur_i_1].size(); j++) {
      string tmp(dp_vec[cur_i_1][j]);
      tmp.append(s1);
      dp_vec[cur_i].push_back(tmp);
    }
    // dp[i] = dp[i-2] + s2
    for (int j = 0; j < dp_vec[cur_i_2].size(); j++) {
      for (int k = 0; k < s2.size(); k++) {
        string tmp(dp_vec[cur_i_2][j]);
        tmp.append(s2[k]);
        dp_vec[cur_i].push_back(tmp);
      }
    }
  }
  str_vec = dp_vec[(slen-1) % 3];
  std::sort(str_vec.begin(), str_vec.end());
  vector<string>::iterator new_end = std::unique(str_vec.begin(),
                                                 str_vec.end());
  str_vec.resize(new_end - str_vec.begin());
}

}

void printVec(const vector<string> &vec) {
  for (int i = 0; i < vec.size(); i++) {
    cout << vec[i] << endl;
  }
}

int main(int argc, const char *argv[])
{
  vector<string> str_vec;
  dp::translate("22222", 5, str_vec);
  printVec(str_vec);
  return 0;
}
