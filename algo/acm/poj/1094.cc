
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

typedef long long int int64;
typedef unsigned char uint8;

ostream &operator<<(ostream &os, const uint8 v) {
  os << (int)v;
  return os;
}

#define N 26
#define COLOR_WHITE 0
#define COLOR_GRAY 1
#define COLOR_BLACK 2
#define HAS_CYCLE 0
#define RELATION_DETERMINED 1
#define RELATION_UNDETERMINED 2

// topological sort


class Vertex {
 public:
  uint8 color;
  uint8 d;
  uint8 f;
  uint8 indegree;
  uint8 outdegree;
};

class Graph {
 public:
  Vertex v[N];
  bool e[N][N];
  uint8 nv;
  void init(uint8 n) {
    nv = n;
    for (uint8 i = 0; i < nv; i++) {
      v[i].color = COLOR_WHITE;
      v[i].d = 0;
      v[i].f = 0;
      v[i].indegree = 0;
      v[i].outdegree = 0;
      for (uint8 j = 0; j < nv; j++) {
        e[i][j] = false;
      }
    }
  }
  void initDFSData() {
    for (uint8 i = 0; i < nv; i++) {
      v[i].color = COLOR_WHITE;
      v[i].d = 0;
      v[i].f = 0;
    }
  }
  // a -> b
  void addEdge(uint8 a, uint8 b) {
    //cout << (int)a << " " << (int)b << endl;
    if (!e[a][b]) {
      v[a].outdegree += 1;
      v[b].indegree += 1;
    }
    /*cout << v[a].indegree << " ind ";
    cout << v[b].indegree << " ind " << endl;*/
    e[a][b] = true;
  }
};

static int time_stamp = 0;

// return false if has cycle
bool dfsVisit(Graph &g, uint8 u, char sortedSeq[], uint8 &seq_len) {
  time_stamp += 1;
  g.v[u].d = time_stamp;
  g.v[u].color = COLOR_GRAY;
  for (uint8 v = 0; v < g.nv; v++) {
    if (g.e[u][v]) {
      if (g.v[v].color == COLOR_WHITE &&
          !dfsVisit(g, v, sortedSeq, seq_len)) {
          return false;
      } else if (g.v[v].color == COLOR_GRAY) {
        // back edge
        return false;
      }
    }
  }
  time_stamp += 1;
  g.v[u].f = time_stamp;
  g.v[u].color = COLOR_BLACK;
  sortedSeq[seq_len] = u + 'A';
  seq_len += 1;
  //cout << "there " << seq_len << endl;
  return true;
}

// return false if has cycle
uint8 topSort(Graph &g, uint8 origin, char sortedSeq[], uint8 &seq_len) {
  time_stamp = 0;
  g.initDFSData();
  seq_len = 0;

  // start from origin to determin whether the relation has been
  // determined
  if (!dfsVisit(g, origin, sortedSeq, seq_len)) {
    return HAS_CYCLE;
  }
  if (seq_len != g.nv) {
    return RELATION_UNDETERMINED;
  }
  for (uint8 i = 0; i < g.nv; i++) {
    if (g.v[i].color == COLOR_WHITE) {
      if (!dfsVisit(g, i, sortedSeq, seq_len)) {
        return HAS_CYCLE;
      }
    }
  }
  return RELATION_DETERMINED;
}

class Edge {
 public:
  char a, b;
  Edge() {}
  Edge(char ha, char hb):a(ha), b(hb) {}
};

int n;
int m;
char sortedSeq[N+1];
Graph g;
int main(int argc, const char *argv[])
{
  //freopen("test.in", "r", stdin);
  scanf("%d %d", &n, &m);
  while (n != 0 && m != 0) {
    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
      char a, sign, b;
      scanf("%*[ \n\t]%c%c%c", &a, &sign, &b);
      edges.push_back(Edge(a, b));
    }
    g.init(n);
    bool res_determined = false;
    uint8 origin = n;
    for (int i = 0; i < m; i++) {
      char a = edges[i].a;
      char b = edges[i].b;
      g.addEdge(a-'A', b-'A');
      // update origin
      if (origin == n) {
        origin = a-'A';
      } else if (origin == b-'A') {
        origin = a-'A';
      }
      uint8 seq_len = 0;
      uint8 state = topSort(g, origin, sortedSeq, seq_len);
      if (state == HAS_CYCLE) {
        printf("Inconsistency found after %d relations.\n", (i+1));
        res_determined = true;
        break;
      } else if (state == RELATION_DETERMINED) {
        std::reverse(sortedSeq, sortedSeq + seq_len);
        sortedSeq[n] = '\0';
        printf("Sorted sequence determined after %d relations: %s.\n",
               i+1, sortedSeq);
        res_determined = true;
        break;
      }
    }
    if (!res_determined) {
      printf("Sorted sequence cannot be determined.\n");
    }
    scanf("%d %d", &n, &m);
  }
  return 0;
}
