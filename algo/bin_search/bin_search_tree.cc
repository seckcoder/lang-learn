#include <cstdlib>
#include <memory>


struct Node {
  Node *left, *right;
  int v;
};


Node *createNewNode(int v) {
  Node *pn = (Node *)malloc(sizeof(Node));
  pn->v = v;
  return pn;
}

// insert a value
Node *insert(Node *root, int v) {
  if (root == NULL) {
    return createNewNode(v);
  }
  if (v > root->v) {
    return insert(root->right, v);
  } else if (v < root->v) {
    return insert(root->left, v);
  } else {
    // no duplicate elements allowed in the tree
    return root;
  }
}

// query value v
Node *query(Node *root, int v) {
  if (root == NULL) {
    return NULL; // can't find
  }
  if (v > root->v) {
    return query(root->right, v);
  } else if (v < root->v) {
    return query(root->left, v);
  } else {
    return root;
  }
}

inline bool is_leaf(Node *root) {
  return (root->left == NULL && root->right == NULL);
}

void swap_value(Node *pn1, Node *pn2) {
  int tmp = pn1->v;
  pn1->v = pn2->v;
  pn2->v = tmp;
}

// delete node root, assert root is not null
Node *del(Node *root) {
  if (root->left == NULL && root->right == NULL) {
    free(root);
    return NULL;
  } else if (root->left == NULL) {
    Node *tmp = root->right;
    free(root);
    return tmp;
  } else if (root->right == NULL) {
    Node *tmp = root->left;
    free(root);
    return tmp;
  } else {
    if (root->left->v < root->right->v) {
      root->v = root->right->v;
      // swap_value(root, root->right);
      root->right = del(root->right);
      return root;
    } else if (root->left->v > root->right->v) {
      root->v = root->left->v;
      // swap_value(root, root->left);
      root->left = del(root->left);
      return root;
    } // assert no value in the tree is equal
  }
  return NULL; // make compiler happy
}

// delete v in the bin search tree. return the new root after deleting
Node *del(Node *root, int v) {
  if (root) {
    if (root->v == v) {
      del(root);
    } else if (root->v > v) {
      root->left = del(root->left, v);
    } else {
      root->right = del(root->right, v);
      return root;
    }
  } else {
    // maybe v not found
    return NULL;
  }
}

// query whether there exist a value within a range
bool query(Node *root, int left, int right) {
  if (root->v >= left && root->v <= right) {
    return true;
  } else if (root->v < left) {
    return query(root->right, left, right);
  } else if (root->v > right) {
    return query(root->left, left, right);
  }
}
