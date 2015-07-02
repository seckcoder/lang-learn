
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
  int v;
  int w;
  Edge(int hv, int hw) : v(hv), w(hw) {}
};


// adjacency list
typedef vector<vector<Edge> > Graph;


template <class Compare, class DataType>
class Heap {
  public:
    Heap(Compare hc):comp(hc) {}
    void push(vector<DataType> &heap, const DataType &v) {
      heap.push_back(v);
      std::push_heap(heap.begin(), heap.end());
    }
    DataType top(const vector<DataType> &heap) const {
      return heap[0];
    }
    void pop(vector<DataType> &heap) {
      std::pop_heap(heap.begin(), heap.end());
      heap.pop_back();
    }
    bool empty(const vector<DataType> &heap) const {
      return heap.empty();
    }
  private:
    Compare comp;
};

class MinHeapSt {
  public:
    MinHeapSt(size_t size, int hsrc):heap(std::less<int>()) {
      data.resize(size);
      src = hsrc;
    }
    ~MinHeapSt() {
    }
    bool empty() const {
      return heap.empty(data);
    }
    void relax(int u, int v, int w) {
    }
    int extractMin() {
      return 0;
    }
    void extractMin(int &u, int &w) {
    }
  private:
    Heap<std::less<int>, int> heap;
    vector<int> data;
    int src;
};

template <class MinWeightSt>
vector<Edge> dijkstra(const Graph &g, int s) {
  vector<Edge> shortest_paths;
  MinWeightSt min_w_st(g.size(),s);
  while (!min_w_st.empty()) {
    int u,w;
    min_w_st.extractMin(u,w);
    for (vector<Edge>::const_iterator edge_it = g[u].begin();
        edge_it != g[u].end();
        edge_it++) {
      min_w_st.relax(u,edge_it->v,edge_it->w);
    }
  }
  return shortest_paths;
}

int main() {
  vector<vector<int> > edges = {
    {0,1,10}, {0, 3, 5},
    {1,2,1}, {1, 3, 2},
    {2,4,4},
    {3,1,3}, {3,2,9}, {3,4,2},
    {4,2,6}, {4, 0, 7}
  };
  int num_vertices = 5;
  Graph g(num_vertices);
  for (int i = 0; i < edges.size(); i++) {
    int from = edges[i][0],
        to = edges[i][1],
        w = edges[i][2];
    g[from].push_back(Edge(to,w));
  }
  vector<Edge> shortest_paths = dijkstra<MinHeapSt>(g, 0);
  for (int i = 0; i < shortest_paths.size(); i++) {
    cout << 0 << " " << shortest_paths[i].v << " " << shortest_paths[i].w << endl;
  }
  return 0;
}
