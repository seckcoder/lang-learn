/**
 *  * Definition for binary tree
 *   * struct TreeNode {
 *    *     int val;
 *     *     TreeNode *left;
 *      *     TreeNode *right;
 *       *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 *        * };
 *         */

#include <cstdio>
#include <vector>
#include <deque>
#include <iostream>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode (int x) : val(x), left(NULL), right(NULL) {}
};

class BSTIterator {
  public:
    TreeNode *rt;
    vector<TreeNode*> trees;
    deque<int> xs;
    vector<int> xs_acc;
    BSTIterator(TreeNode *root) {
      rt = root;
      trees.push_back(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
      if (trees.empty() && xs.empty() && xs_acc.empty()) return false;
      if (trees.size() == 1 && trees[0] == NULL && xs.empty() && xs_acc.empty()) return false;
      return true;
    }

    /** @return the next smallest number */
    int next() {
      //preOrder();
      inOrder();
      int v = xs.front();
      xs.pop_front();
      return v;
    }
    void inOrder() {
      while (!trees.empty() && xs.empty()) {
        TreeNode *cur = trees.back();
        trees.pop_back();
        if (cur == NULL && xs_acc.empty()) {
          // pass
        } else if (cur == NULL) {
          xs.push_back(xs_acc.back());
          xs_acc.pop_back();
        } else {
          xs_acc.push_back(cur->val);
          trees.push_back(cur->right);
          trees.push_back(cur->left);
        }
      }
    }
};


int main() {
  TreeNode n1(1);
  TreeNode n2(2);
  TreeNode n3(3);
  n2.left = &n1;
  n2.right = &n3;
  BSTIterator i = BSTIterator(&n2);
  while (i.hasNext()) {
    cout << i.next() << endl;
  }
  return 0;
}

/**
 *  * Your BSTIterator will be called like this:
 *   * BSTIterator i = BSTIterator(root);
 *    * while (i.hasNext()) cout << i.next();
 *     */
