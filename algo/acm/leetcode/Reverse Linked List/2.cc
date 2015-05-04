/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *moveFront(ListNode *start, int step) {
        // assert start won't move to NULL
        for (int i = 1; i <= step; i++) {
            start = start->next;
        }
        return start;
    }
    ListNode *removeNext(ListNode *cur) {
        // assert cur != NULL, cur->next != NULL
        ListNode *next = cur->next;
        cur->next = next->next;
        return next;
    }
    void insertNext(ListNode *cur, ListNode *next) {
        next->next = cur->next;
        cur->next = next;
    }
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        // The key point of this problem is the usage of sentinel.
        ListNode tmp_node(0);
        ListNode *sentinel = &tmp_node;
        sentinel->next = head;
        ListNode *begin = moveFront(sentinel, m-1);
        ListNode *tail = moveFront(sentinel, n);
        while (begin->next != tail) {        
            ListNode *next = removeNext(begin);
            insertNext(tail, next);
        }
        return sentinel->next;
    }
};
