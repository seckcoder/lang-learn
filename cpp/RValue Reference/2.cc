

#include "../base.h"


class ArrayWrapper {
  public:
    ArrayWrapper()
      :_p_vals(new int[64])
      ,_size(64) {
        cout << "haha" << endl;
      }
    /* move constructor */
    ArrayWrapper(ArrayWrapper&& other)
      :_p_vals(other._p_vals)
      ,_size(other._size) {
        other._p_vals = NULL;
        other._size = 0;
    }

    ~ArrayWrapper() {
      delete [] _p_vals;
    }
    
  private:
    int *_p_vals;
    int _size;
};

void f(ArrayWrapper a) {
}

int main() {
  f(ArrayWrapper());
  return 0;
}
