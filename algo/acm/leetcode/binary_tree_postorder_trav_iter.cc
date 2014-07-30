#include <vector>
#include <iostream>

using namespace std;


struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  vector<int> postorderTraversal(TreeNode *root) {
    if (root == NULL) {
      return vector<int>();
    } else {
      vector<int> left = postorderTraversal(root->left);
      vector<int> right = postorderTraversal(root->right);
      left.insert(left.end(), right.begin(), right.end());
      left.insert(left.end(), root->val);
      return left;
    }
  }
};

void print_vector(vector<int> v) {
  for(int i = 0; i < v.size(); i++) {
    cout << v[i] << endl;
  }
}

int main(int argc, const char *argv[])
{
  Solution sol;
  TreeNode n1(1);
  TreeNode n2(2);
  TreeNode n3(3);
  n1.right = &n2;
  n2.left = &n3;
  sol.postorderTraversal(&n1);
  //print_vector(sol.postorderTraversal(&n1));
  return 0;
}