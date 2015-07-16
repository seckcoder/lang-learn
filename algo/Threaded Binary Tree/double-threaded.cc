
#include <iostream>
using namespace std;

/* Double threaded binary trees */



/* When the tree node is threaded, its left
 * branch will point to the predecessor while its right branch
 * will point to the sucessor.
 * 
 * Intution:
 * Threads are reference to the predecessors and successors of the node according to an inorder traversal.  
 * For in-order traversal, left nodes are the predecessor while
 * the right nodes are successor.
 */
struct TreeNode {
  int val;
  bool is_thread; 
  TreeNode *left, *right;
  TreeNode(int v): val(v), is_thread(false), left(NULL), right(NULL) {}
};


TreeNode *parent(TreeNode *p) {
  TreeNode *cur = p;
  /* If p is the right branch of the parent, then the parent is the
   * predecessor of p. So we try the left branches of p
   */
  for (;;) {
    if (cur->is_thread) {
      if (!cur->left || cur->left->right != p) break;
      else return cur->left;
    }
    cur = cur->left;
  }
  /* If p is the left branch of the parent, then the parent is the successor
   * of p. so we try the right branches of p
   */
  for (;;) {
    if (cur->is_thread) {
      if (!cur->right || cur->right->left != p) break;
      else return cur->right;
    }
    cur = cur->right;
  }
  /* If can't find, then we know for sure that p is the root of the tree */
  return NULL;
}
