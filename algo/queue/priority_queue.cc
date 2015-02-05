
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
}


#define LC(i) (((i)<<1)+1)
#define RC(i) (((i)<<1)+2)
// the parent function is unsafe for index starting from 0.
#define PARENT(i) (((i)-1)>>1)

// Notes:
//  heap[root] maynot be a heap
void maxHeapify(vector<Job> &heap, uint32_t root) {
  uint32_t max_index = root,
           left_child = LC(root),
           right_child = RC(root);
  // We don't need to check whether root is in range for this function.
  // It coincidently matches our need.
  if (left_child < heap.size() && heap[max_index].priority < heap[left_child].priority) {
    max_index = left_child;
  }
  if (right_child < heap.size() && heap[max_index].priority < heap[right_child].priority) {
    max_index = right_child;
  }
  if (root != max_index) {
    std::swap(heap[root], heap[max_index]);
    maxHeapify(heap, max_index);
  }
}

// Notes
//   We build from the first non-leaf node since all leaf nodes are heap
void buildHeap(vector<Job> &heap) {
  if (heap.size() > 1) {
    for (int i = PARENT(heap.size()-1);
        i >= 0; i--) {
      maxHeapify(heap, i);
    }
  }
}

// insert a job to the heap
void insert(vector<Job> &heap, const Job &job) {
  heap.push_back(job);
  // When the job size is 1, the integer(-1) can't be represented in uint32_t!
  if (heap.size() > 1) maxHeapify(heap, PARENT(heap.size()-1));
}

// get the job with max priority
Job getMaxPriority(const vector<Job> &heap) {
  assert(heap.size() > 0);
  return heap[0];
}

// remove the job with max priority
void removeMaxPriority(vector<Job> &heap) {
  assert(heap.size() > 0);
  std::swap(heap.front(), heap.back());
  heap.resize(heap.size()-1);
  maxHeapify(heap, 0);
}

int main() {
  vector<Job> queue;
  insert(queue, Job(2));
  insert(queue, Job(1));
  insert(queue, Job(3));
  cout << getMaxPriority(queue) << endl;
  return 0;
}
