
#include "../base.h"


void preOrder(const TreeNode *root, vector<int> &trav) {
  vector<const TreeNode *> ts;
  trav.clear();
  ts.push_back(root); 
  while (!ts.empty()) {
    const TreeNode *r = ts.back();
    ts.pop_back();
    if (r) {
      ts.push_back(r->right);
      ts.push_back(r->left);
      trav.push_back(r->val);
    }
  }
}

class PreOrderIter {
  public:
    vector<const TreeNode *> ts;
    const TreeNode *tmp;
    PreOrderIter(TreeNode *root_):ts(1, root_) {
    }
    bool hasNext() {
      while (!ts.empty()) {
        const TreeNode *r = ts.back();
        ts.pop_back();
        if (r) {
          ts.push_back(r->right);
          ts.push_back(r->left);
          tmp = r;
          return true;
        }
      }
      return false;
    }
    const TreeNode *next() {
      return tmp;
    }
};
void preOrderRev(const TreeNode *root, vector<int> &trav) {
  vector<const TreeNode *> ts;
  trav.clear();
  ts.push_back(root);
  while (!ts.empty()) {
    const TreeNode *r = ts.back();
    ts.pop_back();
    if (r) {
      ts.push_back(r->left);
      ts.push_back(r->right);
      trav.push_back(r->val);
    }
  }
}

void inOrder(const TreeNode *root, vector<int> &trav) {
  vector<const TreeNode*> ts;
  vector<int> acc;
  ts.push_back(root);
  while (!ts.empty()) {
    const TreeNode *r = ts.back();
    ts.pop_back();
    if (r) {
      ts.push_back(r->right);
      ts.push_back(r->left);
      acc.push_back(r->val);
    } else if (!acc.empty()) {
      trav.push_back(acc.back());
      acc.pop_back();
    } 
  }
}
void inOrderRev(const TreeNode *root, vector<int> &trav) {
  vector<const TreeNode*> ts;
  vector<int> acc;
  ts.push_back(root);
  while (!ts.empty()) {
    const TreeNode *r = ts.back();
    ts.pop_back();
    if (r) {
      ts.push_back(r->left);
      ts.push_back(r->right);
      acc.push_back(r->val);
    } else if (!acc.empty()) {
      trav.push_back(acc.back());
      acc.pop_back();
    }
  }
}
class InOrderIter {
  public:
    vector<const TreeNode *> ts;
    vector<const TreeNode*> acc;
    const TreeNode *tmp;
    InOrderIter(TreeNode *root_):ts(1, root_), acc() {
    }
    bool hasNext() {
      while (!ts.empty()) {
        const TreeNode *r = ts.back();
        ts.pop_back();
        if (r) {
          ts.push_back(r->right);
          ts.push_back(r->left);
          acc.push_back(r);
        } else if (!acc.empty()) {
          tmp = acc.back();
          acc.pop_back();
          return true;
        }
      }
      return false;
    }
    const TreeNode *next() {
      return tmp;
    }
};

void postOrder(const TreeNode *root, vector<int> &trav) {
  vector<const TreeNode*> ts;
  ts.push_back(root);
  while (!ts.empty()) {
    const TreeNode *r = ts.back();
    if (r) {
      ts.push_back(r->left);
      ts.push_back(r->right);
      trav.push_back(r->val);
    }
  }
  std::reverse(trav.begin(), trav.end());
}
void postOrder1(const TreeNode *root, vector<int> &trav) {
  vector<const TreeNode*> ts;
  if (!root) return;
  
  do {
    while (root) {
      if (root->right)
        ts.push_back(root->right);
      ts.push_back(root);
      root = root->left;
    }
    root = ts.back();
    if (root->right && ts.back() == root->right) {
      ts.pop_back();
      ts.push_back(root);
      root = root->right;
    } else {
      trav.push_back(root->val);
      root = NULL;
    }
  } while (!ts.empty());
}
void postOrderRev(const TreeNode *root, vector<int> &trav) {
}
class PostOrderIter {
};

template <class Iter>
void exhaustIter(Iter iter) {
  while (iter.hasNext()) {
    const TreeNode *cur = iter.next();
    cout << cur->val << " ";
  }
  cout << endl;
}

int main() {
  TreeNode *r = randomTree();
  exhaustIter(PreOrderIter(r));
  cout << endl;
  vector<int> trav;
  preOrder(r, trav);
  printVec(trav);
  trav.clear();
  preOrderRev(r, trav);
  printVec(trav);
  trav.clear();
  inOrder(r, trav);
  printVec(trav);
  trav.clear();
  inOrderRev(r, trav);
  printVec(trav);
  trav.clear();
  exhaustIter(InOrderIter(r));
  return 0;
}
