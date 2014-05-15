#include <stdio.h>

char sudo[9][10];


void solve() {
}

int main(int argc, const char *argv[])
{
  int t;
  scanf("%d", &t);
  while (t > 0) {
    for(int i = 0; i < 9; i++) {
      scanf("%s", sudo[i]);
    }
    solve();
    for(int i = 0; i < 9; i++) {
      printf("%s\n", sudo[i]);
    }
  }
  return 0;
}
