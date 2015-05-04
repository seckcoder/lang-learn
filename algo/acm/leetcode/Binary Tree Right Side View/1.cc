/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> rightSideView(TreeNode *root) {
        vector<int> right_side_view;
        if (root == NULL) return right_side_view;
        vector<TreeNode *> stack;
        stack.push_back(root);
        while (!stack.empty()) {
            right_side_view.push_back(stack.back()->val);
            vector<TreeNode *> tmp;
            for (int i = 0; i < stack.size(); i++) {
                TreeNode *cur = stack[i];
                if (cur->left != NULL) {
                    tmp.push_back(cur->left);
                }
                if (cur->right != NULL) {
                    tmp.push_back(cur->right);
                }
            }
            stack = tmp;
        }
        return right_side_view;
    }
};
