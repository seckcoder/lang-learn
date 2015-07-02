/*
 * Heap with the help of std::make_heap
 *
 */


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> PriorityQueue;


// This class is mainly used to provide namespace and Uniform Compare constraint
template <class Compare, class DataType>
class Heap {
  public:
    Heap() {}
    void push(vector<DataType> &heap, const DataType &v) {
      heap.push_back(v);
      std::push_heap(heap.begin(), heap.end());
    }
    void push(vector<DataType> &heap, const DataType &v, Compare comp) {
      heap.push_back(v);
      std::push_heap(heap.begin(), heap.end(), comp);
    }
    DataType top(const vector<DataType> &heap) const {
      return heap[0];
    }
    void pop(vector<DataType> &heap) {
      std::pop_heap(heap.begin(), heap.end());
      heap.pop_back();
    }
    void pop(vector<DataType> &heap, Compare comp) {
      std::pop_heap(heap.begin(), heap.end(), comp);
      heap.pop_back();
    }
};

void push(PriorityQueue &que, int v) {
  que.push_back(v);
  std::push_heap(que.begin(), que.end());
}

int top(const PriorityQueue &que) {
  return que[0];
}

void pop(PriorityQueue &que) {
  std::pop_heap(que.begin(), que.end());
  que.pop_back();
}


int main() {
  PriorityQueue que;
  Heap<std::less<int>,int> heap;
  heap.push(que, 2);
  heap.push(que, 1);
  heap.push(que, 3);
  cout << heap.top(que) << endl;
  heap.pop(que);
  cout << heap.top(que) << endl;
  return 0;
}
