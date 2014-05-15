#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;


#define M 9
#define square_idx(i, j) (((i)/3)*3 + ((j)/3))
char sudo[M][M+1];

bool rows_exist[M][M];
bool cols_exist[M][M];
bool square_exist[M][M];

bool is_conflict(int i, int j, char c) {
  int c_i = c - '1';
  /*if (i == 7 && j == 0 && c == '9') {
    printf("******: %c %d\n", c, rows_exist[i][c_i]);
  }*/
  return rows_exist[i][c_i] ||
      cols_exist[j][c_i] ||
      square_exist[square_idx(i,j)][c_i];
}

void fill_hash(int i, int j, char c, bool value) {
  int c_i = c - '1';
  rows_exist[i][c_i] = value;
  cols_exist[j][c_i] = value;
  square_exist[square_idx(i,j)][c_i] = value;
}


void initial_hash_table() {
  for(int i = 0; i < M; i++) {
    memset(rows_exist, 0, M*sizeof(bool));
    memset(cols_exist, 0, M*sizeof(bool));
    memset(square_exist, 0, M*sizeof(bool));
  }
  for(int i = 0; i < M; i++) {
    for(int j = 0; j < M; j++) {
      char c = sudo[i][j];
      if (c != '0') {
        fill_hash(i, j, c, true);
      }
      //cout << "here: " << i << " " << j << " " << c << " " << rows_exist[7][8] << endl;
    }
  }
  /*cout << "there " << is_conflict(7, 0, '9') << " " 
      << rows_exist[7][8] << endl;*/
}

void get_options(int i, int j, char options[M], int *pnum) {
  *pnum = 0;
  for(int k = 0; k < M; k++) {
    char c = '1'+k;
    if (!is_conflict(i, j, c)) {
      options[*pnum] = c;
      *pnum += 1;
    }
  }
}

void print_result() {
  for(int i = 0; i < M; i++) {
    printf("%s\n", sudo[i]);
  }
  //printf("%s", sudo[8]);

}

bool solve_rec(int i, int j) {
  if (i >= M) {
    //print_result();
    //printf("\n");
    return true;
  } else if (j >= M) {
    return solve_rec(i+1, 0);
  } else if (sudo[i][j] == '0') {
    char options[M];
    int num_options = 0;
    get_options(i, j, options, &num_options);
    //printf("%d %d %d\n", i, j, num_options);
    for(int k = 0; k < num_options; k++) {
      sudo[i][j] = options[k];
      fill_hash(i, j, options[k], true);
      bool succeed = solve_rec(i, j+1);
      if (!succeed) {
        sudo[i][j] = '0';
        fill_hash(i, j, options[k], false);
      } else {
        return true;
      }
    }
    //printf("%d %d %d failed\n", i, j, num_options);
    return false;
  } else {
    return solve_rec(i, j+1);
  }
}

bool solve() {
  initial_hash_table();
  return solve_rec(0, 0);
}

int main(int argc, const char *argv[])
{
  int t;
  //scanf("%d", &t);
  cin >> t;
  while (t > 0) {
    for(int i = 0; i < M; i++) {
      //printf("%d\n", i);
      cin >> sudo[i];
      //cout << sudo[i] << endl;
      //printf("***%s***\n", sudo[i]);
    }
    //cout << endl;
    if (solve()) {
      print_result();
    }
    t-=1;
  }
  return 0;
}
