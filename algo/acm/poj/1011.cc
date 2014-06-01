#include<vector>
#include <iostream>
#include <algorithm>
#include <functional>   // std::greater
using namespace std;

int skipEqual(const vector<int> &sticks, int i) {
  int j = i + 1;
  while (j < sticks.size() && sticks[j] == sticks[i]) {
    j += 1;
  }
  return j;
}

bool tryUnitLen(int k, int l, int unit_len, vector<int> &sticks, bool chosen[]) {
  if (k == 0) {
    // succeed
    return true;
  } else if (l == unit_len) {
    return tryUnitLen(k-1, 0, unit_len, sticks, chosen);
  } else {
    int i = 0;
    while ( i < sticks.size() ) {
      if (!chosen[i] && (l + sticks[i]) <= unit_len) {
        chosen[i] = true;
        if (!tryUnitLen(k, l+sticks[i], unit_len, sticks, chosen)) {
          chosen[i] = false;
          if (l == 0) {
            // l == 0, the first stick can't fit, then it can't be fitted
            // any more
            break;
          } else {
            i = skipEqual(sticks, i);
          }
        } else {
          return true;
        }
      } else {
        i += 1;
      }
    }
    return false;
  }
}


int solve(vector<int> &sticks) {
  sort(sticks.begin(), sticks.end(), greater<int>());
  int max_len = sticks[0];
  int sum_len = 0;
  for(int i = 0; i < sticks.size(); i++) {
    sum_len += sticks[i];
  }
  bool *chosen = (bool*)malloc(sticks.size()*sizeof(bool));
  for(int unit_len = max_len; unit_len < sum_len; unit_len++) {
    if (sum_len % unit_len == 0) {
      memset(chosen, false, sizeof(bool)*sticks.size());
      if (tryUnitLen(sum_len/unit_len, 0, unit_len, sticks, chosen)) {
        return unit_len;
      }
    }
  }
  return sum_len;
}

int main(int argc, const char *argv[])
{
  int n;
  cin >> n;
  while (n != 0) {
    vector<int> sticks(n);
    for(int i = 0; i < n; i++) {
      cin >> sticks[i];
    }
    cout << solve(sticks) << endl;
    cin >> n;
  }
  return 0;
}
