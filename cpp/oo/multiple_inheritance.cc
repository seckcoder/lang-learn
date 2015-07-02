#include <iostream>
using namespace std;


class Object1 {
  public:
    virtual void m1() {
      cout << "object1:m1" << endl;
    }
    void m2() {
    }
};

class Object2 {
  public:
    virtual void m1() {
      cout << "object2:m1" << endl;
    }
    void m2() {
    }
};

class C1: public Object1, public Object2 {
  public:
    virtual void m1() {
      cout << "C1:m1" << endl;
    }
};

int main() {
  C1* c = new C1();
  c->m1();
  // c->m2(); you can't call m2. It will generate an error.
  delete c;
  return 0;
}
