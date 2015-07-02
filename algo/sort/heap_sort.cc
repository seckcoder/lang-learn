
#include <iostream>
#include <vector>

using namespace std;


#define LC(i) ((i)<<1)
#define RC(i) (((i)<<1)+1)

template <class T>
void maxHeapify(T *vec, int heap_size, int root) {
  int max_i = root,
      lc = LC(root),
      rc = RC(root);

  if (lc <= heap_size && vec[lc] > vec[max_i]) {
    max_i = lc;
  }
  if (rc <= heap_size && vec[rc] > vec[max_i]) {
    max_i = rc;
  }
  if (max_i != root) {
    std::swap(vec[root], vec[max_i]);
    maxHeapify(vec, heap_size, max_i);
  }
}

template <class T>
void buildHeap(T *vec, int n) {
  for (int i = n/2; i >= 1; i--) {
    maxHeapify(vec, n, i);
  }
}

template <class T>
void heapSort(T *vec, int n) {
  buildHeap(vec, n);
  int heap_size = n;
  for (int i = n; i >= 2; i--) {
    std::swap(vec[i], vec[1]);
    heap_size -= 1;
    maxHeapify(vec, heap_size, 1);
  }
}


int main() {
  int vec[] = {-1, 1,2,3,0,4};
  heapSort(vec,5);
  for (int i = 1; i <= 5; i++) {
    cout << vec[i] << " ";
  }
  cout << endl;
  return 0;
}
