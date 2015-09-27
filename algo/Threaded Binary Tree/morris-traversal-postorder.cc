
#include "../base.h"



/*
 *
 *  The print_reverse function is just amazing! 
 *  The sentinel node is used to print root
 */

void reverseRightPath(TreeNode *r)
{
  TreeNode *prev = NULL;
  while (r)
  {
    TreeNode *tmp = r->right;
    r->right = prev;
    prev = r;
    r = tmp;
  }
}

void printRightPath(TreeNode *from, TreeNode *to)
{
  reverseRightPath(from);
  for (TreeNode *cur = to; cur ; cur = cur->right)
  {
    cout << cur->val << " ";
  }
  reverseRightPath(to);
}


void postOrder(TreeNode *root)
{
  TreeNode sentinel(0);
  sentinel.left = root;
  TreeNode *cur = &sentinel, *prev = NULL;

  while (cur)
  {
    if (!cur->left)
    {
      cur = cur->right;
    } else
    {
      prev = cur->left;
      while (prev->right && prev->right != cur)
      {
        prev = prev->right;
      }
      if (!prev->right)
      {
        prev->right = cur;
        cur = cur->left;
      } else
      {
        prev->right = NULL;
        printRightPath(cur->left, prev);
        cur = cur->right;
      }
    }
  }
}

int main()
{
  TreeNode n1(1);
  TreeNode n2(2);
  TreeNode n3(3);
  TreeNode n4(4);
  TreeNode n5(5);
  TreeNode n6(6);
  TreeNode n7(7);
  TreeNode n8(8);
  TreeNode n9(9);
  n9.left = &n5;
  n9.right = &n8;
  n5.left = &n1;
  n5.right = &n4;
  n4.left = &n2;
  n4.right = &n3;
  n8.right = &n7;
  n7.left = &n6;
  postOrder(&n9);
  return 0;
}
