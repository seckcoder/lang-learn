#include <iostream>

using namespace std;


int knight_number_of_moves(int x, int y) {
  int num = 0;
  // x + 2, y + 1 : 2
  // x + 1, y + 2 : 2
  // x - 2, y -1 : 2
  // x - 1, y - 2 : 2
  if (x + 2 < 8 && y + 1 < 8) {
    num += 2;
  }
  if (x + 1 < 8 && y + 2 < 8) {
    num += 2;
  }
  if (x - 2 >= 0 && y - 1 >= 0) {
    num += 2;
  }
  if (x - 1 >= 0 && y - 2 >= 0) {
    num += 2;
  }
  return num;
}



/* total possible number of moves for knight */
int total_move_for_knight() {
  int sum_moves = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      sum_moves += knight_number_of_moves(i,j);
    }
  }
  return sum_moves/2;
}


int main() {
  out << knight_number_of_moves(0, 0) << " " << total_move_for_knight() << endl;
  return 0;
}
