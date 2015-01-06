#include <iostream>
#include <vector>
#include <deque>

using namespace std;

class BinTree {
  public:
    BinTree() { v = 0; left = right = NULL; }
    BinTree(int hv) { v = hv; left = right = NULL; }
    int v;
    BinTree *left;
    BinTree *right;
};


void preOrder(BinTree *rt, deque<int> &xs) {
  vector<BinTree *> stack;
  stack.push_back(rt);
  while (!stack.empty()) {
    BinTree *cur = stack.back();
    stack.pop_back();
    if (cur != NULL) {
      xs.push_back(cur -> v);
      stack.push_back(cur->right);
      stack.push_back(cur->left);
    }
  }
}

void inOrder(BinTree *rt, deque<int> &xs) {
  vector<BinTree *> stack;
  stack.push_back(rt);
  vector<int> acc_xs;

  while (!stack.empty()) {
    BinTree *cur = stack.back();
    stack.pop_back();
    if (cur == NULL && acc_xs.empty()) {
    } else if (cur == NULL) {
      int x = acc_xs.back();
      acc_xs.pop_back();
      xs.push_back(x);
    } else {
      acc_xs.push_back(cur->v);
      stack.push_back(cur->right);
      stack.push_back(cur->left);
    }
  }
}


void postOrder(BinTree *rt, deque<int> &xs) {
  vector<BinTree *> stack;
  stack.push_back(rt);

  while (!stack.empty()) {
    BinTree *cur = stack.back();
    stack.pop_back();
    if (cur != NULL) {
      xs.push_front(cur->v);
      stack.push_back(cur->left);
      stack.push_back(cur->right);
    }
  }
}


int main() {
  BinTree n1(1);
  BinTree n2(2);
  BinTree n3(3);
  n2.left = &n1;
  n2.right = &n3;

  cout << "pre order:" << endl;
  {
    deque<int> res;
    preOrder(&n2, res);
    for (int i = 0; i < res.size(); i++) {
      cout << res[i] << endl;
    }
  }
  
  cout << "in order: " << endl;
  {
    deque<int> res;
    inOrder(&n2, res);
    for (int i = 0; i < res.size(); i++) {
      cout << res[i] << endl;
    }
  }
  
  cout << "post order: " << endl;
  {
    deque<int> res;
    postOrder(&n2, res);
    for (int i = 0; i < res.size(); i++) {
      cout << res[i] << endl;
    }
  }
  return 0;
}
