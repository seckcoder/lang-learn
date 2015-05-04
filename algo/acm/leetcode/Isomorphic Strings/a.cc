#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;


class Solution {
  public:
    bool isIsomorphic(string s, string t) {
      typedef unordered_map<char, char> HashMap;
      HashMap map_s_t;
      HashMap map_t_s;
      for (int i = 0; i < s.length(); i++) {
        HashMap::iterator it_s_t = map_s_t.find(s[i]);
        HashMap::iterator it_t_s = map_t_s.find(t[i]);
        
        /* one char can't be mapped to two chars */
        if (it_s_t != map_s_t.end() && it_s_t->second != t[i]) return false;
        
        /* two chars can't be mapped to the same char */
        if (it_t_s != map_t_s.end() && it_t_s->second != s[i]) return false;
        
        if (it_s_t == map_s_t.end()) {
            map_s_t[s[i]] = t[i];
        }
        if (it_t_s == map_t_s.end()) {
            map_t_s[t[i]] = s[i];
        }
      }
      return true;
    }
};


int main()
{
  cout << Solution().isIsomorphic("ab", "aa") << endl;
  return 0;
}
