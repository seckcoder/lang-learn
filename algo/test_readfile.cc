#include <stdio.h>


int main(int argc, const char *argv[]) {
  FILE* fin = fopen("data/test.dat", "r");
  while (true) {
    int v;
    fscanf(fin, "%d", &v);
    if (feof(fin)) {
      break;
    }
    printf("%d\n", v);
  }
  fclose(fin);
}
