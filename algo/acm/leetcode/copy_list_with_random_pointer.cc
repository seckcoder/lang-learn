// http://oj.leetcode.com/problems/copy-list-with-random-pointer/

#include <map>
#include <cstdlib>

using namespace std;

typedef struct RandomListNode {
  int label;
  RandomListNode *next, *random;
  RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
} RandomListNode;


typedef map<RandomListNode *, RandomListNode *> node_map;

RandomListNode *deep_copy(RandomListNode *h, node_map &nmap) {
  if (h == NULL) {
    return NULL;
  } else {
    RandomListNode *h_copy = (RandomListNode *)malloc(sizeof(RandomListNode));
    h_copy->label = h->label;
    h_copy->next = deep_copy(h->next, nmap);
    h_copy->random = h->random;
    nmap.insert(std::pair<RandomListNode *, RandomListNode*>(h, h_copy));
    //printf("deep_copy: %d %d\n",h, h_copy);
    return h_copy;
  }
}

void update_random(RandomListNode *h, const node_map &nmap) {
  while (h != NULL) {
    if (h->random != NULL) {
      h->random = nmap.find(h->random)->second;
    }
    h = h->next;
  }
}

class Solution {
 public:
  RandomListNode *copyRandomList(RandomListNode *head) {
    node_map nmap;
    RandomListNode *head_copy = deep_copy(head, nmap);
    update_random(head_copy, nmap);
    return head_copy;
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
