/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include "base.h"
#include <iostream>
#include <deque>
using namespace std;
 
typedef std::deque<TreeNode *>::const_iterator const_iter;
#define val(it) ((*(it))->val)
#define leftptr(it) ((*(it))->left)
#define rightptr(it) ((*(it))->right)

class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        if (root == NULL) return true;
        std::deque<TreeNode *> deq;
        deq.push_back(root);
        while (!deq.empty()) {
            const_iter begin = deq.begin(), back = deq.end() - 1;
            cout << "here4" << endl;
            while (begin <= back) {
                cout << "here1" << endl;
                if (*begin == NULL && *back == NULL) {
                  // pass
                } else if (*begin == NULL || *back == NULL) {
                  return false;
                } else if (val(begin) != val(back)) {
                  return false;
                }
                begin++;
                back--;
            }
            begin = deq.begin();
            const_iter end = deq.end();
            while (begin != end) {
                cout << "here2" << endl;
                if (*begin != NULL) {
                    deq.push_back(leftptr(begin));
                    deq.push_back(rightptr(begin));
                }
                begin++;
                deq.pop_front();
            }
            cout << "here3" << endl;
        }
        return true;
    }
};

int main(int argc, const char *argv[])
{
  TreeNode t(1);
  Solution sol;
  sol.isSymmetric(&t);
  return 0;
}
