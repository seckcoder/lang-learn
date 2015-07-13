#include <initializer_list>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

/* T -> Compare -> m (T, Compare) */
template <class T, class Compare=std::less<T> >
class Object {
    public:
        T val;
        Compare value_compare; /* the compare function */
        explicit Object(const T &v_):val(v_) {}
        explicit Object(const T &v_, const Compare comp)
            :val(v_), value_compare(comp) {}
        bool operator<(const Object &o) const {
            return value_compare(val, o.val);
        }
        bool operator<(const T &v_) const {
            return value_compare(val, v_);
        }
};



/* using `typedef` declare a function type */
typedef bool (*CompareInt)(int,int);

template <class T>
bool comp_T(T a, T b) {
    return a < b;
}


template <class T>
struct CompFunctor: binary_function<T,T,bool> {
    bool operator()(T a, T b) const {
        return a < b;
    }
};

/* using `using` to declare a template function type */
template <class T>
using CompareT = bool (*) (T, T);

int main(int argc, const char *argv[]) {
    cout << (Object<int>(1) < 3) << endl;
    cout << (Object<int,std::less<int> >(1) < 3) << endl;

    /* using functor */
    cout << (Object<int, CompFunctor<int> >(1) < 3) << endl;

    /* pass aliased function type */
    cout << (Object<int, CompareInt>(1, comp_int) < 3) << endl;

    auto comp_char = [&](char a, char b) { return a < b; };
    cout << (Object<char, decltype(comp_char)>('a', comp_char) < 'b') << endl;

    /* c++11 doesn't support polymorphic lambdas.
     * */
    cout << (Object<char, CompareT<char> >('a', comp_T) < 'b') << endl;
    return 0;
}
