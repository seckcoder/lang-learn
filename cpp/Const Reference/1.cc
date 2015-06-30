
#include <string>
#include <iostream>
using namespace std;

/*
 * A temporary bound to a reference member in a constructor’s ctor-initializer
(12.6.2) persists until the constructor exits.
 */

class Sandbox
{
public:
    Sandbox(const string& n) : member(n) {} /* string("four") will be deleted before the constructor exits */
    const string& member;
};

/* Compile with:
 * g++ -Wall -Wextra *.cc
 */
class X
{
private:
        const int a;
        const int& b;
public:
        X(): a(10) , b(20)
        {
        //      std::cout << "constructor : a " << a << std::endl;
        //      std::cout << "constructor : b " << b << std::endl;
        }

        void display()
        {
            std::cout << "display():a:" << a << std::endl;
            std::cout << "display():b:" << b << std::endl;

        }
};


int main()
{
    {
        /* Example 1 */ 
        Sandbox sandbox(string("four"));
        cout << "The answer is: " << sandbox.member << endl;
    }
    {
        /* Example 2 */

        X x;
        x.display();
    }
    return 0;
}
