#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
  public:

    void takeWhen(const vector<string> &words, int L, int cur, int &next, int &spaceLen) {
      // we can take at least one word for each line
      int str_len = words[cur].length(), // length accumulation of word
          acc_len = str_len; // length accumulation of word + 1 space between each word
      next = cur + 1;

      // if we take only one space, we will get the number of words we can get
      // acc_len is used to decide when to break
      while (next < words.size() && acc_len + 1 + words[next].length() <= L) {
        str_len += words[next].length();
        acc_len += 1 + words[next].length();
        next += 1;
      }
      // the real space length
      spaceLen = L - str_len;
    }
    string wrapOne(const vector<string> &words, int cur, int next, int spaceLen) {
      int num_spaces = next - cur - 1; // num_words - 1
      if (num_spaces == 0) {
        string res = words[cur];
        res.append(spaceLen, ' ');
        return res;
      }
      // contains at least two words
      if (spaceLen % num_spaces == 0) {
        int space_unit_len = spaceLen / num_spaces;
        string res = words[cur];
        for (int i = cur+1; i < next; i++) {
          res.append(space_unit_len, ' ');
          res += words[i];
        }
        return res;
      } else {
        int space_unit_len = spaceLen / num_spaces;
        int extra_space_len = spaceLen % num_spaces;
        string res = words[cur];
        for (int i = cur+1; i < next; i++) {
          if (extra_space_len > 0) {
            res.append(space_unit_len+1 , ' ');
            extra_space_len -= 1;
          } else {
            res.append(space_unit_len, ' ');
          }
          res += words[i];
        }
        return res;
      }
    }
    string wrapLast(const vector<string> &words, int L, int cur) {
      string res = words[cur];
      for (int i = cur+1; i < words.size(); i++) {
        res += " ";
        res += words[i];
      }
      res.append(L - res.length(), ' ');
      return res;
    }
    vector<string> fullJustify(vector<string> &words, int L) {
      vector<string> res;
      if (words.size() == 0) return res;
      int cur = 0;
      // contains at least one word
      while (1) {
        int next, spaceLen;
        takeWhen(words, L, cur, next, spaceLen);
        if (next >= words.size()) {
          res.push_back(wrapLast(words, L, cur));
          break;
        } else {
          res.push_back(wrapOne(words, cur, next, spaceLen));
        }
        cur = next;
      }
      return res;
    }
};


int main() {
  Solution sol;
  /*
  vector<string> words {"This", "is", "an", "example", "of", "text", "justification."};
  vector<string> res = sol.fullJustify(words, 16);
  */

  vector<string> words {"a","b","c","d","e"};
  vector<string> res = sol.fullJustify(words, 1);
  for (int i = 0; i < res.size(); i++) {
    cout << res[i] << endl;
  }
  return 0;
}
