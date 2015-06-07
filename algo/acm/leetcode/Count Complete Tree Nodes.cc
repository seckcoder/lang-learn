
#include <queue>
#include <cstdlib>
#include <iostream>
#include <cstdio>
using namespace std;


/**
 * Key Idea: For complete binary tree, there are two cases
 *
 * 1. Left is full tree and right is complete tree
 * 2. Right is full tree and left is complete tree.
 *
 * Note, it's easy to calculate the number of nodes for full tree.
 *
 */

struct TreeNode {

    int val;

    TreeNode *left;

    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}

};


#define pow2(x) ((1<<(x)))

inline int getHeight(TreeNode *root) {
    int h = 0;
    while (root) {
        h += 1;
        root = root->left;
    }
    return h;
}

class Solution {
    public:
        int countNodes(TreeNode* root) {
            if (root == NULL) return 0;
            int left_h = getHeight(root->left);
            int right_h = getHeight(root->right);
            if (left_h == right_h) {
                // left is a full bin tree
                return pow2(left_h) + countNodes(root->right);
            } else {
                // left is a complete bin tree, right is a full bin tree
                return pow2(right_h) + countNodes(root->left);
            }
        }
};

int main() {
    TreeNode n1(1);
    TreeNode n2(2);
    TreeNode n3(3);
    TreeNode n4(4);
    TreeNode n5(5);
    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n5;
    printf("%d\n", Solution().countNodes(&n1));
    return 0;
}
