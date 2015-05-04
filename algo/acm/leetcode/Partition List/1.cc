#include <iostream>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x): val(x), next(NULL) {}
};

// We can think of this question in Haskell, which is much easier.
// See 1.hs: partition_tail_rec
class Solution {
public:
    ListNode *partition(ListNode *head, int x) {
        ListNode tmp_node1(0), tmp_node2(0);
        tmp_node1.next = NULL;
        ListNode *sentinel_of_lt = &tmp_node1;
        ListNode *tail_of_lt = sentinel_of_lt;
        tmp_node2.next = head;
        ListNode *sentinel_of_ge = &tmp_node2;
        ListNode *tail_of_ge = sentinel_of_ge;
        // we construct two lists.
        // The first list consists of values less than x
        // The second list consists of values greater or equal than x
        
        while (tail_of_ge && tail_of_ge->next) {
            ListNode *cur = tail_of_ge->next;
            if (cur->val < x) {
                // move cur to the tail of less than
                cur = removeNext(tail_of_ge);
                insertNext(tail_of_lt, cur);
                tail_of_lt = tail_of_lt->next;
            } else {
                tail_of_ge = tail_of_ge->next;
            }
        }
        tail_of_lt->next = sentinel_of_ge->next;
        return sentinel_of_lt->next;
    }
    // remove next node of cur and return the removed node.
    // assert cur->next != NULL
    
    ListNode *removeNext(ListNode *cur) {
        ListNode *next = cur->next;
        cur->next = next->next;
        return next;
    }
    // insert next as the next node of cur
    // assert cur != null, next != null
    void insertNext(ListNode *cur, ListNode *next) {
        next->next = cur->next;
        cur->next = next;
    }
};


int main() {
  ListNode n1(1);
  ListNode *head = Solution().partition(&n1, 2);
  while (head != NULL) {
    cout << head->val << " ";
    head = head->next;
  }
  cout << endl;
  return 0;
}
