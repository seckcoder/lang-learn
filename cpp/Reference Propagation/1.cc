

#include <cassert>
#include <cstdlib>

class TreeNode {
    public:
        int val;
        TreeNode *left, *right;
        TreeNode(int v) :val(v) {}
};

class Tree {
    public:
        TreeNode *r;
        Tree():r(NULL) {}
        void insert(int v) {
        }
};


int main() {
    TreeNode *r = NULL;
    TreeNode *&cur = r;
    cur = new TreeNode(4);
    assert( r != NULL  && r->val == 4);
    return 0;
}
