#include <string>
#include <cassert>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;


bool streq(string s1, int s1_start, string s2, int s2_start, size_t len) {
  for (int i = 0; i < len; i++) {
    if (s1[s1_start+i] != s2[s2_start+i]) return false;
  }
  return true;
}

vector<int> naive_string_matcher(string str, string pattern) {
  size_t str_len = str.length(),
         patt_len = pattern.length();

  assert(patt_len <= str_len);
  
  vector<int> patt_indices;
  /* shift: number of characters on the left of starting index to compare
   * with the pattern
   */
  for (int shift = 0; shift <= str_len - patt_len; shift++) {
    /* pattern[0:] == str[shift:shift+patt_len] */
    if (streq(pattern, 0,
          str, shift, patt_len)) {
      patt_indices.push_back(shift);
    }
  }
  return patt_indices;
}

inline int pmod(int a,int b) {
  if (b < 0) {
    return pmod(-a,-b);
  }
  int ret = a % b;
  if (ret < 0) ret += b;
  return ret;
}

/* d: base of input large numbers
 * q: prime number used(generally, we choose q >= pattern.length())
 */
template <class MapFunc>
vector<int> rabin_karp_matcher(string str, string pattern,
    MapFunc c2i,
    int d, int q) {
  int strlen = str.length(),
      patt_len = pattern.length();
  
  // h = d^(m-1) % q
  int h = 1;
  for (int i = 1; i <= patt_len-1; i++) {
    h = (h * d) % q;
  }

  int p = 0,
      t = 0;

  for (int i = 0; i < patt_len; i++) {
    p = (d * p + c2i(pattern[i])) % q;
    t = (d * t + c2i(str[i])) % q;
  }
  vector<int> indices;

  int shift = 0;
  for (shift = 0; shift < strlen - patt_len; shift++) {
    // before the loop, we have t = t_shift
    if (p == t) {
      if (streq(str, shift, pattern, 0, patt_len)) {
        indices.push_back(shift);
      }
    }
    // update t. str[shift] is the high-order digit of t,
    // so we remove it from t(multiply to d^(m-1)).
    // str[shift+patt_len] is the next digit of the low-order digit,
    // so we add it to t.
    //
    // use positive mod here.
    t = pmod(d * (t - c2i(str[shift])*h) + c2i(str[shift+patt_len]),  q);
  }
  
  // shift = strlen - patt_len
  if (p == t) {
    if (streq(str, shift, pattern, 0, patt_len)) {
      indices.push_back(shift);
    }
  }
  return indices;
}


class FiniteAutomata {
  public:
    FiniteAutomata(const string &pattern,
        const std::unordered_set<char> &char_set) {
      int patt_len = pattern.length();
      end_state = patt_len;
      trans.resize(patt_len+1);
      compute_trans_naive(pattern, char_set);
    }
    void compute_trans_naive(
        const string &pattern,
        const std::unordered_set<char> &char_set) {
    }
    const int start_state = 0;
    bool isEndState(int q) const {
      return q == end_state;
    }
    int match(int q, char c) const {
      return 0;
    }
  private:
    vector<std::unordered_map<char, int>> trans;
    int end_state;
};

vector<int> finite_automata_matcher(
    const string str,
    FiniteAutomata &fa) {
  int state = fa.start_state; // initial state is zero
  vector<int> indices;
  for (int i = 0; i < str.length(); i++) {
    state = fa.match(state, str[i]);
    if (fa.isEndState(state)) {
      indices.push_back(i);
    }
  }
  return indices;
}


void compute_prefix_function(const string pattern, vector<int> &pi) {
  int patt_len = pattern.length();

  int k = 0; // number of characters matched
  pi[0] = 0;

  for (int i = 1; i < patt_len; i++) {
    while (k > 0 && pattern[k] != pattern[i]) {
      k = pi[k];
    }

    if (pattern[k] == pattern[i]) {
      k += 1;
    }
    pi[i] = k;
  }
}

vector<int> kmp(const string str, const string pattern) {
  
  int patt_len = pattern.length();
  int str_len = str.length();

  vector<int> pi(patt_len, -1);


  compute_prefix_function(pattern, pi);

  int k = 0;  // number of characters matched
  vector<int> indices;
  for (int i = 0; i < str_len; i++) {
    while (k > 0 && pattern[k] != str[i]) {
      k = pi[k];
    }

    if (pattern[k] == str[i]) {
      k += 1;
    }
    if (k == patt_len) {
      // str[...i] == pattern[...k]
      indices.push_back(i-patt_len+1);
      k = pi[k];
    }
  }
  return indices;
}


inline int c2i(char c) {
  return c - 'a';
}


template <typename T>
void printVec(const vector<T> &vec) {
  for (int i = 0; i < vec.size(); i++) {
    cout << vec[i] << " ";
  }
  cout << endl;
}

int main() {
  /* 0120100120102 */
  string str = "abcabaabcabac";
  string pattern = "abaa";
  vector<int> indices = naive_string_matcher(str, pattern);
  printVec(indices);
  indices = rabin_karp_matcher(str, pattern,
      c2i,
      3, 5);
  printVec(indices);
  printVec(kmp(str, pattern));
  return 0;
}
