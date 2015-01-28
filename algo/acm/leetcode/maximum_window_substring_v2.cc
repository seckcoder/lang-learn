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
      for (int p = 0, r = 0; r < S.length(); p += 1, r += 1) {
        cout << p << " " << r << endl;
        // loop invariant: Fix p, [p,r] is not a fit. Extend r until we find one.
        while (r < S.length()) {
          if (hash_map.find(S[r]) != hash_map.end()) {
            HashMap::mapped_type &cur_counter = hash_map[S[r]];
            cur_counter.contained += 1;
            if (cur_counter.contained == cur_counter.expected) {
              fitted_count += 1;
              if (fitted_count == T_uniq_count) break;
            }
          }
          r += 1;
        }
        // we can't find a fit
        if (r >= S.length()) break;

        // we find a fit
        // loop invariant: Fix r, [p,r] is a fit. Move p until it's not a fit
        // The loop will break once we break the fit.
        while (1) {
          if (hash_map.find(S[p]) != hash_map.end()) {
            HashMap::mapped_type &cur_counter = hash_map[S[p]];
            cur_counter.contained -= 1;
            if (cur_counter.contained < cur_counter.expected) {
              fitted_count -= 1;
              break;
            }
          }
          p += 1;
        }

        // [p,r] is the smallest fit for current r.
        if (r-p+1 < ans.len) {
          ans.update(p, r-p+1);
        }
      }

      if (ans.len > S.length()) return "";
      else return ans.select(S);
    }
};


int main() {
  Solution sol;
  cout << sol.minWindow("bdab", "ab") << endl;
}
