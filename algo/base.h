
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <cassert>
#include <stack>
#include <queue>
#include <utility>
#include <cstddef>
#include <algorithm>
#include <initializer_list>
#include <deque>
#include <sys/time.h>

using namespace std;
struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e): start(s), end(e) {}
};

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x): val(x), next(NULL) {}
};

static ListNode* nodesList(int n) {
  ListNode *prev = new ListNode(1);
  ListNode *head = prev;
  for (int i = 2; i <= n; i++) {
    ListNode *cur = new ListNode(i);
    prev->next = cur;
    prev = cur;
  }
  return head;
}

template <class T>
void printVec(const vector<T> &vec, char sep=' ') {
  for(auto v:vec) {
    cout << v << sep;
  }
  cout << endl;
}

template <class T>
void printVecOfVec(const vector<vector<T>> &vv) {
  for (auto v:vv) {
    for (auto x:v) {
      cout << x << " ";
    }
    cout << endl;
  }
  cout << endl;
}

template <class Key, class T>
void printVecOfPair(const vector<pair<Key, T>> &vv) {
    for (auto p:vv) {
        cout << p.first << " " << p.second << endl;
    }
    cout << endl;
}

static void printList(ListNode *head) {
  while (head) {
    cout << head->val << " ";
    head = head->next;
  }
  cout << endl;
}


struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x): val(x), left(NULL), right(NULL) {}
};


template <class TreeNode>
void printInOrder(TreeNode *root) {
  if (!root) return;
  printInOrder(root->left);
  cout << root->val << " ";
  printInOrder(root->right);
}


/*
 *
 * 0
 * |      \
 * 1      2
 * | \    | \
 * 3  4   5 6
 */
static TreeNode* randomTree() {
  vector<TreeNode *> ts;
  int n = 7;
  for (int i = 0; i < n; i++) {
    ts.push_back(new TreeNode(i));
  }
  ts[0]->left = ts[1];
  ts[0]->right = ts[2];
  ts[1]->left = ts[3];
  ts[1]->right = ts[4];
  ts[2]->left = ts[5];
  ts[2]->right = ts[6];
  return ts[0];
}


class TreeLinkNode {
  public:
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

template <class T, template<typename> class Col>
T max_elements(const Col<T> &vec) {
  return *std::max_element(vec.begin(), vec.end());
}


struct TreeNodeWithSize {
  int val;
  int size; // number of nodes in the tree
  TreeNodeWithSize *left;
  TreeNodeWithSize *right;
  TreeNodeWithSize(int x): val(x), left(NULL), right(NULL),size(1) {}
};


struct Point {
  int x;
  int y;
  Point(): x(0), y(0) {}
  Point(int a, int b): x(a), y(b) {}
};


struct UndirectedGraphNode {
  int label;
  vector<UndirectedGraphNode *> neighbors;
  UndirectedGraphNode(int x) : label(x) {};
};

static double wtime(void) {
    double          now_time;
    struct timeval  etstart;
    struct timezone tzp;

    if (gettimeofday(&etstart, &tzp) == -1)
        perror("Error: calling gettimeofday() not successful.\n");

    now_time = ((double)etstart.tv_sec) +              /* in seconds */
               ((double)etstart.tv_usec) / 1000000.0;  /* in microseconds */
    return now_time;
}
