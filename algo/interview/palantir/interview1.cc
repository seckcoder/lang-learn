

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Given an array, find longest increasing arithmetic sequence
int las(vector<int> &vec) {
  vector<int> las_dp(0, vec.size());
  for (int i = 0; i < vec.size(); i++) {
    for (int j = 0; j < i; j++) {
      if (vec[i] >= vec[j]) {
        las_dp[i] = std::max(las_dp[i], las_dp[j]+1);
      }
    }
  }
  int max_las = 0;
  for (int i = 0; i < las_dp.size(); i++) {
    max_las = std::max(las_dp[i], max_las);
  }
  return max_las;
}



// Given a list of string, return the list of prefix that can uniquely define each string.

vector<string> uniq_prefix(const vector<string> &s_vec) {
  vector<string> prefix_vec;
  for (int i = 0; i < s_vec.size(); i++) {
    string str = s_vec[i]; // current string
    for (int j = 1; j <= str.length(); j++) {
      // enumerate every prefix
      string prefix1 = str.substr(0, j);
      bool is_unique = true;
      for (int k = 0; k < s_vec.size(); k++) {
        if (k != i) {
          string prefix2 = s_vec[k].substr(0, j);
          if (prefix1 == prefix2) {
            is_unique = false;
            break;
          }
        }
      }
      if (is_unique) {
        prefix_vec.push_back(prefix1);
        break;
      }
    }
  }
  return prefix_vec;
}


void uniq_prefix_update_cursor(const vector<string> &s_vec,
    int k, vector<int> &cursor_vec) {
  const string &cur_str = s_vec[k];
  for (int i = k+1; i < s_vec.size(); i++) {
    int cursor_k = cursor_vec[k],
        cursor_i = cursor_vec[i];
    while (cursor_k > cursor_i && cursor_i < s_vec[i].length() && s_vec[k][cursor_i] == s_vec[i][cursor_i]) {
      cursor_i += 1;
    }
    while (cursor_k == cursor_i &&
        cursor_k < s_vec[k].length() &&
        cursor_i < s_vec[i].length() &&
        s_vec[k][cursor_k] == s_vec[i][cursor_i]) {
      cursor_k += 1;
      cursor_i += 1;
    }
    // cursor_k < cursor_i means s_vec[k][cursor_k] != s_vec[i][cursor_k]
    cursor_vec[k] = cursor_k;
    cursor_vec[i] = cursor_i;
  }
}

vector<string> uniq_prefix_optimized(const vector<string> &s_vec) {
  vector<int> cursor_vec(0, s_vec.size());
  for (int i = 0; i < s_vec.size(); i++) {
    uniq_prefix_update_cursor(s_vec, i, cursor_vec);
  }
  vector<string> prefix_vec;
  for (int i = 0; i < cursor_vec.size(); i++) {
    prefix_vec.push_back(s_vec[i].substr(0, cursor_vec[i]+1));
  }
  return prefix_vec;
}


template <class Iter>
bool is_palindrome(Iter p, Iter r) {
  while (p < r && *p == *r) {
    p++;
    r--;
  }
  return p>=r;
}
template <class Iter>
int longest_palindrome(Iter begin, Iter end) {
  size_t max_len = 0;
  size_t len = 1;
  for (Iter cur = begin; cur != end; cur++, len+=1) {
    if (is_palindrome(begin, cur)) {
      max_len = std::max(len, max_len);
    }
  }
  return max_len;
}

// Given a string, return the number of characters you need to put at the end of the string in order for the string to be a palindrome.
int gen_palindrome(string str) {
  int n = longest_palindrome(str.rbegin(), str.rend());
  return str.length() - n;
}


// Given a list of weights (each one associated with a label), generate a random label based on the weight.




int main() {
  cout << gen_palindrome("aba") << endl;
  cout << gen_palindrome("ab") << endl;
  return 0;
}
