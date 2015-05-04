/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <iostream>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode *swapPairs(ListNode *head) {
        ListNode tmpNode(0);
        tmpNode.next = head;
        // a fake node, with next being the head.
        ListNode *sentinel = &tmpNode;
        ListNode *cur = sentinel;
        while (atLeastTwoNodes(cur)) {
            swapPair(cur);
            cur = walk(cur, 2);
        }
        return sentinel->next;
    }
    // check the list contains at least two nodes. Otherwise, we don't need to swap
    bool atLeastTwoNodes(ListNode *sentinel) {
        // if (sentinel == NULL) return false;
        if (sentinel->next == NULL) return false;
        if (sentinel->next->next == NULL) return false;
        return true;
    }
    
    // 把结点往前移step步
    // assert the list has at least step length
    ListNode *walk(ListNode *cur, int step) {
        for (int i = 1; i <= step; i++) {
            cur = cur->next;
        }
        return cur;
    }
    void swapPair(ListNode *prev) {
        ListNode *node1 = prev->next;
        ListNode *node2 = node1->next;
        prev->next = node2;
        //node2->next = node1;
        node1->next = node2->next;
        node2->next = node1;
    }
};


int main() {
  ListNode n1(1);
  ListNode n2(2);
  ListNode n3(3);
  ListNode n4(4);
  n1.next = &n2;
  n2.next = &n3;
  n3.next = &n4;
  Solution sol;
  
  ListNode *p = sol.swapPairs(&n1);;
  while (p != NULL) {
    cout << p->val << endl;
    p = p->next;
  }
  return 0;
}
