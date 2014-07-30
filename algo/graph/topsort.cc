#include "dfs.h"
#include <algorithm>


class OnFinishedOp {
 public:
  OnFinishedOp(vector<int> &vec):sorted_vtx(vec){
    sorted_vtx.clear();
  }
  void operator()(int u) {
    sorted_vtx.push_back(u);
  }
 private:
  vector<int> &sorted_vtx;
};

void TopSort(Graph &g,
             vector<int> &sorted_vtx) {
  OnFinishedOp on_finished(sorted_vtx);
  DFS(g, on_finished);
  std::reverse(sorted_vtx.begin(),
               sorted_vtx.end());
}


int main(int argc, const char *argv[])
{
  Graph g;
  vector<int> vtx;
  TopSort(g, vtx);
  return 0;
}
