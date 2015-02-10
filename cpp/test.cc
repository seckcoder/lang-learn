#include <initializer_list>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;


int main(int argc, const char *argv[]) {
  int a = 0, b = 0;
  while (a != 1) {
    cin >> a >> b;
    cout << a << " " << b << endl;
    cin.clear();
  }
  return 0;
}
