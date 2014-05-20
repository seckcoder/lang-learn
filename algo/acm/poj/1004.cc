#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;


int main(int argc, const char *argv[])
{
  float sum = 0.0;
  for(int i = 1; i <= 12; i++) {
    float a;
    cin >> a;
    sum += a * 100;
  }
  sum = round(sum / 12.0) / 100.0;
  cout << "$" << std::fixed << setprecision(2) << sum << endl;
  return 0;
}
