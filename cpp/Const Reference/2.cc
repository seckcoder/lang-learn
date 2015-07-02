
/* The most important constant */

#include "../base.h"

string foo() { return "foo"; }


class Base {
    public:
    ~Base() {
        cout << "Base::~Base()" << endl;
    }
};
class Derived: public Base {
    public:
        int *v;
        Derived() {
            v = new int;
            *v = 3;
        }
        ~Derived() {
            cout << "Derived::~Derived()" << endl;
            delete v;
        }
};
int main() {
    {
        /* Example 1
         * Reference to constant lengthens the lifetime of temporary
         * until the lifetime of the reference
         */
        const string &ref = foo();
        cout << ref << endl;
    }
    printDelim();
    {
        /* Example 2
         * The destructor of Devived even don't need to be virtual.
         * It will be called automatically.
         */

        const Base &base = Derived();
        printDelim('-', 5);
    }
    printDelim();
    {
        /* Example 3
         * Compare this with Example 2.
         * Note the following code will cause memory leaks
         * since the destructor of Base and derived is not virtual
         */
        Derived *pd = new Derived;
        Base *pb = pd;
        delete pb;
    }
    return 0;
}
