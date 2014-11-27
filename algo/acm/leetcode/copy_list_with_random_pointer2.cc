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

RandomListNode *deepCopy(RandomListNode *head) {
  if (head == NULL) return NULL;
  RandomListNode *copy_node = (RandomListNode *)malloc(sizeof(RandomListNode));
  copy_node->label = head->label;
  copy_node->next = deepCopy(head->next);
  copy_node->random = NULL;
  head->next = copy_node;
  return head;
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
  RandomListNode *copy = orig->next;
  orig->next = copy->next;
  copy->next = seperateList(copy->next);
  return copy;
}


class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
      RandomListNode *orig = deepCopy(head);
      updateRandom(orig);
      return seperateList(orig);
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
