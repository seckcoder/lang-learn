#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cassert>

using namespace std;

struct UndirectedGraphNode {
  int label;
  vector<UndirectedGraphNode *> neighbors;
  UndirectedGraphNode(int x) : label(x) {};
};

class Solution {
  public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
      if (node == NULL) return NULL;
      unordered_map<int, UndirectedGraphNode*> visited;
      return dfs(node, visited);
    }
    UndirectedGraphNode *dfs(UndirectedGraphNode *node, unordered_map<int, UndirectedGraphNode*> &visited) {
      // cout << "begin" << endl;
      UndirectedGraphNode *copied_node = new UndirectedGraphNode(node->label);
      //copied_node->neighbors.clear();
      visited.insert(std::pair<int, UndirectedGraphNode *>(copied_node->label, copied_node));
      // cout << "haha" << endl;
      for (int i = 0; i < node->neighbors.size(); i++) {
        if (visited.find(node->neighbors[i]->label) == visited.end()) {
          copied_node->neighbors.push_back(dfs(node->neighbors[i], visited));
        } else {
          // cout << "here" << endl;
          copied_node->neighbors.push_back(visited[node->neighbors[i]->label]);
        }
      }
      //cout << "there" << endl;
      return copied_node;
    }
};
int main() {
  Solution sol;
  UndirectedGraphNode node(-1);
  node.neighbors.push_back(&node);
  UndirectedGraphNode *pn = sol.cloneGraph(&node);
  assert(pn->label == node.label);
  cout << pn->neighbors.size() << endl;
  assert(pn->neighbors[0] == pn);
  return 0;
}
