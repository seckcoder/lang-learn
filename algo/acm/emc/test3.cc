#include <cstdio>

struct IntList {
  int value;
  IntList *next;
};

// you can also use includes, for example:
// #include <algorithm>
int solution(IntList * L, int M) {
  int len = 0;
  IntList *tmp = L;
  while (tmp != NULL) {
    len += 1;
    tmp = tmp->next;
  }
  int idx_of_m = len - M;
  // I'm not sure ...
  if (idx_of_m < 0 || idx_of_m >= len) {
    return -1;
  }
  tmp = L;
  int counter = 0;
  while (tmp != NULL) {
    if (counter == idx_of_m) {
      return tmp->value;
    }
    counter += 1;
    tmp = tmp->next;
  }
  return -1;
}

int main(int argc, const char *argv[]) {

}
