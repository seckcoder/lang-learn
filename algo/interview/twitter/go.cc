



bool isCaptured(
    const Board &board,
    const Point &p
    vector<vector<bool> &visited) {
  if (p.x == board_size) return true;
  if (p.y == board_size) return true;
  visited[p] = true;
  if (board[p] == '_') return false;
  if (board[p] == 'W') return true;
  if (board[p] == 'B') {
    vector<Point> points;
    getFourDirectionPoints(p, points);
    forEach(points, p) {
      if (!visited[p]) {
        if (!isCaptured(board,p, visited)) return false;
      }
    }
    return true;
  }
}
