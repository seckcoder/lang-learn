/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include <iostream>
#include <vector>
using namespace std;
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* Method1: Copy nodes */
class Solution1 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<TreeNode *> nodes;
        nodes.push_back(root);
        vector<vector<int>> level_order_trav;
        if (root == NULL) return level_order_trav;
        while (!nodes.empty()) {
            vector<TreeNode *> tmp;
            vector<int> trav;
            for (int i = 0; i < nodes.size(); i++) {
                trav.push_back(nodes[i]->val);
                if (nodes[i]->left) tmp.push_back(nodes[i]->left);
                if (nodes[i]->right) tmp.push_back(nodes[i]->right);
            }
            level_order_trav.push_back(trav);
            /* Note: before copying, we need to make sure
             * 'nodes' contains enough memory
             */
            nodes.resize(tmp.size());
            vector<TreeNode *>::iterator end_of_nodes = std::copy(tmp.begin(), tmp.end(), nodes.begin());
        }
        return level_order_trav;
    }
};

/* Method2 : without copy nodes */
class Solution {
  public:
    vector<vector<int>> levelOrder(TreeNode* root) {
      vector<vector<int>> level_order_trav;
      if (root == NULL) return level_order_trav;
      vector<TreeNode *> nodes;
      nodes.push_back(root);
      int start_idx = 0;
      int cur_level_nodes_count = 1;
      
      while (start_idx < nodes.size()) {
        vector<int> cur_level_trav;
        int next_level_nodes_count = 0;
        for (int i = start_idx; i < start_idx + cur_level_nodes_count; i++) {
          cur_level_trav.push_back(nodes[i]->val);
          if (nodes[i]->left) {
            nodes.push_back(nodes[i]->left);
            next_level_nodes_count += 1;
          }
          if (nodes[i]->right) {
            nodes.push_back(nodes[i]->right);
            next_level_nodes_count += 1;
          }
        }
        level_order_trav.push_back(cur_level_trav);
        start_idx += cur_level_nodes_count;
        cur_level_nodes_count = next_level_nodes_count;
      }
      return level_order_trav;
    }
};

int main()
{
  TreeNode n1(1);
  TreeNode n2(2);
  TreeNode n3(3);
  n1.left = &n2;
  n1.right = &n3;
  Solution sol;
  sol.levelOrder(&n1);
  return 0;
}
