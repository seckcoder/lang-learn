#include <iostream>
using namespace std;


class Object {
};


class C1: public Object {
  public:
    C1() {}
    void m1 () {
      this->m2();
    }
    void m2 () {
      cout << "c1:m2" << endl;
    }
};

class C2: public C1 {
public:
  void m1() {
    cout << "c2:m1" << endl;
  }
  void m2() {
    cout << "c2:m2" << endl;
  }
  void m3() {
    C1::m1();
  }
};

class C3 : public C2 {
public:
  void m1() {
    cout << "c3:m1" << endl;
  }
  void m2() {
    cout << "c3:m2" << endl;
  }
};


int main() {
  C3 *c3 = new C3();
  c3->m3();
  delete c3;
  return 0;
}
