#include <vector>

using std::vector;

#define COLOR_WHITE 0
#define COLOR_GRAY 1
#define COLOR_BLACK 2

class Vertex {
 public:
  char color;
  int pi;
  int d;
  int f;
};

class Graph {
 public:
  vector<Vertex> v;
  vector<vector<int> > e;
};
