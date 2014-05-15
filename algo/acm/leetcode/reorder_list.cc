#include <vector>

using std::vector;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

ListNode *reorder(vector<ListNode *> &vec, int start, int end) {
  if (start == end) {
    vec[start]->next = NULL;
    return vec[start];
  } else if (start > end) {
    return NULL;
  } else {
    vec[start]->next = vec[end];
    vec[end]->next = reorder(vec, start+1, end-1);
    return vec[start];
  }
}

void fill_vec(vector<ListNode*> &vec, ListNode *h) {
  vec.clear();
  while (h != NULL) {
    vec.push_back(h);
    h = h->next;
  }
}

class Solution {
 public:
  void reorderList(ListNode *head) {
    std::vector<ListNode*> vec;
    fill_vec(vec, head);
    int len = vec.size();
    reorder(vec, 0, len-1);
  }
};

void print_list(ListNode *l) {
  while (l != NULL) {
    printf("%d ", l->val);
    l = l->next;
  }
}

int main(int argc, const char *argv[])
{
  ListNode n1(1);
  /*ListNode n2(2);
  ListNode n3(3);
  ListNode n4(4);
  n1.next = &n2;
  n2.next = &n3;
  n3.next = &n4;*/
  Solution sol;
  //sol.reorderList(&n1);
  sol.reorderList(NULL);
  print_list(&n1);
  return 0;
}
