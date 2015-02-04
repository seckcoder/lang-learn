#include <initializer_list>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;


int main(int argc, const char *argv[]) {
  ifstream ifs("test.txt");
  string type1, type2, id;
  int score;
  ifs >> type1 >> type2 >> id >> score;
  string rest;
  ifs >> std::ws;
  std::getline(ifs, rest);
  cout << rest.length() << endl;
  ifs.close();
  return 0;
}
