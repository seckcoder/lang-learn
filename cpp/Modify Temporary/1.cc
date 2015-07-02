/*
 *
 * For whatever historical reasons unknown,
 * C++ doesn't want us to modify temporary objects(Some people said as temporary
 * object will disappear in a short time, then modifying it in most cases will
 * cause error). But we do can modify it by fooling compiler and the language.
 * 
 */

#include "../base.h"

class Object {
    public:
        int a,b;
        Object():a(0),b(0) {}
        Object &setA(int a_) {
            a = a_;
            return (*this);
        }
        Object &setB(int b_) {
            b = b_;
            return (*this);
        }
};

ostream& operator<<(ostream& os, const Object &o) {
    os << o.a << " " << o.b;
}

// http://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html
int main() {
    cout << Object().setA(1).setB(2) << endl;
    return 0;
}
