#include <iostream>
#include <unordered_set>
#include <map>
#include <string>
#include <queue>

using namespace std;


int bfs(const string &start, const string &end,
        map<string,int> &dis,
        unordered_set<string> &visited,
        unordered_set<string> &dict
        ) {
  queue<string> q;
  q.push(start);
  visited.insert(start);
  dis[start] = 1;
  while (!q.empty()) {
    string u = q.front();
    q.pop();
    string v = u;
    for (int i = 0; i < u.length(); i++) {
      for (char c = 'a'; c <= 'z'; c+=1) {
        if (c != v[i]) {
          char tmp = v[i];
          v[i] = c;
          if (dict.find(v) != dict.end() &&
              visited.find(v) == visited.end()) {
            dis[v] = dis[u] + 1;
            if (v == end) return dis[v];
            visited.insert(v);
            q.push(v);
          }
          v[i] = tmp;
        }
      }
    }
  }
  return 0;
}

class Solution {
public:
    int ladderLength(string start, string end, unordered_set<string> &dict) {
      unordered_set<string> visited;
      map<string, int> dis;
      dict.insert(start);
      dict.insert(end);
      if (start == end) return 1;
      return bfs(start, end, dis, visited, dict);
    }
};


int main(int argc, const char *argv[])
{

  string start = "hit";
  string end = "hot";
  unordered_set<string> dict({"hot","dot","dog","lot","log"});
  Solution sol;
  cout << sol.ladderLength(start, end, dict) << endl;
  return 0;
}
