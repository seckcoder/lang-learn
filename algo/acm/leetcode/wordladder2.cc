#include <iostream>
#include <unordered_set>
#include <vector>
#include <map>
#include <string>
#include <queue>

using namespace std;


int bfs(const string &start, const string &end,
        map<string,int> &dis,
        map<string, vector<string> > &pre,
        unordered_set<string> &visited,
        unordered_set<string> &dict
        ) {
  queue<string> q;
  q.push(start);
  visited.insert(start);
  dis[start] = 1;
  bool found = false;
  int shortest_dis = 0;
  while (!q.empty()) {
    string u = q.front();
    q.pop();
    string v = u;
    int dis_u = dis[u];
    if (found && dis_u >= shortest_dis) {
      break;
    }
    for (int i = 0; i < u.length(); i++) {
      for (char c = 'a'; c <= 'z'; c+=1) {
        if (c != v[i]) {
          char tmp = v[i];
          v[i] = c;
          if (dict.find(v) != dict.end()) {
            if (pre[v].size() == 0) {
              pre[v].push_back(u);
            } else if (dis[pre[v][0]] >= dis[u]) {
              pre[v].push_back(u);
            }
            if (visited.find(v) == visited.end()) {
              dis[v] = dis_u + 1;
              if (!found && v == end) {
                found = true;
                shortest_dis = dis[v];
              }
              visited.insert(v);
              q.push(v);
            }
          }
          v[i] = tmp;
        }
      }
    }
  }
  if (found) return shortest_dis;
  else return 0;
}


void dfs(const string &u,
         map<string, vector<string> > &pre,
         vector<vector<string> > &seqs) {
  for (int i = 0; i < pre[u].size(); i++) {
    vector<vector<string> > cur_seqs;
    dfs(pre[u][i], pre, cur_seqs);
    for (int j = 0; j < cur_seqs.size(); j++) {
      cur_seqs[j].push_back(u);
      seqs.push_back(cur_seqs[j]);
    }
  }
}

class Solution {
public:
    vector<vector<string> > ladderLength(string start, string end, unordered_set<string> &dict) {
      unordered_set<string> visited;
      map<string, int> dis;
      map<string, vector<string> > pre;
      dict.insert(start);
      dict.insert(end);
      vector<vector<string> > seqs;
      if (start == end) {
        vector<string> seq;
        seq.push_back(start);
        seqs.push_back(seq);
      } else {
        int len = bfs(start, end, dis, pre, visited, dict);
        cout << len << endl;
        if (len > 0) {
          dfs(end, pre, seqs);
        }
      }
      return seqs;
    }
};


int main(int argc, const char *argv[])
{

  string start = "hit";
  string end = "hot";
  unordered_set<string> dict({"hot","dot","dog","lot","log"});
  Solution sol;
  vector<vector<string> > seqs = sol.ladderLength(start, end, dict);
  for (int i = 0; i < seqs.size(); i++) {
    for (int j = 0; j < seqs[i].size(); j++) {
      cout << seqs[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}
