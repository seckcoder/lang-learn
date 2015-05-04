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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode tmp(0);
        ListNode *sentinel = &tmp;
        sentinel->next = head;
        
        ListNode *prev = sentinel;
        while (prev->next != NULL) {
            ListNode *cur = prev->next;
            if (cur->val == val) {
                removeNextNode(prev);
            } else {
                prev = cur;
            }
        }
        return sentinel->next;
    }
    /* assert next node is not NULL */
    
    void removeNextNode (ListNode *prev) {
        ListNode *cur = prev->next;
        prev->next = cur->next;
        free(cur);
    }
};
