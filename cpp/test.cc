#include <initializer_list>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

void foo(const vector<string> &vec) {
  for (int i = 0; i < vec.size(); i++) {
    for (int j = 0; j < vec[i].length(); j++) {
      cout << vec[i][j] << endl;
    }
  }
}

int main(int argc, const char *argv[]) {
  vector<string> vec;
  vec.push_back("ab");
  foo(vec);
  return 0;
}
