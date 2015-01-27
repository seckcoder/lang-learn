#include <initializer_list>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

unsigned roundToEven(unsigned x, int k);
string bin(unsigned int x) {
  if (x == 0) return string("0");
  string res;
  while (x) {
    int hx = x >> 1;
    res.append(1, '0' + (x - (hx << 1)));
    x = hx;
  }
  std::reverse(res.begin(), res.end());
  return res;
}


unsigned float_i2f(int x) {
  int e = ((127+30) << 23);
  int mask, halfValue, last;
  if (x == 0) return 0;
  if (x == (1<<31)) return ((127+31)<<23) | (1<<31);
  if (x < 0) {
    x = -x;
    // sign_mask = (1<<31);
    e = (1<<31) + e;
  }

  while (!(x&(1<<30))) {
    x <<= 1;
    e -= (1<<23);
    //e -= 1;
  }
  
  // round to even
  
  mask = 0xFF;
  halfValue = 0x40;
  last = x & mask;
  if (last != halfValue) {
    e += (last & halfValue) >> 6; // carry
  }
  return ((x >> 7) & 0x7FFFFF) + e;
}


unsigned float_i2f2(int x) {
  int sign_mask = 0;
  int min_int = 0x80000000;
  int e;
  if (x == 0) return 0;
  if (x == min_int) return 0xcf000000;
  if (x < 0) {
    x = -x;
    sign_mask = min_int;
  }

  return 0;

  /* e = 0x4b000000; // (127 + 23) << 23 */
  /* if (x < 0x1000000) { */
  /*   while (!(x & 0x800000)) { */
  /*     x = x << 1; */
  /*     e -= 0x800000; // 1 << 23 */
  /*   } */
  /* } else { */
  /*   while (x >= 0x1000000) { */
  /*     x = x >> 1; */
  /*     e += 0x800000; */
  /*   } */
  /*   cout << bin(e) << endl; */
  /* } */
  /* return sign_mask | e | (x & 0x7FFFFF); */
}


unsigned roundToEven(unsigned x, int k) {
  unsigned mask = ~((~0)<<(k+1));
  unsigned halfValue = 1<<(k-1);
  unsigned last = x & mask;
  if (last == halfValue) {
    // is half and zero
    // simply ignore
  } else {
    // get the kth bit
    x += (last & halfValue);
  }
  return x>>k;
}

void testRoundToEven(int x, int k) {
  cout << "test " << x << " remove last " << k << " bits" << endl;
  cout << bin(x) << endl;
  cout << bin(roundToEven(x,k)) << endl;
  cout << "................................" << endl;
}

unsigned float_i2f1(int x) {
  unsigned count = 0x4f800000; // 159 << 23
  unsigned tmp;
  unsigned abs = x;
  unsigned last = 0;
  if(x < 0){
    count = 0xcf800000; // -159 << 23
    abs = -x;
  }
  while(abs){
    tmp = abs;
    abs <<= 1;
    count = count - 0x800000; // count -= (1 << 23);
    if(tmp & 0x80000000){ // moved enough
      last = (abs & 0x3ff); // last ten
      // if x < (1<<24), then it will move for at least 8 pos.
      // so, count += 0
      // otherwise
      if(last != 0x100){
        count = count + ((abs & 0x100) >> 8);// get the 9th bit of abs
      }
      return (abs >> 9) + count;
    }
  }
  return 0;
}

int fromBin(string s) {
  int res = 0;
  for (int i = 0; i < s.length(); i++) {
    res = (res << 1) + (0 + (s[i] - '0'));
  }
  return res;
}

void subOverflow() {
  int x = 0xC0000000;
  int y = 0xA0000000;
  cout << bin(x) << endl;
  cout << bin(y) << endl;
  cout << bin(x - y) << endl;
  cout << "0-00000----1-1" << endl;
  cout << bin((~y)+1) << endl;
  cout << bin(x+((~y)+1)) << endl;
  cout << x - y << endl;
}
void test(const char **argv) {
  string v1 = bin(float_i2f(atoi(argv[1])));
  cout << v1 << endl;
  cout << "----------" << endl;
  string v2 = bin(float_i2f1(atoi(argv[1])));
  cout << v2 << endl;
}

void test_round() {
  const int n = 7;
  int values[n] = {
    fromBin("1000"), // 1000
    fromBin("1001"), // 1000
    fromBin("1010"), // 1000
    fromBin("1011"), // 1100
    fromBin("1101"), // 1100
    fromBin("1110"),  // 10000
    fromBin("1111") // 10000
    };
  //testRoundToEven(fromBin("1110"), 2);
  for (int i = 0; i < n; i++) {
     testRoundToEven(values[i], 2);
  }
}
int main(int argc, const char *argv[]) {
  subOverflow();
  return 0;
}
