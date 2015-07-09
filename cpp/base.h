#include <iostream>
#include <string>
#include <vector>
using namespace std;


static void printDelim(const char c = '-', int count = 50) {
    for (int i = 0; i < count; i++) {
        cout << c;
    }
    cout << endl;
}


template <class T>
static void printVec(vector<T> &vec) {
  for (int i = 0; i < vec.size(); i++) {
    cout << vec[i] << " ";
  }
}
