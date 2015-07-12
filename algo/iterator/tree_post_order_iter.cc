
#include "../base.h"

/* post order traversal is more complex than pre order and in order traversal.
 */

/* one stack method
 * Key idea:
 *  We define:
 *    visiting a node means when we first encounter a node.
 *    traversing a node means when we add its value to the result vector.
 *
 *  So the key idea is we need to record the previous `traversed` node.
 *  1. If the current node's right branch is null, then we need to traverse the current
 *  node.
 *  2. If the previous traversed node is current node's right branch, then we know
 *  we should traverse the current node.
 *  Also, we need a stack to record the `visited` nodes.
 * */
vector<int> postOrder1(TreeNode *root) {
  vector<int> res;
  stack<TreeNode*> st;
  TreeNode *pre = NULL, *p = root;
  
  /* p: a new node we are gonna visit
   * st: a stack of nodes that we have visited their left branches
   * pre: previous node that we have traversed their value(include in res)
   */
  while (p || !st.empty()) { /* as long as we have a new node to visit, or a stack of nodes to visit their right branch and traverse their value, we continue */
    if (p) {  /* for a new node to visit, we directly visit it's left branch */
      st.push(p);
      p = p->left;
    } else {
      p = st.top(); /* no new node to visit, we pop a node whose left branch has been visited */
      if (p->right && p->right != pre) { /* p has a right branch and it's right branch hasn't been traversed */
        p = p->right; /* we need to visit right */
      } else {
        /* otherwise, either p doesn't have a right branch or it's right branch has been traversed.
         * At this time, we could traverse the node p
         */
        res.push_back(p->val);
        pre = p; /* update previous traversed node */
        st.pop(); /* we don't need the traversed nodes any more */
        p = NULL; /* For the next step, we will try to traverse the parent of p. So we directly set it as null so that we could traverse its parent*/
      }
    }
  }
  return res;
}
