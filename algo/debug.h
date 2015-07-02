#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

template <class T>
void debugVec(const vector<T> &vec, std::ostream &os=std::cout) {
  for (int i = 0; i < vec.size(); i++) {
    os << vec[i] << " ";
  }
  os << std::endl;
}
