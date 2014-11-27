#include <iostream>
using namespace std;

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
 public:
  int maxPathSum(TreeNode *root) {
    if (root == NULL) return 0;
    int max_sum = INT_MIN;
    recur(root, max_sum);
    return max_sum;
  }
  // max_sum store the maximum sum
  // Return the max sum end at point p
  int recur(TreeNode *p, int &max_sum) {
    if (p == NULL) return 0;
    int left_max = std::max(recur(p->left, max_sum), 0),
        right_max = std::max(recur(p->right, max_sum), 0);
    max_sum = std::max(max_sum,
                       left_max + right_max + p->val);
    return std::max(left_max + p->val,
                    right_max + p->val);
  }
};


int main(int argc, const char *argv[])
{
  /*TreeNode p1(1), p2(2), p3(3);
  p1.left = &p2;
  p1.right = &p3;*/
  TreeNode p1(-1);
  TreeNode p2(-2);
  p1.left = &p2;
  Solution sol;
  cout << sol.maxPathSum(&p1) << endl;
  return 0;
}
