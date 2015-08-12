


#include "base.h"

template <typename T, template <typename> class Container>
void foo(Container<T> &container, T v) {
    container.push_back(v);
}


template <template <typename, typename...> class Container, 
          typename Value,
          typename... AddParams >
void bar(Container<Value, AddParams...> & c, const Value & t)
{
    c.push_back(t);
}

template <typename T>
class OneParameterVector {
    public:
    void push_back(const T &v) {}
};

#include <vector>
int main () {
    OneParameterVector<float> b;
    bar (b, 1.2f);
    std::vector<float> c;
    bar (c, 1.2f);
    return 0;
}



