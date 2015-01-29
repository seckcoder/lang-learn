#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    bool isScramble(string s1, string s2) {
      if (s1.size() != s2.size()) return false;
      int n = s1.size();
      if (n == 0) return true;
      int dict[26];
      memset(dict, 0, 26*sizeof(int));
      //int dict[26] = {0};
      for (int i = 0; i < n; i++) {
        dict[s1[i]-'a']++;
      }
      for (int i = 0; i < n; i++) {
        dict[s2[i]-'a']--;
      }
      for (int i = 0; i < 26; i++) {
        if (dict[i]) return false;
      }
      if (n <= 3) return true;
      for (int i = 1; i < n; i++) {
        bool result = isScramble(s1.substr(0, i), s2.substr(0, i))
          && isScramble(s1.substr(i, n-i),s2.substr(i, n-i));
        result = result || isScramble(s1.substr(0,i), s2.substr(n-i, i)) &&
            isScramble(s1.substr(i, n-i),s2.substr(0, n-i));
        if (result) return true;
      }
      return false;
    }
};

int main() {
  Solution sol;
  cout << sol.isScramble("rgtae", "great") << endl;
  return 0;
}
