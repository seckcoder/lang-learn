#include <stdlib.h>


void find_path(char **map, int m, int n) {
}



int test() {
  int m = 4;
  int n = 4;
  char **map = (char**)malloc(m*sizeof(char*));
  for(int i = 0; i < m; i++) {
    map[i] = (char*)malloc(n*sizeof(char));
    for(int j = 0; j < n; j++) {
      map[i][j] = 'o';
    }
  }

  map[0][0] = 's';
  map[m-1][n-1] = 'e';
  map[1][1] = 'x';
  map[2][2] = 'x';
  find_path(map, m, n);
}
