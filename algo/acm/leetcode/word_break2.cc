#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;


#define M 10000

bool segmentable[M];
class Solution {
public:
    bool wordBreak(string s, unordered_set<string> &dict) {
      memset(segmentable, false, sizeof(segmentable));
      for (int size = 1; size <= s.size() && !segmentable[s.size()-1]; size++) {
        if (!segmentable[size-1] && (dict.find(s.substr(0, size)) != dict.end())) {
          segmentable[size-1] = true;
        }
        if (segmentable[size-1]) {
          for (int i = size; i < s.size(); i++) {
            if (dict.find(s.substr(size, i-size+1)) != dict.end()) {
              segmentable[i] = true;
            }
          }
        }
      }
      return segmentable[s.size()-1];
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
