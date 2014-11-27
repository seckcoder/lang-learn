#include <initializer_list>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char *argv[])
{
  char a, b, c;
  cin >> a >> b >> c;
  string s({a, b, c});
  cout << s << endl;
  return 0;
}
