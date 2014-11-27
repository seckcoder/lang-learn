#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
 public:
  bool dictFind(const unordered_set<string> &dict, const string &s) {
    return (dict.find(s) != dict.end());
  }
  bool wordBreak(string s, unordered_set<string> &dict) {
    if (s.size() == 0) return true;
    for (int size = 1; size <= s.size(); size++) {
      cout << s.substr(0, size) << " " << s.substr(size, s.size() - size) << endl;
      if (dictFind(dict, s.substr(0, size)) && wordBreak(s.substr(size, s.size() - size), dict)) {
        return true;
      }
    }
    return false;
  }
};


int main(int argc, const char *argv[])
{
  Solution sol;
  string s = "abcdbe";
  unordered_set<string> dict({"abc", "a", "b", "d", "b", "dbe"});
  if (sol.wordBreak(s, dict)) {
    cout << "hello" << endl;
  }
  return 0;
}
