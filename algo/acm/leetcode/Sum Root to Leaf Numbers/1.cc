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
    int sumNumbers(TreeNode *root) {
        int sumv = 0;
        string acc;
        sumNumbers(root, acc, sumv);
        return sumv;
    }
    bool isLeaf(TreeNode *root) {
        if (root->left == NULL && root->right == NULL) return true;
        return false;
    }
    void sumNumbers(TreeNode *root, string &acc, int &sumv) {
        if (root == NULL) return; // not a leaf, just a broken branch
        if (isLeaf(root)) {
            acc.push_back('0' + root->val);
            addV(acc, sumv);
            acc.pop_back();
            return;
        }
        acc.push_back('0' + root->val);
        sumNumbers(root->left, acc, sumv);
        sumNumbers(root->right, acc, sumv);
        acc.pop_back();
    }
    void addV(const string &acc, int &sumv) {
        if (acc.empty()) return;
        int i = 0;
        while (i < acc.length() && acc[i] == '0') ++i;
        int tmpv = 0;
        while (i < acc.length()) {
            tmpv = tmpv * 10 + (acc[i] - '0');
            i += 1;
        }
        sumv += tmpv;
    }
};
