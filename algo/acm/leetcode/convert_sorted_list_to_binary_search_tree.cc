/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include <iostream>
#include <cassert>

using namespace std;
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  ListNode *walk(ListNode *p, int n) {
    for (int i = 1; i <= n; i++) {
      p = p->next;
    }
    return p;
  }
  int listLength(ListNode *p) {
    int len = 0;
    while (p != NULL) {
      len += 1;
      p = p->next;
    }
    return len;
  }
  TreeNode *sortedListToBST(ListNode *head) {
    if (head == NULL) return NULL;
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->left = root->right = NULL;
    if (head->next == NULL) {
      root->val = head->val;
      return root;
    }
    // len >= 2
    int len = listLength(head);
    ListNode *mid_prev = walk(head, len/2-1);
    ListNode *mid = mid_prev->next;
    assert(mid != NULL);
    mid_prev->next = NULL;
    root->val = mid->val;
    root->left = sortedListToBST(head);
    root->right = sortedListToBST(mid->next);
    return root;
  }
};


void printTree(TreeNode *r) {
  if (r != NULL) {
    cout << r->val << " ";
    printTree(r->left);
    printTree(r->right);
  }
}

int main(int argc, const char *argv[])
{
  ListNode l1(1);
  ListNode l2(2);
  ListNode l3(3);
  /*l1.next = &l2;
  l2.next = &l3;*/
  Solution sol;
  printTree(sol.sortedListToBST(&l1));
  return 0;
}
