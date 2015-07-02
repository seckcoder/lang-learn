#include <cstdio>

class L {
  public:
    int m;
};

class A:public L {
};
class B:public L {

};
class C:public A, public B{
  public:
    int f() {
      return A::m;
    }
};

int main() {
  C c;
  printf("%d\n", c.f());
  return 0;
}
