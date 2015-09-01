
#include <iostream>
#include <vector>
using namespace std;


/* Single threaded */

struct TreeNode {
  int val;
  bool is_thread;
  TreeNode *left, *right;
  TreeNode(int v):val(v), is_thread(false), left(NULL), right(NULL) {}
};




/* right branch points to the successor of threaded node */
vector<int> inOrder(TreeNode *p) {
  vector<int> ans;
  TreeNode sentinel(0); /* a fake node used as the parent of the root */
  TreeNode *pre = &sentinel;
  while (p) {
    /* If previously visited node is not a threaded node, then
     * we know p is on the right branch of previous node,
     * and we should visit p's left branches first(which are p's precessors).
     * We will revisit p again when we get to the nearest p's precessor
     */
    if (!pre->is_thread) {
      while (p->left) p = p->left;
    }
    /* if pre is a threaded node, then we know we have visited
     * p's left branches, now we need to traverse p and visit p's
     * right branches
     */
    ans.push_back(p->val);
    pre = p;
    p = p->right;
  }
  return ans;
}



int main() {
  TreeNode n1(1);
  TreeNode n2(2);
  TreeNode n3(3);
  TreeNode n4(4);
  TreeNode n5(5);
  n1.left = &n2;
  n1.right = &n3;
  n2.left = &n4;
  n2.right = &n5;

  n4.right = &n2;
  n4.is_thread = true;
  n5.right = &n1;
  n5.is_thread = true;

  for (auto v: inOrder(&n1)) {
    cout << v << " " ;
  }
  cout << endl;
    
  return 0;
}
