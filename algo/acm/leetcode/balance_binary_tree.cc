/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#define ISBALANCEDTREE(left_depth, right_depth) (std::abs((left_depth) - (right_depth)) <= 1)

class Solution {
 public:
  bool isBalanced(TreeNode *root) {
    if (root == NULL) return true;
    int left_depth, right_depth;
    return recur(root->left, left_depth) &&
        recur(root->right, right_depth) &&
        ISBALANCEDTREE(left_depth, right_depth);
  }
  bool recur(TreeNode *p, int &depth) {
    if (p == NULL) {
      depth = 0
          return true;
    } else {
      int left_depth, right_depth;
      if (recur(p->left, left_depth) && recur(p->right, right_depth) && ISBALANCEDTREE(left_depth, right_depth)) {
        depth = std::max(left_depth, right_depth) + 1;
        return true;
      } else {
        return false;
      }
    }

  }
};
