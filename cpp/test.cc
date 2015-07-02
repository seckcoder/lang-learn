#include <initializer_list>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;


int main(int argc, const char *argv[]) {
  vector<int> nums = {1,2};
  cout << (nums.begin() < (nums.end() - 2)) << endl;
  return 0;
}
