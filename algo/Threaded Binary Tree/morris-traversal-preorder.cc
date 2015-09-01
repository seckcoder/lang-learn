#include <vector>
#include <iostream>
using namespace std;

/* morris iterative tree traversal.
 * Note that morris traversal don't need
 * the tree be a threaded binary tree
 * 
 */

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode (int v):val(v), left(NULL), right(NULL) {}
};


/* morris inorder traversal
 *
 * We maintain the tree so that first we change it into a threaded binary tree for
 * inorder traversal. After nodes traversed, we recover it back to the original binary
 * tree.
 *
 * For every node(current node), if it's left branch is not empty, then it has predecessors.
 * Then we know we should modify some node(thread node) in the left subtree so that it right branch
 * points to current node.
 *
 * The next time we visit the thread node, we change its right branch back to null.
 *
 * */
vector<int> inorder(TreeNode *p) {
  vector<int> ans;
  while (p) {
    if (!p->left) {
      // p doesn't have left branches. So it doesn't have predecessors.
      ans.push_back(p->val);
      p = p->right;
    } else {
      // p has predecessors.
      // First, we find p's nearest predecessor, which is a thread node.
      
      TreeNode *pre = p->left; /* pre might be the predecessor */
      // we know the rightest node of the tree rooted at p-left should
      // be the thread node we want.
      // If this is the first time we visit the thread node, then pre->right is null.
      // Otherwise, pre->right = p
      while (pre->right != NULL && pre->right != p) {
        pre = pre->right;
      }
      if (pre->right == NULL) {
        // This should be the first time we visit the thread node
        pre->right = p;
        /* After we change the subtree rooted at pre into a threaded binary tree,
         * we should start to traverse the subtree.
         * So we first visit the left branches of the subtree
         */
        ans.push_back(p->val);
        p = p->left;
      } else {
        // This is the second time we visit the thread node.
        // At this time, we also get back to the root of the subtree(pre).
        // As we have already traversed the left branches, we should now traverse
        // the root and the right branches.
        pre->right = NULL; // change this node back since we don't need this thread node anymore.
        // now we visit the right branches
        p = p->right;
      }
    }
  }
  return ans;
}


int main() {
  TreeNode n1(1);
  TreeNode n2(2);
  TreeNode n3(3);
  TreeNode n4(4);
  TreeNode n5(5);
  TreeNode n6(6);
  n1.left = &n2;
  n1.right = &n3;
  n2.left = &n4;
  n2.right = &n5;
  n4.right = &n6;
  for (auto v: inorder(&n1)) {
    cout << v << " ";
  }
  cout << endl;
  return 0;
}
