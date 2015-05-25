#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
      // the version without using reversed string s

      if (s.length() <= 1) return s;
      vector<int> pi(s.length()+1, 0);
      compute_prefix_function(s, pi);
      
      // kmp
      int k = longestPalindromeFromBeginning(pi, s);
      
      int num_unmatched_chars = s.length() - k;
      string palind;
      for (int i = 0; i < num_unmatched_chars; i++) {
        palind.push_back(s[s.length() - i - 1]);
      }
      palind += s;
      return palind;
    }
    int longestPalindromeFromBeginning(const vector<int> &pi,
        string s) {
      /* The basic idea is kmp.
       *
       * For string s, the longest palindrome from beginning of s
       * is the longest match for string: s[0...] and rev_s[...-1].
       * So we just run kmp for s and rev_s and return the final k value
       */
      int k = 0;  // number of characters matched
      for (int i = s.length() - 1; i >= 0; i--) {
        while (k > 0 && s[i] != s[k]) {
          k = pi[k];
        }
        if (s[i] == s[k]) {
          k += 1;
        }
        if (k == s.length() && i > 0) {
          k = pi[k];
        }
      }
      return k;
    }
    string shortestPalindrome1(string s) {
      // the version using a reversed string s
      vector<int> pi(s.length()+1, 0);
      compute_prefix_function(s, pi);
      string rev_s(s.rbegin(), s.rend());

      // kmp 
      
      int k = 0; // number of characters matched
      for (int i = 0; i < rev_s.length(); i++) {
        while (k > 0 && rev_s[i] != s[k]) {
          k = pi[k];
        }
        if (rev_s[i] == s[k]) {
          k += 1;
        }
        // for the last character, we don't need to move k
        if (k == s.length() && i + 1 < rev_s.length()) {
          k = pi[k];
        }
      }
      // final k is number of characters matched between rev_s[...,-1]
      // and s[0...]
      
      int num_unmatched_chars = s.length() - k;
      string palind;
      for (int i = 0; i < num_unmatched_chars; i++) {
        palind.push_back(s[s.length() - i - 1]);
      }
      palind += s;
      return palind;
    }
    void compute_prefix_function(string s, vector<int> &pi) {
      
      int s_len = s.length();

      int k = 0; // number of characters matched
      pi[1] = k;
      for (int i = 2;  i <= s.length(); i++) {
        while (k > 0 && s[k] != s[i-1]) {
          // cout << s[k] << " " << s[i] << " " << k << endl;
          k = pi[k];
        }
        if (s[k] == s[i-1]) {
          k += 1;
        }
        pi[i] = k;
      }
    }
};




int main() {
  Solution sol;
  cout << sol.shortestPalindrome("aacecaaa") << endl;
  cout << sol.shortestPalindrome("abcd") << endl;
  cout << sol.shortestPalindrome("a") << endl;
  cout << sol.shortestPalindrome("aba") << endl;
  return 0;
}
