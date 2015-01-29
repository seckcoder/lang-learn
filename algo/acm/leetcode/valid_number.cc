#include <cstring>


#include <iostream>

using namespace std;

class Solution {
  public:
    int cur = 0;
    const char *s;
    int len;

    bool isNumber(const char *hs) {
      cur = 0;
      s = hs;
      len = strlen(hs);
      //cout << len << endl;
      return parse();
    }
    void skipSpaces() {
      while (cur < len && s[cur] == ' ') cur += 1;
    }
    bool parseNonZeroInt() {
      if (cur >= len) return true;
      if (s[cur] == '0') return false;
      while (cur < len && s[cur] >= '0' && s[cur] <= '9') cur += 1;
      return true;
    }
    bool isDigit(char c) {
      return c >= '0' && c <= '9';
    }
    bool parseIntNonEmpty() {
      if (cur >= len) return false; // TODO...
      if (!isDigit(s[cur])) return false;
      while (cur < len && isDigit(s[cur])) cur += 1;
      return true;
      /* if (s[cur] == '0') { */
      /*   cur += 1; */
      /*   return parseNonZeroInt(); */
      /* } else { */
      /*   return parseNonZeroInt(); */
      /* } */
    }

    bool parseDecimalNonEmpty() {
      if (cur >= len) return false;
      if (!isDigit(s[cur])) return false;
      return parseDecimal();
    }
    bool parseDecimal() {
      while (cur < len && s[cur] >= '0' && s[cur] <= '9') cur += 1;
      return true;
    }
    bool isSign(char c) {
      return c == '-' || c == '+';
    }
    bool parseScientific() {
      if (cur >= len) return false; // TODO...
      if (!isSign(s[cur]) && !isDigit(s[cur])) return false;
      if (s[cur] == '0') {
        cur += 1;
        return parseNonZeroInt();
      } else if (isSign(s[cur])) {
        cur += 1;
        return parseIntNonEmpty();
      } else {
        return parseIntNonEmpty();
      }
    }
    bool parse1() {
       if (s[cur] == '.') {
        cur += 1;
        if (!parseDecimalNonEmpty()) return false;
      } else if (isDigit(s[cur])) {
        if (!parseIntNonEmpty()) return false;
        if (cur >= len) return true;
        if (s[cur] == '.') {
          cur += 1;
          if (!parseDecimal()) return false;
        } else if (s[cur] == 'e') {
          cur += 1;
          if (!parseScientific()) return false;
        }
      }
      return true;
    }
    bool parse() {
      skipSpaces();
      if (cur >= len) return false;
      if (isSign(s[cur])) {
        cur += 1;
        if (!parse1()) return false;
      } else {
        if (!parse1()) return false;
      }
      skipSpaces();
      return cur >= len;
    }
};

int main() {
  Solution sol;
  const int n = 12;
  const char *ss[n] = {"4e+", "+.8", "-1.", "0", " 0.1 ", "abc", "1 a", "2e10", ".", ".1", "1.", "00"};
  for (int i = 0; i < n; i++) {
    cout << strlen(ss[i]) << " " << ss[i] << " " << sol.isNumber(ss[i]) << endl;
  }
}
