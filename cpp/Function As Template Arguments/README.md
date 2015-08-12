
A Tutorial on how to declare function types in C++
We could use the following methods:

* Functor
Inherit from unary_function/binary_function...

* using `typedef`

typedef ReturnType (*FunctionPointer)(ArgType...)

* using `using`

* using `decltype`
