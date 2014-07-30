#include "graph.h"

static int time_stamp = 0;

template<class OnFinished>
void DFS(Graph &g, OnFinished &on_finished) {
  for (int i = 0; i < g.v.size(); i++) {
    g.v[i].color = COLOR_WHITE;
    g.v[i].pi = -1;
  }
  time_stamp = 0;
  for (int u = 0; u < g.v.size(); u++) {
    if (g.v[u].color == COLOR_WHITE) {
      DFSVisit(g, u, on_finished);
    }
  }
}

template<class OnFinished>
void DFSVisit(Graph &g, int u, OnFinished &on_finished) {
  time_stamp += 1;
  g.v[u].d = time_stamp;
  g.v[u].color = COLOR_GRAY;
  for (int i = 0; i < g.e[u].size(); i++) {
    int v = g.e[u][i];
    if (g.v[v].color == COLOR_WHITE) {
      g.v[v].pi = u;
      DFSVisit(g, v, on_finished);
    }
  }
  on_finished(u);
  g.v[u].color = COLOR_BLACK;
  time_stamp += 1;
  g.v[u].f = time_stamp;
}
