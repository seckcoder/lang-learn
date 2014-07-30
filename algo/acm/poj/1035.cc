//#define SECK_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <cstring>
#include <cstdlib>
#include <list>
#include <numeric>
#include <ctime>
#include <algorithm>
#include <set>
#include <string>
#include <iomanip>
#include <cmath>
#include <map>
#include <functional>
#include <climits>
#include <cstdio>
#include <cassert>

using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::cin;
using std::string;
using std::map;
using std::cerr;
using std::ostream;
using std::istream;

#define PI 3.14159265359
#define IS_ODD(v) ((v) & 1)
//#define IS_EVEN(v) (((v) - (((v) >> 1) << 1)) == 0)
typedef long long int int64;
typedef unsigned char uint8;

ostream &operator<<(ostream &os, const uint8 v) {
  os << (int)v;
  return os;
}

istream &operator>>(istream &is, uint8 &v) {
  int tmp;
  is >> tmp;
  v = (uint8)tmp;
  return is;
}

#define N 10000
#define M 50
#define MAX_STR_LEN 15

int dict_num;
char dict[N+1][MAX_STR_LEN+1];
int dict_words_len[N+1];
char query[M+1][MAX_STR_LEN+1];
int query_num=0;

int replace(const char *s, const char *d) {
  int cnt = 0;
  while (*s && cnt < 2) {
    if (*s != *d) {
      cnt++;
    }
    s++; d++;
  }
  return cnt;
}
bool add(const char *s, const char *d) {
  int cnt = 0;
  while (*s) {
    if (*s != *d) {
      d++;
      cnt += 1;
      if (cnt > 1) return false;
    } else {
      s++;
      d++;
    }
  }
  return true;
}
bool del(const char *s, const char *d) {
  int cnt = 0;
  while (*s) {
    if (*s != *d) {
      s++;
      cnt += 1;
      if (cnt > 1) return false;
    } else {
      s++;
      d++;
    }
  }
  return true;
}

bool correct(const char *s, int len, vector<int> &alts) {
  for (int i = 0; i < dict_num; i++) {
    if (dict_words_len[i] == len) {
      int diff_num = replace(s, dict[i]);
      if (diff_num == 0) {
        return true;
      } else if (diff_num == 1) {
        alts.push_back(i);
      }
    } else if (len + 1 == dict_words_len[i]) {
      if (add(s, dict[i])) {
        alts.push_back(i);
      }
    } else if (len > 1 && dict_words_len[i] + 1 == len) {
      if (del(s, dict[i])) {
        alts.push_back(i);
      }
    }
  }
  return false;
}
void solve() {
  dict_num = 0;
  while (scanf("%s", dict[dict_num]) != EOF && dict[dict_num][0] != '#') {
    dict_words_len[dict_num] = strlen(dict[dict_num]);
    dict_num++;
  }
  while (scanf("%s", query[query_num]) != EOF && query[query_num][0] != '#') {
    query_num++;
  }
  for (int i = 0; i < query_num; i++) {
    int len = strlen(query[i]);
    vector<int> alts;
    if (correct(query[i], len, alts))  {
      printf("%s is correct\n", query[i]);
    } else {
      printf("%s:", query[i]);
      for (int i = 0; i < alts.size(); i++) {
        printf(" %s", dict[alts[i]]);
      }
      printf("\n");
    }
  }
}

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  solve();

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
