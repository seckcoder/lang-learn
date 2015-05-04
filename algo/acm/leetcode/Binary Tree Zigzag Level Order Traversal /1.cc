/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
enum Dir {LEFT_RIGHT, RIGHT_LEFT};
class Solution {
public:
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        vector<vector<int>> traversal;
        if (root == NULL) return traversal;
        vector<TreeNode *> stack;
        stack.push_back(root);
        Dir dir = LEFT_RIGHT;
        
        while (!stack.empty()) {
            if (dir == LEFT_RIGHT) {
                traverse(stack.begin(), stack.end(), traversal);
                dir = RIGHT_LEFT;
            } else if (dir == RIGHT_LEFT) {
                traverse(stack.rbegin(), stack.rend(), traversal);
                dir = LEFT_RIGHT;
            }
            vector<TreeNode *>tmp;
            for (int i = 0; i < stack.size(); i++) {
                if (stack[i]->left != NULL) {
                    tmp.push_back(stack[i]->left);
                }
                if (stack[i]->right != NULL) {
                    tmp.push_back(stack[i]->right);
                }
            }
            stack = tmp;
        }
        return traversal;
    }
    template <class ITER>
    void traverse(ITER begin, ITER end, vector<vector<int>> &traversal) {
        vector<int> tmp_vec;
        for (ITER it = begin; it != end; it++) {
            tmp_vec.push_back((*it)->val);
        }
        traversal.push_back(tmp_vec);
    }
};
