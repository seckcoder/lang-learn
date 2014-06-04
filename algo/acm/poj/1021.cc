// there's still something wrong with the hash function, which makes it
// won't pass the test case:
/*6 3 14
0 0 0 1 0 2 1 1 2 0 2 1 2 2 3 1 3 2 3 0 4 1 4 2 5 0 5 1
0 1 0 2 1 1 1 2 1 0 2 0 2 1 3 2 3 1 3 0 4 1 5 0 5 1 5 2*/
// It seems the test cases on poj is not rigorous.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <set>
#include <cstdio>
#include <climits>
#include <functional>


using namespace std;


#define M 100

class Point {
 public:
  int x, y;
};

int w, h, n;
vector<Point> graph1;
vector<Point> graph2;
int Board[M][M];

void GetCPGBFS(const vector<Point> &graph, int k, vector<bool> &visited,
               vector<int> &conn_points) {
  conn_points.push_back(k);
  visited[k] = true;
  int top = 0;
  while (top < conn_points.size()) {
    const Point &cur_p = graph[conn_points[top]];
    top += 1;

    // right
    if (cur_p.x + 1 < w) {
      int k_right = Board[cur_p.x + 1][cur_p.y];
      if (k_right >= 0 && !visited[k_right]) {
        conn_points.push_back(k_right);
        visited[k_right] = true;
      }
    }

    // left
    if (cur_p.x - 1 >= 0) {
      int k_left = Board[cur_p.x - 1][cur_p.y];
      if (k_left >= 0 && !visited[k_left]) {
        conn_points.push_back(k_left);
        visited[k_left] = true;
      }
    }

    // up
    if (cur_p.y + 1 < h) {
      int k_up = Board[cur_p.x][cur_p.y + 1];
      if (k_up >= 0 && !visited[k_up]) {
        conn_points.push_back(k_up);
        visited[k_up] = true;
      }
    }

    // down
    if (cur_p.y - 1 >= 0) {
      int k_down = Board[cur_p.x][cur_p.y - 1];
      if (k_down >= 0 && !visited[k_down]) {
        conn_points.push_back(k_down);
        visited[k_down] = true;
      }
    }
  }
}


void UpdateBoard(const vector<Point> &graph) {
  //cout << "updateboard" << endl;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      Board[i][j] = -1;
    }
  }
  for (int i = 0; i < graph.size(); i++) {
    Board[graph[i].x][graph[i].y] = i;
  }
}

void GetConnectedPointGroup(const vector<Point> &graph,
                            vector<vector<int> > &cpg) {
  UpdateBoard(graph);
  vector<bool> visited(graph.size(), false);
  cpg.clear();
  //cout << "here" << endl;
  for (int i = 0; i < graph.size(); i++) {
    //cout << i << " " << visited[i] << endl;
    if (!visited[i]) {
      vector<int> tmp;
      cpg.push_back(tmp);
      GetCPGBFS(graph, i, visited, cpg.back());
      //cout << cpg.back().size() << endl;
    }
  }
}


bool CmpCPGBySize(const vector<int> &g1,
                  const vector<int> &g2) {
  return g1.size() < g2.size();
}

void hashCPG(const vector<Point> &graph,
             const vector<int> &conn_points,
             vector<int> &hash_v) {
  hash_v.resize(conn_points.size());
  for (int i = 0; i < conn_points.size(); i++) {
    hash_v[i] = 0;
    for (int j = 0; j < conn_points.size(); j++) {
      if (graph[conn_points[i]].x == graph[conn_points[j]].x ||
          graph[conn_points[i]].y == graph[conn_points[j]].y ) {
        hash_v[i] += 1;
      }
    }
  }
  sort(hash_v.begin(), hash_v.end());
}

bool hashEqual(const vector<int> &v1,
               const vector<int> &v2) {
  if (v1.size() != v2.size()) {
    return false;
  }
  for (int i = 0; i < v1.size(); i++) {
    if (v1[i] != v2[i]) {
      return false;
    }
  }
  return true;
}

int removeHashV(const vector<int> &hash_v,
                const vector<vector<int> > &hash_seq,
                vector<bool> & removed) {
  for (int i = 0; i < hash_seq.size(); i++) {
    if (!removed[i] && hashEqual(hash_v, hash_seq[i])) {
      removed[i] = true;
      return i;
    }
  }
  return -1;
}

bool solve() {
  vector<vector<int> > cpg1;
  GetConnectedPointGroup(graph1, cpg1);
  vector<vector<int> > cpg2;
  GetConnectedPointGroup(graph2, cpg2);
  /*print_cpg(cpg1);
  print_cpg(cpg2);*/
  //cout << cpg1.size() << " " << cpg2.size() << endl;
  if (cpg1.size() != cpg2.size()) {
    return false;
  }
  sort(cpg1.begin(), cpg1.end(), CmpCPGBySize);
  sort(cpg2.begin(), cpg2.end(), CmpCPGBySize);
  
  int cpg_num = cpg1.size();
  for (int i = 0; i < cpg_num;) {
    int j = i;
    while (j < cpg_num && cpg1[j].size() == cpg1[i].size()) {
      if (cpg2[j].size() != cpg1[i].size()) {
        return false;
      }
      j += 1;
    }

    vector<vector<int> > cpg1_hash_seq(j-i);
    vector<vector<int> > cpg2_hash_seq(j-i);
    for (int k = i; k < j; k++) {
      hashCPG(graph1, cpg1[k], cpg1_hash_seq[k-i]);
      hashCPG(graph2, cpg2[k], cpg2_hash_seq[k-i]);
    }
    vector<bool> removed(cpg2_hash_seq.size(), false);
    for (int u = 0; u < cpg1_hash_seq.size(); u++) {
      if (removeHashV(cpg1_hash_seq[u], cpg2_hash_seq, removed) < 0) {
        return false;
      }
    }
    i = j;
    //cout << i << endl;
  }
  return true;
}

int main(int argc, const char *argv[])
{
  freopen("test.in", "r", stdin);
  int t;
  scanf("%d", &t);
  while (t >= 1) {
    scanf("%d %d %d", &w, &h, &n);
    graph1.resize(n);
    graph2.resize(n);
    for (int i = 0; i < n; i++) {
      scanf("%d %d", &graph1[i].x, &graph1[i].y);
    }
    for (int i = 0; i < n; i++) {
      scanf("%d %d", &graph2[i].x, &graph2[i].y);
    }
    if (solve()) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
    t -= 1;
  }
  return 0;
}
