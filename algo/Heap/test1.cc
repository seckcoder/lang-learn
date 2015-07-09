
#include "heap.h"

#include <iostream>
using namespace std;


int main() {
    Heap<int, std::greater<int>> heap;
    for (auto v: {100, 99, 9, 91,82, 8,7, 80}) {
        heap.insert(v);
    }
    for (int i = 1; i < heap.vec.size(); i++) cout << heap.vec[i] << " ";
    cout << endl;
    heap.erase(8);
    for (int i = 1; i < heap.vec.size(); i++) cout << heap.vec[i] << " ";
    cout << endl;

    /* you can see that the heap is not in valid state if you don't run bottom-up
     * in the erase function
     * */

    return 0;
}
