// http://learn.hackerearth.com/tutorial/trees/19/iterative-tree-traversals/
//
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

struct Node {
  int data;
  Node *left, *right;
};


void recur(Node *root) {
  if (root == NULL) return;
  recur(root->left);
  recur(root->right);
  printf("%d ", root->data);
}

void iterative1(Node *root) {
  if (root == NULL) return;
  vector<Node *> rec_stack;
  vector<Node *> post_stack;
  rec_stack.push_back(root);
  while (!rec_stack.empty()) {
    Node *top = rec_stack.back();
    rec_stack.pop_back();
    post_stack.push_back(top);
    if (top->left != NULL) {
      rec_stack.push_back(top->left);
    }
    if (top->right != NULL) {
      rec_stack.push_back(top->right);
    }
  }

  while (!post_stack.empty()) {
    printf("%d ", post_stack.back()->data);
    post_stack.pop_back();
  }
}

void iterative2(const Node *root) {
  const Node *p = root;
  const Node *prev = NULL;

  vector<const Node *> parents;
  do {
    while (p != NULL) {
      parents.push_back(p);
      p = p->left;
    }
    while (p == NULL && parents.size() > 0) {
      p = parents.back();
      if (p->right == NULL || p->right == prev) {
        cout << p->data << endl;
        prev = p;
        p = NULL;
        parents.pop_back();
      } else {
        p = p->right;
      }
    }
  } while (parents.size() != 0);
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
 
    iterative2(root);
 
    return 0;
}
