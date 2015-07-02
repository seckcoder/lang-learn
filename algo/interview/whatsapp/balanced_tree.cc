#include <vector>
#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

// construct a balanced tree from a sorted list


struct BinSearchNode {
  int v;
  BinSearchNode *left, *right;
  BinSearchNode(int hv): v(hv), left(NULL), right(NULL) {}
};


inline int completeTreePartition(int n) {
  int k = int(log2((n-1)/2+1));
  int rest_elems = n - 2*((1<<k)-1)-1;
  return (1<<k)-1 + std::min(rest_elems, (1<<k));
}

BinSearchNode *recur(const vector<int> &vec, int p, int r) {
  if (p > r) return NULL;
  int m = p+completeTreePartition(r-p+1);
  BinSearchNode *root = new BinSearchNode(vec[m]);
  root->left = recur(vec, p, m-1);
  root->right = recur(vec, m+1, r);
  return root;
}

BinSearchNode *convert(const vector<int> &vec) {
  return recur(vec, 0, vec.size()-1);
}

void printTree(const BinSearchNode *root) {
  std::vector<const BinSearchNode*> que;
  que.push_back(root);
  while (!que.empty()) {
    for (int i = 0; i < que.size(); i++) {
      if (que[i]) {
        cout << que[i]->v << " ";
      } else {
        cout << "- ";
      }
    }
    cout << endl;
    std::vector<const BinSearchNode*> tmp;
    for (int i = 0; i < que.size(); i++) {
      if (que[i]) {
        tmp.push_back(que[i]->left);
        tmp.push_back(que[i]->right);
      }
    }
    que.resize(tmp.size());
    std::copy(tmp.begin(), tmp.end(), que.begin());
  }
}

int main() {
  vector<int> vec = {1,2,3,4,5,6,7,8};
  printTree(convert(vec));
  return 0;
}
