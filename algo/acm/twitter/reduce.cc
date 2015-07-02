#include <iostream>
using namespace std;

inline int gcd(int a, int b) {
  if (b == 0) {
    return a;
  } else {
    return gcd(b, a%b);
  }
}
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    string sx,sy;
    std::getline(std::cin, sx, '/');
    int x = std::stoi(sx);
    std::getline(std::cin, sy, '\n');
    int y = std::stoi(sy);
    int gcd_v = gcd(x,y);
    cout << x / gcd_v << "/" << y /gcd_v << endl;
  }
  return 0;
}
