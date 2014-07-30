#include <vector>
#include <iostream>

using namespace std;

#define COLOR_WHITE 0
#define COLOR_GRAY 1
#define COLOR_BLACK 2

class Vertex {
 public:
  int c;
  int d;
  int f;
  int low;
  void init() {
    c = COLOR_WHITE;
    d = 0;
    f = 0;
    low = 0;
  }
};

class Graph {
 public:
  Graph() {
    timestamp = 0;
    V.clear();
    E.clear();
  }
  void init(int n) {
    V.resize(n);
    E.resize(n);
    for (int i = 0; i < n; i++) {
      V[i].init();
    }
  }
  int timestamp;
  vector<Vertex> V;
  vector<vector<int> > E;
  int ts() {
    int ans = timestamp;
    timestamp += 1;
    return ans;
  }
  void addEdge(int u, int v) {
    E[u].push_back(v);
    E[v].push_back(u);
  }
};

typedef vector<vector<int> > Tree;

// w 是u及其descendent:v中使得(v,w)且w.d最小的点。
void dfsVisitRec(Graph &g, int u, int &w, Tree &tree) {
  g.V[u].c = COLOR_GRAY;
  g.V[u].d = g.ts();
  g.V[u].low = g.V[u].d;
  for (int i = 0; i < g.E[u].size(); i++) {
    int v = g.E[u][i];
    if (g.V[v].c == COLOR_WHITE) {
      tree[u].push_back(v);
      int v_w = v;
      // (descendent of u,w)
      dfsVisitRec(g, v, v_w, tree);
      g.V[u].low = std::min(g.V[u].low, g.V[v_w].d);
      w = (g.V[v_w].d < g.V[w].d)?v_w:w;
    } else if (g.V[v].c == COLOR_GRAY) {
      // (u,w);
      w = (g.V[v].d < g.V[w].d)?v:w;
    }
  }
  g.V[u].c = COLOR_BLACK;
  g.V[u].f = g.ts();
}

void dfsVisit(Graph &g, int u, Tree &tree) {
  int u_w;
  dfsVisitRec(g, u, u_w, tree);
}

int dfs(Graph &g, Tree &tree) {
  tree.resize(g.V.size());
  for (int i = 0; i < tree.size(); i++) {
    tree[i].clear();
  }
  for (int i = 0; i < g.V.size(); i++) {
    if (g.V[i].c == COLOR_WHITE) {
      dfsVisit(g, i, tree);
    }
  }
  return 0;
}


void getArticulationPoint(const Graph &g, const Tree &tree, int r,
                          vector<int> &pts) {
  for (int i = 0; i < g.V.size(); i++) {
    if (i == r && tree[r].size() >= 2) {
      pts.push_back(i);
    } else if (g.V[i].d > g.V[i].low) {
      pts.push_back(i);
    }
  }
}

template <class T>
ostream &operator<<(ostream &os, const vector<T> &vec) {
  for (int i = 0; i < vec.size(); i++) {
    os << vec[i] << " ";
  }
  return os;
}

int main(int argc, const char *argv[])
{
  freopen("test1.in", "r", stdin);
  int n;
  scanf("%d", &n);
  int u, v;
  Graph g;
  g.init(n);
  while (scanf("%d %d", &u, &v) != EOF) {
    g.addEdge(u, v);
  }
  Tree tree;
  int r = dfs(g, tree);
  vector<int> articulationpts;
  getArticulationPoint(g, tree, r, articulationpts);
  cout << articulationpts << endl;
  return 0;
}
