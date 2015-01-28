#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;


class CountPair {
  public:
    int expected;
    int contained;
};

class ResultPair {
  public:
    ResultPair(int hs, int hl) : start(hs), len(hl) {}
    int start;
    int len;
    void update(int hs, int hl) {
      start = hs;
      len = hl;
    }
    string select(const string &str) {
      return str.substr(start, len);
    }
};

class Solution {
public:
    string minWindow(string S, string T) {

      if (T.length() == 0) return "";

      typedef std::unordered_map<char, CountPair> HashMap;
      HashMap hash_map;

      int T_uniq_count = 0;
      for (int i = 0; i < T.length(); i++) {
        if (hash_map.find(T[i]) == hash_map.end()) {
          hash_map[T[i]].expected = 1;
          hash_map[T[i]].contained= 0;
          T_uniq_count += 1;
        } else {
          hash_map[T[i]].expected += 1;
        }
      }

      ResultPair ans(0, S.length()+1);

      int fitted_count = 0;
      for (int i = 0, j = 0; i < S.length(); i+=1, j+=1) {
        while (i < S.length()) {
          if (hash_map.find(S[i]) != hash_map.end()) {
            HashMap::mapped_type &cur_counter = hash_map[S[i]];
            cur_counter.contained += 1;
            if (cur_counter.contained == cur_counter.expected) {
              fitted_count += 1;
              if (fitted_count == T_uniq_count) break;
            }
          }
          i += 1;
        }

        // We can't find a fit
        if (i >= S.length()) break;

        // The loop will surely terminate since len(T) > 0, so j must <= i;
        while (true) {
          if (hash_map.find(S[j]) != hash_map.end()) {
            HashMap::mapped_type &cur_counter = hash_map[S[j]];
            cur_counter.contained -= 1;
            if (cur_counter.contained < cur_counter.expected) {
              // this is the just fitting position
              fitted_count -= 1;
              if (i-j+1 < ans.len) {
                ans.update(j, i-j+1);
              }
              break;
            }
          }
          j += 1;
        }
      }
      ans.select(S);
      // cout << ans.second << endl;
      if (ans.len > S.length()) return "";
      else return ans.select(S);
    }
};


int main() {
  Solution sol;
  cout << sol.minWindow("bdab", "ab") << endl;
}
