
// this version start its index from 1


#include <cstdlib>
#include <vector>
#include <cassert>
#include <iostream>
using namespace std;

class Job {
  public:
    int priority;
    Job():priority(0) {}
    Job(int hp) :priority(hp) {}
};

ostream &operator<<(ostream &os, const Job &job) {
  os << job.priority;
  return os;
};


#define M 10000

#define LC(i) ((i)<<1)
#define RC(i) (((i)<<1)+1)
#define PARENT(i) ((i)>>1)
class Heap {
  public:
    Heap() : len(0) {};
    Job &operator[] (uint32_t n) {
      return heap[n];
    }

    const Job &operator[] (uint32_t n) const {
      return heap[n];
    }
    uint32_t size() const {
      return len;
    }

    void maxHeapify(uint32_t root) {
      uint32_t left_c = LC(root),
               right_c = RC(root),
               max_index = root;
      if (left_c <= len && heap[max_index].priority < heap[left_c].priority) {
        max_index = left_c;
      }
      if (right_c <= len && heap[max_index].priority < heap[right_c].priority) {
        max_index = right_c;
      }
      if (max_index != root) {
        std::swap(heap[max_index], heap[root]);
        maxHeapify(max_index);
      }
    }

    void push(const Job &job) {
      len += 1;
      heap[len] = job;
      maxHeapify(PARENT(len));
    }

    void pop() {
      assert(len >= 1);
      std::swap(heap[1], heap[len]);
      len -= 1;
      maxHeapify(1);
    }
    
    const Job &top() const {
      return heap[1];
    }

    void buildHeap() {
      for (int i = PARENT(len); i >= 1; i--) {
        maxHeapify(i);
      }
    }

  private:
    Job heap[M];
    uint32_t len; // heap len. Note the index starts from 1
};

int main() {
  Heap heap;
  heap.push(2);
  heap.push(1);
  heap.push(3);
  cout << heap.top() << endl;
  return 0;
}
