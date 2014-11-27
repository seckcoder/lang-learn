
#include <string>

using namespace std;

#define tolowercase(c) (((c) - 'A') + 'a')

class Solution {
 public:
  // we consider empty string as palindrome
  bool isPalindrome(string s) {
    formatString(s);
    for (int i = 0, j = s.length() - 1; i < j; i++, j--) {
      if (s[i] != s[j]) return false;
    }
    return true;
  }
  void formatString(string &s) {
    int j = 0;
    for (int i = 0; i < s.length(); i++) {
      if (s[i] >= 'A' && s[i] <= 'Z') {
        s[j] = tolowercase(s[i]);
        j += 1;
      } else if ((s[i] >= 'a' && s[i] <= 'z') ||
                 (s[i] >= '0' && s[i] <= '9')) {
        s[j] = s[i];
        j += 1;
      }
    }
    s.resize(j);
  }
};

int main(int argc, const char *argv[])
{
  
  return 0;
}
