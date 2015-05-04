#include <string>
#include <iostream>
using namespace std;

#define M 1000


// using dynamic programming.
// O(n^2) for both time and space complexity
string method1(const string s) {
  bool is_palindrome[M][M];
  memset(is_palindrome, false, sizeof(is_palindrome));
  // len = 1
  for (int i = 0; i < s.length(); i++) {
    is_palindrome[i][1] = true;
  }

  // len = 2
  for (int i = 0; i < s.length()-1; i++) {
    if (s[i] == s[i+1]) is_palindrome[i][2] = true;
  }

  for (int len = 3; len <= s.length(); len++) {
    for (int i = 0; i + len - 1 < s.length(); i++) {
      int j = i + len - 1;
      if (s[i] == s[j] && is_palindrome[i+1][len-2]) {
        is_palindrome[i][len] = true;
      }
    }
  }

  int max_len = 0;
  int start = 0;
  for (int i = 0; i < s.length(); i++) {
    for (int len = s.length(); len >= 1; len--) {
      if (is_palindrome[i][len] && len > max_len) {
        max_len = len;
        start = i;
      }
    }
  }
  if (max_len > 0) {
    return s.substr(start, max_len);
  } else {
    return "";
  }
}

// Think in different aspects, we can get different solution. This is amazing

// O(n^2) time and O(1) space
// Generate all even length and odd length palindromes.
string method2(const string s) {
  if (s.empty()) return "";
  int max_len = 1;
  int start = 0;

  // generate even length palindromes
  for (int i = 1; i < s.length(); i++) {
    int low = i-1,
        high = i;
    while (low >= 0 && high < s.length() && s[low] == s[high]) {
      low -= 1;
      high += 1;
    }
    // After loop [(low+1) : (high-1)] is a palindrome
    if (high-low-1 > max_len) {
      max_len = high-low-1;
      start = low + 1;
    }
  }

  // generate odd length palindromes
  for (int i = 1; i < s.length()-1; i++) {
    int low = i-1, high = i+1;
    // loop invariant: [(low+1):(high-1)] is a palindrome
    
    while (low >= 0 && high < s.length() && s[low] == s[high]) {
      low -= 1;
      high += 1;
    }
    if (high-low-1 > max_len) {
      max_len = high-low-1;
      start = low + 1;
    }
  }
  return s.substr(start, max_len);
}


// Manacher's Algo. O(n) time complexity and O(1) space complexity
// TODO:...
string method3(const string s) {
  return "";
}


int main() {
  cout << method1("forgeeksskeegfor") << endl;
  cout << method2("forgeeksskeegfor") << endl;
  return 0;
}
