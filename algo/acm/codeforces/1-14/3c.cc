#include <iostream>
#include <vector>
#include <string>
#include <string>
#include <iomanip>
#include <cmath>
#include <map>
#include <set>
#include <cstdio>

using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::cin;
using std::string;
using std::map;


#define PI 3.14159265359

char game[3][4];

int main(int argc, const char *argv[])
{
  //freopen("test.in", "r", stdin);
  for (int i = 0; i < 3; i++) {
    scanf("%s", game[i]);
  }

  int x_num = 0, zero_num = 0, dot_num = 0;
  int x_row_stats[3] = {0};
  int x_col_stats[3] = {0};
  int x_cross_stats[2] = {0};
  int zero_row_stats[3] = {0};
  int zero_col_stats[3] = {0};
  int zero_cross_stats[2] = {0};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      switch (game[i][j]) {
        case 'X':
          x_num += 1;
          x_row_stats[i] += 1;
          x_col_stats[j] += 1;
          if (i == j) {
            x_cross_stats[0] += 1;
          }
          if (i + j == 2) {
            x_cross_stats[1] += 1;
          }
          break;
        case '0':
          zero_num += 1;
          zero_row_stats[i] += 1;
          zero_col_stats[j] += 1;
          if (i == j) {
            zero_cross_stats[0] += 1;
          }
          if (i + j == 2) {
            zero_cross_stats[1] += 1;
          }
          break;
        case '.':
          dot_num += 1;
          break;
        default:
          break;
      }
    }
  }
  if (x_num < zero_num || x_num - zero_num >= 2) {
    printf("illegal\n");
  } else {
    bool first_win = false;
    bool second_win = false;
    for (int i = 0; i < 3; i++) {
      if (x_row_stats[i] == 3 ||
          x_col_stats[i] == 3) {
        first_win = true;
      } else if (zero_row_stats[i] == 3 ||
                 zero_col_stats[i] == 3) {
        second_win = true;
      }
    }
    for (int i = 0; i < 2; i++) {
      if (x_cross_stats[i] == 3) {
        first_win = true;
      } else if (zero_cross_stats[i] == 3) {
        second_win = true;
      }
    }
    if (first_win && second_win) {
      printf("illegal\n");
    } else if (first_win && x_num == zero_num + 1) {
      printf("the first player won\n");
    } else if (first_win) {
      printf("illegal\n");
    } else if (second_win && x_num == zero_num) {
      printf("the second player won\n");
    } else if (second_win) {
      printf("illegal\n");
    } else if (dot_num == 0) {
      printf("draw\n");
    } else if (x_num == zero_num) {
      printf("first\n");
    } else if (x_num == zero_num + 1) {
      printf("second\n");
    }
  }
  return 0;
}
