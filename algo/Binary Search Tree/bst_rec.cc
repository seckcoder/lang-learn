
/* A recursive implementation of bst */

class TreeNode {
  public:
    TreeNode *left;
    TreeNode *right;
    int val;
    TreeNode(int v): val(v), left(NULL),right(NULL) {}
};

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

// assert root is not null
TreeNode *tnode_remove(TreeNode *root) {
  //if (!root) cout << "heheh" << endl;
  if (root->left == NULL && root->right == NULL) {
    delete(root);
    return NULL;
  } else if (root->left == NULL) {
    TreeNode *tmp = root->right;
    delete root;
    return tmp;
  } else if (root->right == NULL) {
    TreeNode *tmp = root->left;
    delete root;
    return tmp;
  } else {
    if (root->left->val < root->right->val) {
      root->val = root->right->val;
      root->right = tnode_remove(root->right);
      return root;
    } else {
      root->val = root->left->val;
      root->left = tnode_remove(root->left);
      return root;
    }
  }
}

TreeNode *tnode_remove(TreeNode *root, int val) {
  if (root) {
    if (root->val == val) {
      // cout << "yoyu" << endl;
      return tnode_remove(root);
    } else if (root->val < val) {
      root->right = tnode_remove(root->right, val);
      return root;
    } else {
      root->left = tnode_remove(root->left, val);
      return root;
    }
  } else {
    return NULL;
  }
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

class BinTree {
  public:
    TreeNode *root;
    BinTree() {
      root = NULL;
    }
    void insert(int val) {
      root = tnode_insert(root, val);
    }
    void remove(int val) {
      root = tnode_remove(root, val);
    }
    // [r1,r2]
    bool range_query(int r1, int r2) {
      return tnode_range_query(root, r1,r2);
    }
};


