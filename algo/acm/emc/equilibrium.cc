#include <iostream>
#include <vector>
using namespace std;
// you can also use includes, for example:
// #include <algorithm>

void get_two_sum(const vector<int> &sum, const vector<int> &sum_rev, int p,
                 int *psum1, int *psum2) {
  if (p == 0 && sum.size() == 1) {
    *psum1 = 0;
    *psum2 = 0;
  } else if (p == 0 && sum.size() > 1) {
    *psum1 = 0;
    *psum2 = sum_rev[p+1];
  } else if (p == sum.size() - 1) {
    *psum1 = sum[p-1];
    *psum2 = 0;
  } else  {
    *psum1 = sum[p-1];
    *psum2 = sum_rev[p+1];
  }
}
int solution(const vector<int> &A) {
  if (A.size() == 0) return -1;
    vector<int> sum(A.size()), sum_rev(A.size());
    int tmp = 0;
    for(int i = 0; i < A.size(); i++) {
      //printf("%d\n", A[i]);
      sum[i] = tmp + A[i];
      tmp = sum[i];
    }
    tmp = 0;
    for(int i = A.size() - 1; i >= 0; i--) {
      sum_rev[i] = tmp + A[i];
      tmp = sum_rev[i];
    }
    for(int i = 0; i <= A.size()-1; i++) {
      int sum1, sum2;
      get_two_sum(sum, sum_rev, i, &sum1, &sum2);
      if (sum1 == sum2) {
        return i;
      }
    }
    return -1;
}

int main(int argc, const char *argv[])
{
  int tmp[] = {-7, 1, 5, 2, -4, 3, 0};
  vector<int> A(tmp, tmp+7);
  solution(A);
  return 0;
}
