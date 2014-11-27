#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;



struct Node {
  int data;
  Node *left, *right;
};



namespace iter1 {
void inorder(const Node *root) {
  const Node *p = root;

  vector<const Node *> parents;

  while (p != NULL || parents.size() != 0) {
    while (p != NULL) {
      parents.push_back(p);
      p = p->left;
    }

    p = parents.back();
    parents.pop_back();
    cout << p->data << endl;

    p = p->right;
  }

}
}


// A utility function to create a new tree node
struct Node* newNode(int data)
{
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

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
 
    iter1::inorder(root);
 
    return 0;
}
