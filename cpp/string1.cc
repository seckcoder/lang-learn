#include <string>
#include <iostream>

using namespace std;


int main(int argc, const char *argv[])
{
  // C++ string is not null terminated
  string a(10, 'c');
  cout << a << " " << a.length() << endl;
  a[2] = '\0';
  cout << a << " " << a.length() << endl;
  // But after converting it into c string
  printf("%s\n", a.c_str());
  return 0;
}
