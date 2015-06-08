#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};


/**
 *
 * KeyPoint:
 *
 * 1. Given a list, we can reverse it in linear time with constant space
 * 2. For this question, we want to concatenate consecutive groups after
 * reverse the list in each group. So we need to know the previous group
 * when reversing the current group.
 */


/**
 * NodeGroup: [begin, end] is the list of nodes in the group
 */
class NodeGroup {
public:
    int node_count; /* actual number of nodes */
    ListNode *begin, *end;
    int k; /* the number of nodes needed to form a compact group */
    NodeGroup(ListNode *head, int k_) :k(k_){
        begin = head;
        node_count = 0;
        for (int i = 1; i < k && head; i++) {
            node_count += 1;
            head = head->next;
        }
        if (head) node_count += 1;
        end = head;
    }
    /* reverse all nodes in the list group*/
    void reverse() {
        ListNode *next_group_begin = end->next;
        end->next = NULL;
        ListNode *prev = begin;
        ListNode *cur = begin->next;
        while (cur) {
            ListNode *next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        swapBeginEnd();
        end->next = next_group_begin;
    }
    /* swap begin and end */
    void swapBeginEnd() {
        ListNode *tmp = begin;
        begin = end;
        end = tmp;
    }
    /* When node_count < k, it means the group is not compact. So we
     * can't reverse it
     */
    bool isCompact() const {
        return node_count == k;
    }
};

class Solution {
    public:
        ListNode *reverseKGroup(ListNode* head, int k) {
            if (k < 2) return head;
            /* we need to record the first group so that
             * we can return the head of the new list
             */
            NodeGroup first_group(head, k);
            if (first_group.isCompact()) {
                first_group.reverse();
                NodeGroup prev_group = first_group;
                // cout << prev_group << endl;
                while (true) {
                    NodeGroup next_group(prev_group.end->next, k);
                    if (!next_group.isCompact()) break;
                    next_group.reverse();
                    // cout << next_group << endl;

                    /** concatenate the two groups of nodes
                     */
                    prev_group.end->next = next_group.begin;
                    prev_group = next_group;
                } 
            }
            return first_group.begin;
        }
};

std::ostream &operator<<(ostream &os, const NodeGroup &ng) {
    os << ng.begin->val << " " << ng.end->val << " ";
    if (ng.end->next) {
        os << ng.end->next->val;
    }
    return os;
}

void printList(ListNode *head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    vector<ListNode> vec;
    int n = 5;
    for (int i = 1; i <= n; i++) {
        vec.push_back(ListNode(i));
    }
    for (int i = 0; i < n-1; i++) {
        vec[i].next = &vec[i+1];
    }
    printList(&vec[0]);
    ListNode *head = Solution().reverseKGroup(&vec[0], 6);
    printList(head);
    return 0;
}
