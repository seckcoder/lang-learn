#include <cstdlib>
#include <cassert>
#include <cstdio>

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
  ListNode *detectCycle(ListNode *head) {
    ListNode *h1 = head;
    ListNode *h2 = head;
    if (h1 != NULL) {
      h1->val = 0;
    }
    h1 = forward(h1, 1);
    h2 = forward(h2, 2);
    bool has_cycle = false;
    while (true) {
      if (h1 != NULL) {
        //printf("%d\n", h1->val);
        h1->val = 0; // init
      }
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
    if (!has_cycle) {
      return NULL;
    } else {
      ListNode *h3 = head;
      int meet_num = 0;
      while (meet_num < 2) {
        h3->val += 1;
        if (h3 == h1) {
          meet_num += 1;
        }
        h3 = h3->next;
      }
      h3 = head;
      while (true) {
        if (h3->val > 1) {
          return h3;
        }
        h3 = h3->next;
      }
      return NULL;
    }
  }
};

int main(void) {
  ListNode n1(3);
  ListNode n2(2);
  ListNode n3(0);
  ListNode n4(4);
  n1.next = &n2;
  n2.next = &n3;
  n3.next = &n4;
  n4.next = &n2;
  Solution sol;
  assert(sol.detectCycle(&n1) == &n2);
  return 0;
}
