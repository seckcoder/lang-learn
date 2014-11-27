
class Solution {
 public:
 
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
      int n = listLength(head);
      return recur(&head, n);
  }
  TreeNode *recur(ListNode **ph, int n) {
      if (n == 0) return NULL;
      
      TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
      root->left = recur(ph, (n>>1));
      *ph = (*ph)->next;
      root->val = (*ph)->val;
      root->right = recur(ph, n-(n>>1)-1);
      return root;
  }
};
