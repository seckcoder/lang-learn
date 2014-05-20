#include <iostream>
#include <cmath>

using namespace std;

#define PI 3.14159265359

float disSquare(float x, float y) {
  return x * x + y * y;
}

int main(int argc, const char *argv[])
{
	int t;
	cin >> t;
	for(int r = 1; r <= t; r++) {
		float x, y;
		scanf("%f %f", &x, &y);
    printf("Property %d: This property will begin eroding in year %d.\n",
           r, int(ceil(PI*disSquare(x, y)*0.01)));
  }
  printf("END OF OUTPUT.\n");
  return 0;
}
