#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;



struct Node {
  int data;
  Node *left, *right;
};

// A utility function to create a new tree node
struct Node* newNode(int data)
{
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}


namespace iter1 {
void preorder(const Node *root) {
  const Node *p = root;

  vector<const Node *> parents;

  while (p != NULL || parents.size() != 0) {
    while (p != NULL) {
      cout << p->data << endl;
      parents.push_back(p);
      p = p->left;
    }

    p = parents.back();
    parents.pop_back();
    p = p->right;
  }
}
}

namespace iter2 {


void preorder(const Node *p) {
  vector<const Node *> rights;
  while (p != NULL || rights.size() != 0) {
    cout << p->data  << endl;
    if (p->right != NULL) {
      rights.push_back(p->right);
    }

    if (p->left != NULL) {
      p = p->left;
    } else if (rights.size() != 0) {
      p = rights.back();
      rights.pop_back();
    } else {
      p = NULL;
    }
  }
}

};


// Driver program to test above functions
int main()
{
    // Let us construct the tree shown in above figure
    struct Node* root = NULL;
    root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
 
    iter1::preorder(root);
    cout << endl;
    iter2::preorder(root);
 
    return 0;
}
