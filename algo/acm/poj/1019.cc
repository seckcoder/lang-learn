#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <set>
#include <cstdio>
#include <climits>
#include <algorithm>


using namespace std;

#define int64 long long int

#define MAX_I 2147483647

#define MAX_K 31268

int64 digits_vec[MAX_K+1];
int k_digits_vec[MAX_K+1];


/*int equation(int k) {
  if (k - ((k >> 1)<<1) == 0) {
    return (k >> 1) * (k + 1);
  } else {
    return k * (((k+1)>> 1));
  }
}*/


int searchK(int v, int p, int r) {
  // [p, r)
  while (p < r) {
    int mid = (p + r) >> 1;
    if (digits_vec[mid] < v) {
      if (p + 1 == r) {
        break;
      } else {
        p = mid;
      }
    } else {
      r = mid;
    }
  }
  //cout << "here " << digits_vec[p] << endl;
  return p;
}

int getDigitsNum(int k) {
  int res = 0;
  while (k != 0) {
    k = k / 10;
    res += 1;
  }
  return res;
}

string to_string(int v) {
  string tmp;
  while ( v != 0 ) {
    int digit = v % 10;
    tmp.push_back((char)(digit + '0'));
    v = v / 10;
  }
  std::reverse(tmp.begin(), tmp.end());
  return tmp;
}

string genStrSeq(int k) {
  int pos = 0;
  string res;
  for (int i = 1; i <= k; i++) {
    res.append(to_string(i));
  }
  return res;
}

int searchInK(int v, int p, int r) {
  // [p, r)
  while (p < r) {
    int mid = (p + r) >> 1;
    if (k_digits_vec[mid] < v) {
      if (p + 1 == r) {
        break;
      } else {
        p = mid;
      }
    } else {
      r = mid;
    }
  }
  return p;
}

char solve(int i) {
  int k = searchK(i, 0, MAX_K);
  //cout << k << " " << i - digits_vec[k] << endl;
  int kk = searchInK(i - digits_vec[k], 0, k+1);
  //cout << kk << " " << i - digits_vec[k] - k_digits_vec[kk] << endl;
  //cout << k << " " << kk << endl;
  return to_string(kk + 1)[i - digits_vec[k] - k_digits_vec[kk]-1];
}

int main(int argc, const char *argv[])
{
  //freopen("test.in", "r", stdin);

  int64 total_digits_num = 0;
  digits_vec[0] = 0;
  k_digits_vec[0] = 0;
  for (int k = 1; k <= MAX_K; k++) {
    k_digits_vec[k] = getDigitsNum(k);
    digits_vec[k] =  digits_vec[k-1] + k_digits_vec[k];
  }
  //cout << digits_vec.size() << endl;
  for (int i = 1; i <= MAX_K; i++) {
    digits_vec[i] += digits_vec[i-1];
    k_digits_vec[i] += k_digits_vec[i-1];
  }
  int t;
  scanf("%d", &t);
  while (t--) {
    int i;
    scanf("%d", &i);
    printf("%c\n", solve(i));
  }
  return 0;
}
