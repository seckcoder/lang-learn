#include <iostream>
#include <unordered_map>
using namespace std;

typedef unordered_map<std::string, int> FreqMap;

inline void flipString(const string &s, string &flipped_s) {
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == 'T') {
      flipped_s[i] = 'P';
    } else {
      flipped_s[i] = 'T';
    }
  }
}

int main() {

  int m,n;
  cin >> m >> n;
  FreqMap freq_map; // a hash map to record number of wishes if we flip according to the string(key)
  int max_wishes = 1;
  for (int i = 0; i < m; i++) {
    string s;
    cin >> s;
    string flipped_s(s);
    flipString(s, flipped_s); // flip the string
    FreqMap::iterator it = freq_map.find(s),
                      flipped_it = freq_map.find(flipped_s);
    if (it == freq_map.end() && flipped_it == freq_map.end()) {
      // can't find
      freq_map[s] = 1;
    } else if (it != freq_map.end()) {
      it->second += 1;
      max_wishes = std::max(it->second, max_wishes);
    } else if (flipped_it != freq_map.end()) {
      flipped_it->second += 1;
      max_wishes = std::max(flipped_it->second, max_wishes);
    }
  }
  cout << max_wishes << endl;
  return 0;
}
