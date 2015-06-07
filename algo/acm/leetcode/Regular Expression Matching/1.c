#include <stdbool.h>
#include <assert.h>

#define charMatch(c,p) (((c) != '\0') && (((p) == '.') || ((c) == (p))))

bool isMatch(char* s, char* p) {
  
  if (*s == '\0' && *p == '\0') return true;
  /* Note:
   * when *s == '\0', we can't return false directly.
   * It's possible that we Match "" with "a*"
   */
  if (*p == '\0') return false;

  if (*(p+1) == '*') {
    // match 0
    if (isMatch(s, p+2)) return true;
    // match 1 or more times
    for (int i = 0; s[i] != '\0' && charMatch(s[i], *p); i++) {
      if (isMatch(s+i+1, p+2)) return true;
    }
    return false;
  } else if (charMatch(*s, *p)) {
    return isMatch(s+1, p+1);
  } else {
    return false;
  }
}


int main() {
  assert(isMatch("aa", "a") == false);
  assert(isMatch("aa", "aa") == true);
  assert(isMatch("aaa", "aa") == false);
  assert(isMatch("aa", "a*") == true);
  assert(isMatch("aa", ".*") == true);
  assert(isMatch("ab", ".*") == true);
  assert(isMatch("bc", ".*c") == true);
  assert(isMatch("aab", "c*a*b") == true);
  assert(isMatch("abbc", "ab*bbc") == true);
  assert(isMatch("abcbcd", "a.*c.*d") == true);
  assert(isMatch("a", "ab*") == true);

  return 0;
}
