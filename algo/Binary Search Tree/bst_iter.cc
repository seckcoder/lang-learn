
#include "../base.h"

/* A BinTree implementation */
class BinTreeNode {
  public:
    int val;
    BinTreeNode *left, *right;
    BinTreeNode(int x):val(x), left(NULL), right(NULL) {}
    void searchInRange(int p, int r, vector<int> &res) {
      cout << "val: " << val << endl;
      if (r > val && right) right->searchInRange(p, r, res);
      if (p < val && left) left->searchInRange(p, r, res);
      if (p <= val && val <= r) res.push_back(val);
    }
    bool isLeaf() const {
      return left == NULL && right == NULL;
    }
};

class BinTree {
  public:
    BinTreeNode *root;
    BinTree() {
      root = NULL;
    }
    void insert(int v) {
      BinTreeNode **cur = search_(v);
      if (!*cur) {
        *cur = new BinTreeNode(v);
      }
    }
    void erase(int v) {
      BinTreeNode **cur_node = search_(v);
      if (*cur_node) erase(cur_node);
    }
    void erase(BinTreeNode **cur) {
      /* The same idea as the recursive version */
      while (!(*cur)->isLeaf()) {
        if ((*cur)->left) {
          BinTreeNode **predecessor = &(*cur)->left;
          while ((*predecessor)->right) {
            predecessor = &(*predecessor)->right;
          }
          std::swap((*cur)->val, (*predecessor)->val);
          cur = predecessor;
        } else if ((*cur)->right) {
          BinTreeNode **successor = &(*cur)->right;
          while ((*successor)->left) {
            successor = &(*successor)->left;
          }
          std::swap((*cur)->val, (*successor)->val);
          cur = successor;
        }
      }
      BinTreeNode *tmp = (*cur);
      *cur = NULL; // set as null.
      delete tmp;
    }
    /* range query */
    bool search(int p, int r) {
      BinTreeNode *cur = root;
      while (cur) {
        if (p <= cur->val && cur->val <= r) return true;
        else if (p > cur->val) cur = cur->right;
        else if (r < cur->val) cur = cur->left;
      }
      return false;
    }
    BinTreeNode *search(int v) {
      BinTreeNode *cur = root;
      while (cur) {
        if (v == cur->val) return cur;
        else if (v < cur->val) cur = cur->left;
        else cur = cur->right;
      }
      return NULL;
    }
    /* a const reference copy */
    const BinTreeNode *search(int v) const {
      BinTreeNode *cur = root;
      while (cur) {
        if (v == cur->val) return cur;
        else if (v < cur->val) cur = cur->left;
        else cur = cur->right;
      }
      return NULL;
    }
    /* a function for internal usage.
     * return the pointer to the node
     * Note I didn't use reference here since that makes the
     * code a little bit difficult to understand.
     */
    BinTreeNode **search_(int v) {
      BinTreeNode **cur = &root;
      while (*cur) {
        if (v == (*cur)->val) return cur;
        else if (v < (*cur)->val) cur = &(*cur)->left;
        else cur = &(*cur)->right;
      }
      return cur;
    }

    /* search all those values in range */
    vector<int> searchInRange(int p, int r) {
      vector<int> res;
      if (root) root->searchInRange(p,r,res);
      return res;
    }
};

ostream& operator<<(ostream &os, const BinTreeNode &node) {
  if (node.left) os << *(node.left);
  os << node.val << " ";
  if (node.right) os << *(node.right);
  return os;
}

ostream& operator<<(ostream &os, const BinTree &bt) {
  if (bt.root) os << *(bt.root);
  return os;
}


int main() {

  {
    BinTree bt;

    for (auto v: {20,1,25,24,30,28,27,26}) {
      bt.insert(v);
    }
    cout << bt << endl;
    bt.erase(20);
    cout << bt << endl;
    printVec(bt.searchInRange(24, 27));
  }
  {
    BinTree bt;
    for (auto v: {40}) {
      bt.insert(v);
    }
    bt.erase(40);
    cout << bt << endl;
  }
  {
    BinTree bt;
    for (auto v: {50,30,20,40,70,60,80}) {
      bt.insert(v);
    }
    cout << bt << endl;
    bt.erase(20);
    cout << bt << endl;
    bt.erase(30);
    cout << bt << endl;
    bt.erase(50);
    cout << bt << endl;
    bt.erase(40);
    cout << bt << endl;
    bt.erase(80);
    cout << bt << endl;
    bt.erase(40);
    cout << bt << endl;
    bt.erase(70);
    cout << bt << endl;
    bt.erase(60);
    cout << bt << endl;
  }
  return 0;
}
