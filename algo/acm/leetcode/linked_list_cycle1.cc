#include <cstdlib>

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

ListNode *forward(ListNode *l, int step) {
  while (step > 0 && l != NULL) {
    l = l->next;
    step -= 1;
  }
  return l;
}

class Solution {
 public:
  bool hasCycle(ListNode *head) {
    ListNode *h1 = head;
    ListNode *h2 = head;
    h1 = forward(h1, 1);
    h2 = forward(h2, 2);
    bool has_cycle = false;
    while (true) {
      if (h1 == NULL && h2 == NULL) {
        has_cycle = false;
        break;
      } else if (h1 == NULL || h2 == NULL) {
        has_cycle = false;
        break;
      } else if (h1 == h2) {
        has_cycle = true;
        break;
      } else {
        h1 = forward(h1, 1);
        h2 = forward(h2, 2);
      }
    }
    return has_cycle;
  }
};
