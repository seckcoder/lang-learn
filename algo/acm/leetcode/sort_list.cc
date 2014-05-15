// http://oj.leetcode.com/problems/sort-list/

// struct定义需要在提交的时候注释掉

#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;


struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};
void print_list(ListNode *p);

bool operator<=(const ListNode &n1, const ListNode &n2) {
  return n1.val < n2.val;
}

class Solution {
 public:
  ListNode *sortList(ListNode *head) {
    ListNode *tail = listTail(head);
    return mergesort(head, tail);
  }
  ListNode *listTail(ListNode *p) {
    if (p == NULL) {
      return p;
    } else {
      while (p->next != NULL) {
        p = p->next;
      }
      return p;
    }
  }
  ListNode *ListMiddle(ListNode *head, ListNode *tail) {
    // return the middle of h and t.
    // h != null, t != null, h != t
    int len = 0;
    for(ListNode *tmp = head; tmp != tail->next; tmp = tmp->next) {
      len += 1;
    }
    for(int i = 0; i < (len-1)/2; i++) {
      head = head->next;
    }
    return head;
  }
  ListNode *mergesort(ListNode *head, ListNode *tail) {
    if (head == NULL || tail == NULL) {
      return NULL;
    } else if (head == tail) {
      return head;
    } else {
      ListNode *middle = ListMiddle(head, tail);
      //cout << middle->val << endl;
      ListNode *tmp = middle->next;
      middle->next = NULL;
      /*assert(head == middle);
      assert(tmp == tail);*/
      head = mergesort(head, middle);
      tmp = mergesort(tmp, tail);
      return merge(head, middle, tmp, tail);
    }
  }
  ListNode *merge(ListNode *h1, ListNode *t1, ListNode *h2, ListNode *t2) {
    if (h1 == NULL) {
      //assert(t2->next == NULL);
      return h2;
    } else if (h2 == NULL) {
      //assert(t1->next == NULL);
      return h1;
    } else if ((*h1) <= (*h2)) {
      ListNode *tmp_head = merge(h1->next, t1, h2, t2);
      h1->next = tmp_head;
      return h1;
    } else {
      ListNode *tmp_head = merge(h1, t1, h2->next, t2);
      /*cout << tmp_head->val << endl;
      cout << h2->val << endl;*/
      h2->next = tmp_head;
      return h2;
    }
  }
};

void print_list(ListNode *p) {
  while (p != NULL) {
    cout << p->val << endl;
    p = p->next;
  }
}

int main(int argc, const char *argv[])
{
  ListNode n1(1);
  ListNode n2(2);
  ListNode n3(3);
  n1.next = &n2;
  n2.next = &n3;
  n3.next = NULL;
  Solution sol;
  //sol.sortList(&n1);
  print_list(sol.sortList(&n1));
  return 0;
}
