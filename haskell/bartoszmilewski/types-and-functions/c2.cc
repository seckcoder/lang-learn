#include <iostream>
#include <ctime>
#include <cstdlib>
#include "memoize.h"
#include "utils.h"
using namespace std;


// this function is not pure
int myrand1() {
  std::srand(std::time(0));
  return std::rand();
}


// this function is pure
int myrand2(time_t seed) {
  std::srand(seed);
  return std::rand();
}

int main() {
  // the generated function mem_rand1 from myrand1 is pure(but with side-effect)...
  // But this function is meaningless. What can we do with a function
  // that always return the same value...
  auto mem_rand1 = memoize(myrand1);
  cout << mem_rand1() << endl;
  wait(2);
  cout << mem_rand1() << endl;
  auto mem_rand2 = memoize(myrand2);
  time_t seed = std::time(0);
  cout << mem_rand2(seed) << endl;
  wait(2);
  cout << mem_rand2(seed) << endl;
  
  return 0;
}
