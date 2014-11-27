/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
#include "base.h"
 
 class Range {
public:
     int min, max;
     Range():min(1), max(0) {}
     bool valid() const { return min <= max; }
     void set(int hmin, int hmax) {
         min = hmin;
         max = hmax;
     }
 };
class Solution {
public:
    bool isValidBST(TreeNode *root) {
        if (root == NULL) return true;
        Range r;
        return recur(root, r);
    }
    bool recur(TreeNode *root, Range &r) {
        if (root->left == NULL && root->right == NULL) {
            r.set(root->val, root->val);
            return true;
        } else {
            Range left, right;
            if (root->left && !recur(root->left, left)) return false;
            if (root->right && !recur(root->right, right)) return false;
            if (left.valid()) {
                if (left.max >= root->val) return false;
                r.set(std::min(left.min, root->val), std::max(left.max, root->val));
            }
            if (right.valid()) {
                if (right.min <= root->val) return false;
                r.set(std::min(r.min, right.min), std::max(r.max, right.max));
            }
            return true;
        }
    }
};

int main(int argc, const char *argv[])
{
  TreeNode
  Solution sol;
  sol.isValidBST();
  return 0;
}
