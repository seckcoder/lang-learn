// http://oj.leetcode.com/problems/copy-list-with-random-pointer/

//#include <map>
#include <cstdlib>
#include <cstdio>

using namespace std;

typedef struct RandomListNode {
  int label;
  RandomListNode *next, *random;
  RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
} RandomListNode;


struct BTreeNode {
  RandomListNode *key;
  RandomListNode *val;
  BTreeNode *left, *right;
};

struct BTree {
  BTreeNode *root;
};


void init_btree(BTree *pt) {
  pt->root = NULL;
}

BTreeNode *create_node(RandomListNode *key, RandomListNode *val) {
  BTreeNode *pn = (BTreeNode *)malloc(sizeof(BTreeNode));
  pn->key = key;
  pn->val = val;
  pn->left = NULL;
  pn->right = NULL;
  return pn;
}

BTreeNode *insert1(BTreeNode *pn, RandomListNode *key, RandomListNode *val, BTreeNode **pp_ret_node) {
  if (pn == NULL) {
    *pp_ret_node = create_node(key, val);
    return *pp_ret_node;
  } else if (pn->key == key) {
    pn->val = val;
    *pp_ret_node = pn;
    return *pp_ret_node;
  } else if (pn->key < key) {
    // insert right
    pn->right = insert1(pn->right, key, val, pp_ret_node);
    return pn;
  } else {
    pn->left = insert1(pn->left, key, val, pp_ret_node);
    return pn;
  }
}

BTreeNode *insert(BTree *pt, RandomListNode *key, RandomListNode *val) {
  BTreeNode *ret_node;
  pt->root = insert1(pt->root, key, val, &ret_node);
  return ret_node;
}


BTreeNode *find1(BTreeNode *pnode, RandomListNode *key) {
  if (pnode == NULL) {
    return NULL;
  } else if (pnode->key == key) {
    return pnode;
  } else if (pnode->key < key) {
    return find1(pnode->right, key);
  } else {
    return find1(pnode->left, key);
  }
}

BTreeNode *find(BTree *pt, RandomListNode *key) {
  return find1(pt->root, key);
}

void free_tree_node(BTreeNode *pn) {
  if (pn != NULL) {
    free_tree_node(pn->left);
    free_tree_node(pn->right);
    free(pn);
  }
}

void free_tree(BTree *pt) {
  free_tree_node(pt->root);
}

//typedef map<RandomListNode *, RandomListNode *> node_map;

RandomListNode *deep_copy(RandomListNode *h, BTree *pt) {
  if (h == NULL) {
    return NULL;
  } else {
    RandomListNode *h_copy = (RandomListNode *)malloc(sizeof(RandomListNode));
    h_copy->label = h->label;
    h_copy->next = deep_copy(h->next, pt);
    h_copy->random = h->random;
    insert(pt, h, h_copy);
    //nmap.insert(std::pair<RandomListNode *, RandomListNode*>(h, h_copy));
    //printf("deep_copy: %d %d\n",h, h_copy);
    return h_copy;
  }
}

void update_random(RandomListNode *h, BTree *pt) {
  while (h != NULL) {
    if (h->random != NULL) {
      h->random = find(pt, h->random)->val;
    }
    h = h->next;
  }
}

class Solution {
 public:
  RandomListNode *copyRandomList(RandomListNode *head) {
    BTree t;
    init_btree(&t);
    RandomListNode *head_copy = deep_copy(head, &t);
    update_random(head_copy, &t);
    free_tree(&t);
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
