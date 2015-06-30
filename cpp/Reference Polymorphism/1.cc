
#include <iostream>

using namespace std;

class Base {
    public:
        Base() {}
        virtual void foo() {
            cout << "foo" << endl;
        }
};

class Derived: public Base {
    virtual void foo() {
        cout << "Derived" << endl;
    }
};

int main() {
    Derived derived;
    Base &base = derived;
    base.foo();
    return 0;
}
