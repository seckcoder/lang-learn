#include <iostream>
#include <vector>
#include <string>
#include <string>
#include <iomanip>
#include <cmath>
#include <map>
#include <set>

using std::cout;
using std::endl;
using std::vector;
using std::cin;
using std::string;
using std::map;
using std::set;


typedef map<string, int> NameScoreMapType;
typedef std::pair<string, int> NameScorePairType;



NameScoreMapType::iterator update_name_score_map(
    NameScoreMapType &name_score_map, const string &name, int score) {
    NameScoreMapType::iterator it = name_score_map.find(name);
    if (it == name_score_map.end()) {
      it = name_score_map.insert(NameScorePairType(name, score)).first;
    } else {
      it->second += score;
    }
    return it;
}


int main() {
  int n;
  cin >> n;
  NameScoreMapType name_score_map;
  int max_score = 0;
  vector<NameScoreMapType::const_iterator> max_scorer_stack;
  vector<NameScorePairType> history(n);
  for(int i = 0; i < n; i++) {
    string name;
    int score;
    cin >> name >> score;
    history[i] = NameScorePairType(name, score);
    NameScoreMapType::iterator it = update_name_score_map(name_score_map, name, score);
    if (it->second > max_score) {
      max_scorer_stack.clear();
      max_scorer_stack.push_back(it);
      max_score = it->second;
    } else if (it->second == max_score) {
      max_scorer_stack.push_back(it);
    }
  }
  if (max_scorer_stack.size() == 1) {
    cout << max_scorer_stack[0]->first << endl;
  } else {
    set<string> winners;
    for(int i = 0; i < max_scorer_stack.size(); i++) {
      winners.insert(max_scorer_stack[i]->first);
    }
    name_score_map.clear();
    for(int i = 0; i < n; i++) {
      NameScoreMapType::iterator it = update_name_score_map(name_score_map, history[i].first, history[i].second);
      if (it->second >= max_score && winners.find(it->first) != winners.end()) {
        cout << it->first << endl;
        break;
      }
    }
  }
  return 0;
}
