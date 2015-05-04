
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef unordered_map<unsigned, unsigned> HashMap;
unsigned hashDNADigit(char c) {
  return (c & 0x7);
}
unsigned hashDNA(const string &s, int cur) {
  unsigned value = 0;
  for (int i = cur; i < cur+10; i++) {
    value = (value << 3) | (hashDNADigit(s[i]));
  }
  return value;
}

class Solution {
  public:

    vector<string> findRepeatedDnaSequences(string s) {
      vector<string> repeated_str;
      if (s.length() < 10) return repeated_str;
      unsigned value = hashDNA(s, 0);
      HashMap substr_freq;
      substr_freq[value] = 1;
      unsigned shiftMask = 0x3fffffff;
      for (int i = 1; i + 10 <= s.length(); i++) {
        value = ((value << 3) & shiftMask) | (hashDNADigit(s[i+9]));
        if (substr_freq.find(value) == substr_freq.end()) {
          substr_freq[value] = 1;
        } else {
          if (substr_freq[value] == 1) repeated_str.push_back(s.substr(i, 10));
          substr_freq[value] += 1;
        }
      }
      return repeated_str;
    }
};


int main() {
  Solution().findRepeatedDnaSequences("CAAAAAAAAAC");
  return 0;
}
