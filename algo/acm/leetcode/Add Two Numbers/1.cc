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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        int carry = 0;
        ListNode tmpNode(0);
        ListNode *sentinel = &tmpNode;
        ListNode *prev = sentinel;
        while (l1 != NULL && l2 != NULL) {
            int sum = l1->val + l2->val + carry;
            ListNode *cur = new ListNode(sum % 10);
            carry = sum / 10;
            prev->next = cur;
            prev = cur;
            l1 = l1->next;
            l2 = l2->next;
        }
        ListNode *prest = NULL;
        if (l1 != NULL) prest = l1;
        if (l2 != NULL) prest = l2;
        while (prest != NULL) {
            int sum = prest->val + carry;
            ListNode *cur = new ListNode(sum % 10);
            carry = sum / 10;
            prev->next = cur;
            prev = cur;
            prest = prest->next;
        }
        if (carry != 0) {
            // assert (carry < 10);
            
            ListNode *cur = new ListNode(carry);
            prev->next = cur;
        }
        return sentinel->next;
    }
};
