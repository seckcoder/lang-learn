

/* A BinTree implementation */
class BinTreeNode {
    public:
        int val;
        BinTreeNode *left, *right;
        BinTreeNode(int x):val(x), left(NULL), right(NULL) {}
};

class BinTree {
    public:
        BinTreeNode *root;
        BinTree() {
            root = NULL;
        }
        void insert(int v) {
            BinTreeNode **cur = &root;
            while (*cur) {
                if ((*cur)->val == v) return;
                else if ((*cur)->val < v) cur = &((*cur)->right);
                else cur = &((*cur)->left);
            }
            *cur = new BinTreeNode(v);
        }
        void erase(int v) {
            BinTreeNode **cur = &root;
            while (*cur) {
                if ((*cur)->val == v) erase(cur);
                else if ((*cur)->val < v) cur = &((*cur)->right);
                else cur = &((*cur)->left);
            }
        }
        void erase(BinTreeNode **cur) {
            /* As long as cur has non-null right node,
             * we swap values of cur and right node
             */
            while ((*cur)->right) {
                std::swap((*cur)->val, (*cur)->right->val);
                cur = &((*cur)->right);
            }
            /* if cur doesn't have right node, we set left node as the new cur */
            delete *cur;
            *cur = (*cur)->left;
        }
        bool search(int p, int r) {
            BinTreeNode *cur = root;
            while (cur) {
                if (p <= cur->val && cur->val <= r) return true;
                else if (p > cur->val) cur = cur->right;
                else if (r < cur->val) cur = cur->left;
            }
            return false;
        }
};
