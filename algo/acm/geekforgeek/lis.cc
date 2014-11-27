// http://www.geeksforgeeks.org/largest-independent-set-problem/

#include <cstdio>
#include <cstdlib>
#include <algorithm>

struct Node {
 public:
  int data;
  struct Node *left, *right;
};


int max(int a, int b, int c, int d) {
  return std::max(std::max(std::max(a,b), c), d);
}


namespace recur {

void lisSub(Node *root, int &ir, int &nir) {
  if (root == NULL) {
    ir = 0;
    nir = 0;
  } else {
    int subIr[2];
    int subNir[2];
    lisSub(root->left, subIr[0], subNir[0]);
    lisSub(root->right, subIr[1], subNir[1]);
    ir = subNir[0] + subNir[1] + 1;
    nir = max(subIr[0] + subNir[1],
              subIr[0] + subIr[1],
              subNir[0] + subNir[1],
              subNir[1] + subIr[1]);
  }
}


int lis(Node *root) {
  int ir, nir;
  lisSub(root, ir, nir);
  return std::max(ir, nir);
}

}


// A utility function to create a node
struct Node* newNode( int data )
{
  struct Node* temp = (struct Node *) malloc( sizeof(struct Node) );
  temp->data = data;
  temp->left = temp->right = NULL;
  return temp;
}

// Driver program to test above functions
int main()
{
  // Let us construct the tree given in the above diagram
  struct Node *root         = newNode(20);
  root->left                = newNode(8);
  root->left->left          = newNode(4);
  root->left->right         = newNode(12);
  root->left->right->left   = newNode(10);
  root->left->right->right  = newNode(14);
  root->right               = newNode(22);
  root->right->right        = newNode(25);

  printf ("Size of the Largest Independent Set is %d ", recur::lis(root));

  return 0;
}
