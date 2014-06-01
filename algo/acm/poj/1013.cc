

#include <iostream>
#include <string>
#include <cstdio>


using namespace std;

#define M 12

bool buckets[M];

void SetBuckets(const string &s) {
  memset(buckets, false, M*sizeof(bool));
  for(int i = 0; i < s.length(); i++) {
    buckets[s[i] - 'A'] = true;
  }
}

void SetTrue(bool true_coins[], bool counter_feit[], const string &s) {
  for(int i = 0; i < s.length(); i++) {
    true_coins[s[i] - 'A'] = true;
  }
}

void SetCounterFeit(bool true_coins[], bool counter_feit[], const string &s) {
  for(int i = 0; i < s.length(); i++) {
    counter_feit[s[i] - 'A'] = true;
  }
  SetBuckets(s);
  // 其余的全为真
  for(char c = 'A'; c <= 'L'; c+=1) {
    if (!buckets[c - 'A']) {
      true_coins[c - 'A'] = true;
    }
  }
}

bool GetCounterFeit(bool true_coins[], bool counter_feit[], char &c) {
  int cf_num = 0;
  for(int i = 0; i < M; i++) {
    if (!true_coins[i] && counter_feit[i]) {
      c = i + 'A';
      cf_num += 1;
    }
  }
  //cout << cf_num << endl;
  if (cf_num == 1) {
    return true;
  } else {
    return false;
  }
}


template<class T, class Op>
void CountingSort(T &vec, const Op &op, int p, int r) {
  int *bucket = new int[op.size];
  memset(bucket,0,op.size*sizeof(int));
  for(int i = p; i <= r; i++) {
    bucket[op.hash(vec[i])] += 1;
  }
  for(int i = 0, j = 0; i < op.size; i++) {
    while (bucket[i] > 0) {
      vec[p + j] = op.rev_hash(i);
      bucket[i] -= 1;
      j += 1;
    }
  }
  delete [] bucket;
}

class HashOp {
 public:
  int size;
  HashOp():size(M) {}
  int hash(char c) const {
    return c - 'A';
  }
  char rev_hash(int i) const {
    return i + 'A';
  }
};

string UnionString(string &s1, string &s2) {
  CountingSort(s1, HashOp(), 0, s1.length() - 1);
  CountingSort(s2, HashOp(), 0, s2.length() - 1);
  string res;
  int i, j;
  for (i = 0, j = 0; i < s1.length() && j < s2.length();){
    if (s1[i] < s2[j]) {
      res.push_back(s1[i]);
      i += 1;
    } else if (s1[i] > s2[j]) {
      res.push_back(s2[j]);
      j += 1;
    } else {
      i += 1;
      j += 1;
    }
  }
  while ( i < s1.length() ) {
    res.push_back(s1[i]);
    i += 1;
  }
  while ( j < s2.length() ) {
    res.push_back(s2[j]);
    j += 1;
  }
  return res;
}

struct InputLine {
  string left, right, eva_res;
};


bool solve(const InputLine inputs[3], bool heavier, char &cf_coin) {
    bool true_coins[M];
    bool counter_feit[M];
    memset(true_coins, false, M*sizeof(bool));
    memset(counter_feit, false, M*sizeof(bool));
    for (int i = 0; i < 3; i++) {
      if (inputs[i].eva_res == "even") {
        SetTrue(true_coins, counter_feit, inputs[i].left);
        SetTrue(true_coins, counter_feit, inputs[i].right);
      } else if ((!heavier && inputs[i].eva_res == "up") ||
                 (heavier && inputs[i].eva_res == "down")) {
        SetTrue(true_coins, counter_feit, inputs[i].left);
        SetCounterFeit(true_coins, counter_feit, inputs[i].right);
      } else if ((heavier && inputs[i].eva_res == "up") ||
                 (!heavier && inputs[i].eva_res == "down")) {
        SetTrue(true_coins, counter_feit, inputs[i].right);
        SetCounterFeit(true_coins, counter_feit, inputs[i].left);
      }
    }
    return GetCounterFeit(true_coins, counter_feit, cf_coin);
}


int main(int argc, const char *argv[])
{
  //freopen("test.in", "r", stdin);
  int t;
  cin >> t;
  for(int i = 0; i < t; i++) {
    InputLine inputs[3];
    for(int j = 0; j < 3; j++) {
      string left, right, eva_res;
      cin >> inputs[j].left >> inputs[j].right >> inputs[j].eva_res;
    }
    char cf_coin;
    if (solve(inputs, false, cf_coin)) {
      cout << cf_coin << " is the counterfeit coin and it is light." << endl;
    } else if (solve(inputs, true, cf_coin)) {
      cout << cf_coin << " is the counterfeit coin and it is heavy." << endl;
    } else {
      cout << "no good" << endl;
    }
  }
  return 0;
}
