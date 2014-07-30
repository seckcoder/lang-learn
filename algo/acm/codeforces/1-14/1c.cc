#include <iostream>
#include <vector>
#include <string>
#include <string>
#include <iomanip>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;
using std::cin;
using std::string;

#define feq(a, b) (fabs((a) - (b)) <= 0.01)
#define PI 3.1415926

class Point {
 public:
  double x, y;
};


double euclidDisSquare(const Point &p1, const Point &p2) {
  return (p1.x - p2.x) * (p1.x - p2.x) +  (p1.y - p2.y) * (p1.y - p2.y);
}


double fgcd(double f1, double f2) {
  //cout << f1 << " " << f2 << endl;
  while (!feq(f2, 0)) {
    double tmp = f2;
    f2 = fmod(f1, f2);
    f1 = tmp;
  }
  return f1;
}

double radianToDegree(double radian) {
  return (radian / PI) * 180;
}

int main(int argc, const char *argv[])
{
  Point p1, p2, p3;
  cin >> p1.x >> p1.y;
  cin >> p2.x >> p2.y;
  cin >> p3.x >> p3.y;
  double a2 = euclidDisSquare(p1, p2);
  double b2 = euclidDisSquare(p2, p3);
  double c2 = euclidDisSquare(p1, p3);
  double a = sqrt(a2);
  double b = sqrt(b2);
  double c = sqrt(c2);
  //cout << a << " " << b << " " << c << endl;
  // Halen formula. S = sqrt(p(p-a)(p-b)(p-c)), p = (a+b+c)/2
  // law of of sine. a/sinA = b/sinB = c/sinc = 2R
  // S = absinC/2 = abc/4R
  double p = (a+b+c) * 0.5;
  double S = sqrt(p*(p-a)*(p-b)*(p-c));
  double r = (a*b*c)/(4.0*S);
  double alpha = acos(1.0 - (a2/(r*r))*0.5);
  double beta = acos(1.0 - (b2/(r*r))*0.5);
  double gamma = acos(1.0 - (c2/(r*r))*0.5);
  double theta = fgcd(alpha, fgcd(beta, gamma)); // maximum angle
  double theta_degree = radianToDegree(theta);
  double nedges = int(360.0 / theta_degree);
  cout << std::fixed << std::setprecision(8) << nedges * (r * r * sin(theta)) * 0.5 << endl;
  return 0;
}
