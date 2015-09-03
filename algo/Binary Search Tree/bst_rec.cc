/* A recursive implementation of bst */

#include "../base.h"

void inorder(TreeNode *root) {
  if (root) {
    inorder(root->left);
    cout << root->val << " " ;
    inorder(root->right);
  }
}

TreeNode *tnode_insert(TreeNode *root, int val) {
  if (root) {
    if (root->val < val) {
      root->right = tnode_insert(root->right, val);
    } else if (root->val > val) {
      root->left = tnode_insert(root->left, val);
    }
  } else {
    root = new TreeNode(val);
  }
  return root;
}

/*
 * Basic Idea:
 *  find node, erase it's predecessor/successor. Then continue with
 *  the predecessor/successor
 * */
TreeNode *tnode_erase(TreeNode *root, int key) {
  if (!root) return NULL;
  if (key < root->val) {
    root->left = tnode_erase(root->left, key);
  } else if (key > root->val) {
    root->right = tnode_erase(root->right, key);
  } else {
    if (!root->left && !root->right) {
      delete root;
      root = NULL;
    } else if (root->left) {
      /* Here, as we have got the predecessor, why don't we directly delete
       * this node?
       * 
       * It's possible that predecessor is not a leaf node. At this time,
       * we need to continue the delete process
       */
      TreeNode *predecessor = root->left;
      while (predecessor->right) predecessor = predecessor->right;
      root->val = predecessor->val;
      root->left = tnode_erase(root->left, predecessor->val);
    } else if (root->right) {
      TreeNode *successor = root->right;
      while (successor->left) successor = successor->left;
      root->val = successor->val;
      root->right = tnode_erase(root->right, successor->val);
    }
  }
  return root;
}


bool tnode_range_query(TreeNode *root, int r1, int r2) {
  if (root) {
    if (root->val >= r1 && root->val <= r2) return true;
    else if (root->val < r1) {
      return tnode_range_query(root->right, r1, r2);
    } else {
      return tnode_range_query(root->left, r1, r2);
    }
  } else {
    return false;
  }
}

int tnode_height(TreeNode *r) {
  if (!r) return 0;
  return std::max(tnode_height(r->left),tnode_height(r->right))+1;
}

class BinTree {
  public:
    TreeNode *root;
    BinTree() {
      root = NULL;
    }
    void insert(int val) {
      root = tnode_insert(root, val);
    }
    void erase(int val) {
      root = tnode_erase(root, val);
    }
    // [r1,r2]
    bool range_query(int r1, int r2) const {
      return tnode_range_query(root, r1,r2);
    }
    int height() const {
      return tnode_height(root);
    }
};

ostream& operator<<(ostream &os, const BinTree &bt) {
  std::queue<std::pair<TreeNode*,int>> q;
  int h = bt.height();
  int level = -1;
  q.push(make_pair(bt.root, 0));
  while (!q.empty()) {
    TreeNode *cur = q.front().first;
    int cur_level = q.front().second;
    if (cur_level != level) {
      level = cur_level;
      os << "\n";
    } else {
      os << "\t";
    }
    if (!cur) {
      os << "_|_";
    } else {
      os << cur->val;
      q.push(make_pair(cur->left, cur_level+1));
      q.push(make_pair(cur->right, cur_level+1));
    }
    q.pop();
  }
  os << endl;
  return os;
}

int main() {

  {
    BinTree bt;

    for (auto v: {20,1,25,24,30,28,27,26}) {
      bt.insert(v);
    }
    inorder(bt.root);
    cout << endl;
    bt.erase(20);
    inorder(bt.root);
    cout << endl;
  }

  {
    BinTree bt;
    for (auto v: {50,30,20,40,70,60,80}) {
      bt.insert(v);
    }
    inorder(bt.root); cout << endl;
    bt.erase(20);
    inorder(bt.root); cout << endl;
    bt.erase(30);
    inorder(bt.root); cout << endl;
    bt.erase(50);
    inorder(bt.root); cout << endl;
  }

  {
    BinTree bt;
    for (auto v: {40}) {
      bt.insert(v);
    }
    bt.erase(40);
    inorder(bt.root); cout << endl;
  }

  return 0;
}
