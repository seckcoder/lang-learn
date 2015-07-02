/*
 * Construct a binary search tree from the breads-first-search result
 * 
 *
 * The basic idea is to use BFS to reconstruct the bst.
 * Generally, we maintain a range to represent the value we can put into this
 * node. Each range corresponds to a TreeNode.
 *
 * 
 */

#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

class TreeNode {
  public:
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    int val;
    TreeNode(TreeNode *p) {
      left = NULL;
      right = NULL;
      parent = p;
    }
};

struct Range {
  int left, right;
  TreeNode *root;
  Range(int l, int r, TreeNode *p) : left(l), right(r) {
    root = new TreeNode(p);
  }
  bool contain(int v) {
    return left <= v && v <= right;
  }
  void release() {
    if (root && root->parent) {
      if (root->parent->left == root) {
        root->parent->left = NULL;
        delete root;
      } else {
        root->parent->right = NULL;
        delete root;
      }
    } else if (root) {
      delete root;
    }
  }
};

/* bfs: the bfs search result */
TreeNode *bstFromBFS(vector<int> &bfs) {

  queue<Range> range_que;
  Range range(INT_MIN, INT_MAX, NULL);
  TreeNode *root = range.root;
  range_que.push(range);

  for (int i = 0; i < bfs.size(); i++) {
    Range cur_range = range_que.front();
    range_que.pop();
    while (!cur_range.contain(bfs[i])) {
      cur_range.release();
      cur_range = range_que.front();
      range_que.pop();
    }
    cur_range.root->val = bfs[i];
    Range left_range(cur_range.left, bfs[i]-1, cur_range.root);
    Range right_range(bfs[i]+1, cur_range.right, cur_range.root);
    range_que.push(left_range);
    range_que.push(right_range);
  }
  while (!range_que.empty()) {
    Range cur_range = range_que.front();
    cur_range.release();
    range_que.pop();
  }
  return root;
}

int main() {
  return 0;
}
