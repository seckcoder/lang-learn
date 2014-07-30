#include <iostream>
#include <string>

using namespace std;

void f(int aa) {
  aa = 2;
}

void f1(int &aa) {
  aa = 2;
}

void f2(string s) {
  s[0] = 'e';
}

void f3(string &s) {
  s[0] = 'e';
}

void f4(int a, int &b) {
  cout << "value of a and b : " << a << " " << b << endl;
  cout << "address of a and b : " << &a << " " << &b << endl;
}

void f5(const char *s1, const char *&s2) {
  cout << "s1 points to the same location in memory as s. But the location of the pointer in memory is different." << endl;
  printf("\tAddress of s1: %p ; Address pointed by s1 : %p\n",
         &s1, s1);
  cout << "s2 is passed by reference. Both the location that's pointed by s2 and the location of s2 in memory is the same as s" << endl;
  printf("\tAddress of s2: %p ; Address pointed by s2: %p\n",
         &s2, s2);
}

void f6(string s) {
  printf("After passing string s by value:\n");
  printf("s's data address: %p\n", s.data());
  printf("The address is the same. Just as we expected\n");
  s[0] = 'b';
  printf("After editing s: %p\n", s.data());
}

int main(int argc, const char *argv[])
{

  cout << "/*****************************/" << endl;
  cout << "Basics of parameter passing:" << endl;

  {
    int a = 1;
    cout << "a: " << a << endl;
    f(a); // passing by value
    cout << "after passing by value : " << a << endl;
    f1(a); // passing by reference
    cout << "after passing by reference: " << a << endl;
  }



  {
    string s = "abc";
    cout << "s: " << s << endl;
    f2(s); // passing by value
    cout << "after passing by value : " << s << endl;
    f3(s); // passing by reference
    cout << "after passing by reference: " << s << endl;
  }

  cout << "/*****************************/\n\n" << endl;

  cout << "/*****************************/" << endl;
  cout << "What's the difference? Notice the value of address" << endl;
  {
    int a = 1;
    cout << "address of a : " << &a << endl;
    f4(a, a);
  }
  cout << "/*****************************/\n\n" << endl;


  cout << "/*****************************/" << endl;
  cout << "How about passing address?" << endl;
  {
    const char *s = "abcd";
    printf("Address of s: %p  ; Address pointed by s : %p\n",
           &s, s);
    f5(s, s);
  }
  cout << "/*****************************/\n\n" << endl;

  // Summary:
  //    passing by value copies the data while passing by reference use the
  //    original data.


  cout << "/*****************************/" << endl;
  cout << "Most string implementation uses copy-on-write." << endl;
  {
    string s = "abc";
    printf("Every object of string contains a block of memory, which is pointed by: %p\n",
           s.data());
    string s1 = s; // copy s to anther string s1.
    printf("s1's data address: %p\n", s.data());
    printf("The address is the same. So the copy of string is 'shallow-copy'\n");
    s1[0] = 'e';
    printf("However, after we edit s1, s1's data address is: %p.\nIt's changed! So a new block of memory is allocated.", s1.data());
    printf("This is called copy-on-write. We don't allocate a new block of memory to store\nthe string data until we modify it.\n");

    printf("Passing by value just copies the data. It's 'almost' the same as using '=' operator\n");
    f6(s);
  }
  cout << "/*****************************/\n\n" << endl;

  return 0;
}
