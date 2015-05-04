#include <vector>
#include <iostream>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> inorder;
        vector<int> acc_stack;
        vector<TreeNode*> tree_stack;
        
        tree_stack.push_back(root);
        
        while (!tree_stack.empty()) {
            TreeNode *cur = tree_stack.back();
            tree_stack.pop_back();
            if (cur == NULL && acc_stack.empty()) {
                // pass
            } else if (cur == NULL) {
                inorder.push_back(acc_stack.back());
                acc_stack.pop_back();
            } else {
                acc_stack.push_back(cur->val);
                tree_stack.push_back(cur->right);
                tree_stack.push_back(cur->left);
            }
        }
        return inorder;
    }
};


int main() {
  Solution sol;
  TreeNode n1(1);
  TreeNode n2(2);
  TreeNode n3(3);
  n2.left = &n1;
  n2.right = &n3;
  vector<int> vec = sol.inorderTraversal(&n2);
  for (int i = 0; i < vec.size(); i++) {
    cout << vec[i] << endl;
  }
  return 0;
}
