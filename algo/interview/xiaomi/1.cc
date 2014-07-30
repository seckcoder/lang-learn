// n个石子分成k堆，有多少种分法。注意2,2,3和2,3,2是同一种分法

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print_vec(const vector<int> &res) {
  for(int i = 0; i < res.size(); i++) {
    cout << res[i] << " ";
  }
  cout << endl;
}

int f(int n, int k, int v, vector<int> &res) {
  if (n < k) return 0;
  if (n < k * v) return 0;
  if (k == 1) {
    res.push_back(n);
    print_vec(res);
    res.pop_back();
    return 1;
  }
  if (n == k*v) {
    for (int i = 1; i <= k; i++) {
      res.push_back(v);
    }
    print_vec(res);
    for (int i = 1; i <= k; i++) {
      res.pop_back();
    }
    return 1;
  }

  //cout << "**** " << n << " " << k << " " << v << endl;
  res.push_back(v);
  int div_num = f(n-v, k-1, v, res);
  res.pop_back();
  for (int i = v+1; k * i <= n; i++) {
    res.push_back(i);
    div_num += f(n-i, k-1, i, res);
    res.pop_back();
  }
  return div_num;
}


int main(int argc, const char *argv[])
{
  
  vector<int> res;
  cout << f(20, 10, 1, res) << endl;
  return 0;
}
