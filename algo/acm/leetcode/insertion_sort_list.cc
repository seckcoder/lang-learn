// http://oj.leetcode.com/problems/insertion-sort-list/

/**
 * Definition for singly-linked list.
 * Struct定义需要在提交的时候注释掉
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <iostream>
#include <cstdlib>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

void print_list(ListNode *p);
void insert_next(ListNode *pos, ListNode *to_insert) {
  ListNode *tmp = pos->next;
  pos->next = to_insert;
  to_insert->next = tmp;
}

ListNode *insert_sort(ListNode *head, ListNode *to_insert) {
  if (to_insert == NULL) {
    return head;
  } else {
    //cout << to_insert->val << endl;
    ListNode *next_to_insert = to_insert->next;
    ListNode *insert_pos;
    ListNode *new_head = NULL;
    //cout << "here" << endl;
    if (to_insert->val < head->val) {
      //cout << "there " << to_insert->val << endl;
      // insert in front of head
      to_insert->next = head;
      new_head = to_insert;
    } else {
      for(ListNode *tmp = head; tmp != NULL; tmp = tmp->next) {
        if (tmp->val <= to_insert->val) {
          insert_pos = tmp;
        } else {
          break;
        }
      }
      insert_next(insert_pos, to_insert);
      new_head = head;
    }
    return insert_sort(new_head, next_to_insert);
  }
}

class Solution {
 public:
  ListNode *insertionSortList(ListNode *head) {
    if (head == NULL) {
      return head;
    } else {
      ListNode *tmp = head->next;
      head->next = NULL;
      return insert_sort(head, tmp);
    }
  }
};

void print_list(ListNode *p) {
  while (p != NULL) {
    cout << p->val << endl;
    p = p->next;
  }
}
int main(int argc, const char *argv[]) {
  Solution sol;
  ListNode n1(2);
  ListNode n2(3);
  ListNode n3(1);
  n1.next = &n2;
  n2.next = &n3;
  print_list(sol.insertionSortList(&n1));
}
