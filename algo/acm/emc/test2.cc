#include <cstring>
#include <cstdio>

#define M 1000
void print_bignum(int bignum[]) {
  for(int i = bignum[0]; i >= 1; i--) {
    printf("%d", bignum[i]);
  }
  printf("\n");
}

void initialize(int bignum[]) {
  // N = 0
  bignum[0] = 1; // length
  bignum[1] = 1;
}

// copy bignumber
void copy(int dest[], int src[]) {
  memcpy(dest, src, sizeof(int)*(src[0]+1));
}

// multiply bignum by 10
void mult_10(int bignum[]) {
  for(int i = bignum[0]; i >= 1; i--) {
    bignum[i+1] = bignum[i];
  }
  bignum[1] = 0;
  bignum[0] += 1;
}

// add bignum a and b, result return in a
void add(int a[], int b[]) {
  /*print_bignum(a);
  print_bignum(b);*/
  for(int i = 1; i <= b[0] && i <= a[0]; i++) {
    a[i] += b[i];
  }
  if (b[0] > a[0]) {
    for(int i = a[0]+1; i <= b[0]; i++) {
      a[i] = b[i];
    }
    a[0] = b[0];
  }
  for(int i = 1; i <= a[0]; i++) {
    if (a[i] >= 10) {
      int tmp = a[i] / 10; // carry number
      a[i] = a[i] % 10;
      if (i >= a[0]) {
        a[i+1] = tmp;
        a[0] += 1; // length
      } else {
        a[i+1] += tmp;
      }
    }
  }
}

int stat_digit1_num(int bignum[]) {
  int ret = 0;
  for(int i = 1; i <= bignum[0]; i++) {
    if (bignum[i] == 1) {
      ret += 1;
    }
  }
  return ret;
}



// you can also use includes, for example:
// #include <algorithm>
int solution(int N) {
  // the number of digits will not exceed 2 * 1000
  int bignum[2*M];
  int tmp[2*M];
  initialize(bignum);
  int counter = 0;
  while (counter < N) {
    copy(tmp, bignum);
    mult_10(bignum);
    add(bignum, tmp);
    counter += 1;
  }
  return stat_digit1_num(bignum);
}

int main(int argc, const char *argv[]) {
  printf("%d\n", solution(1000));
  return 0;
}
