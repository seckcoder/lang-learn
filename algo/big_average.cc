#include <iostream>
#include <vector>

using namespace std;



int big_average(const vector<int> &vec) {
  // we want sum(vec) / vec.size()
  int a = vec.size(), quotient = 0, remainder = 0;
  for (int i = 0; i < vec.size(); i++) {
    quotient += vec[i] / a;
    remainder += vec[i] % a;
    if (remainder >= a) {
      quotient += 1; // according to the requirement, quotient will never overflow
      remainder -= a; // the maximum value remainder will hold is 2*(vec.size()-1), apparently, remainder will also not overflow
    }
  }
  return quotient;
}

struct ExactNum {
  int quotient;
  int remainder;
};

ExactNum big_avg_rec(const vector<int> &vec, int p, int r) {
  ExactNum ans;
  if (p == r) {
    ans.quotient = vec[p] / vec.size();
    ans.remainder = vec[p] % vec.size();
  } else {
    ExactNum left = big_avg_rec(vec, p, (p+r)/2);
    ExactNum right = big_avg_rec(vec, (p+r)/2+1, r);
    ans.quotient = left.quotient + right.quotient + (left.remainder + right.remainder) / vec.size();
    ans.remainder = (left.remainder + right.remainder) % vec.size();
  }
  return ans;
}
    
// another version using divide conquer.
int big_average_divide_conquer(const vector<int> &vec) {
  ExactNum exact_num = big_avg_rec(vec, 0, vec.size()-1);
  return exact_num.quotient;
}

int main() {
  vector<int> vec = {2147483647,2147483646,2147483645};
  cout << big_average(vec) << endl;
  cout << big_average_divide_conquer(vec) << endl;
  return 0;
}
