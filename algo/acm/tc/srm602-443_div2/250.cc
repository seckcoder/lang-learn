#include <iostream>
#include <vector>

using namespace std;


class SoccerLeagues {
 public:
  vector<int> points(vector<string> matches) {
    vector<int> scores(matches.size(), 0);
    for(int i = 0; i < matches.size(); i++) {
      for(int j = 0; j < matches[i].size(); j++) {
        if (matches[i][j] == 'W') {
          scores[i] += 3;
        } else if (matches[i][j] == 'D') {
          scores[i] += 1;
          scores[j] += 1;
        } else if (matches[i][j] == 'L') {
          scores[j] += 3;
        }
      }
    }
    return scores;
  }
};
