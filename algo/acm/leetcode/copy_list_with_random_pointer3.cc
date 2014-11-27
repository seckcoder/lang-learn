#include <cstdio>
#include <cstdlib>
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */

struct RandomListNode {
  int label;
  RandomListNode *next, *random;
  RandomListNode(int x): label(x), next(NULL), random(NULL) {}
};

void deepCopy(RandomListNode *head) {
  while (head != NULL) {
    RandomListNode *copy = (RandomListNode *)malloc(sizeof(RandomListNode));
    copy->random = NULL;
    copy->label = head->label;
    copy->next = head->next;
    head->next = copy;
    head = copy->next;
  }
}

void updateRandom(RandomListNode *orig) {
  while (orig != NULL) {
    RandomListNode *copy = orig->next;
    if (orig->random != NULL) copy->random = orig->random->next;
    orig = copy->next;
  }
}

RandomListNode *seperateList(RandomListNode *orig) {
  if (orig == NULL) return NULL;
  RandomListNode *copy_head = orig->next;
  while (orig != NULL) {
    RandomListNode *copy = orig->next;
    orig->next = copy->next;
    orig = copy->next;
    if (orig != NULL) copy->next = orig->next;
  }
  return copy_head;
}


class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
      deepCopy(head);
      updateRandom(head);
      return seperateList(head);
    }
};


void print_list(RandomListNode *l) {
  while (l != NULL) {
    printf("%d %d  |  ", l, l->random);
    printf("%d ", l->label);
    if (l->random != NULL) {
      printf("%d ", l->random->label);
    }
    printf("\n");
    l = l->next;
  }
}


int main(int argc, const char *argv[])
{
  RandomListNode n1(-1);
  n1.random = &n1;
  Solution sol;
  printf("%d\n", &n1);
  print_list(sol.copyRandomList(&n1));
  return 0;
}
