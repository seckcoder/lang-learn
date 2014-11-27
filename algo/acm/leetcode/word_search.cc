#define M 100
bool visited[M][M];
class Solution {
public:
    int width, height;
    bool exist(vector<vector<char> > &board, string word) {
        if (word.length() == 0) return true;
        height = board.size();
        if (height == 0) return false;
        width = board[0].size();
        if (width * height < word.length()) return false;
        memset(visited, false, sizeof(visited));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (board[i][j] == word[0]) {
                    // visited[i][j] = true;
                    if (findPath(board, word, i, j, 1, visited)) return true;
                }
            }
        }
        return false;
    }
    bool findPath(const vector<vector<char> > &board, const string &word, int xi, int yi, int wi, bool visited[][M]) {
        if (wi >= word.length()) return true;
        visited[xi][yi] = true;
        if (xi > 0 && !visited[xi-1][yi] && board[xi-1][yi] == word[wi] && findPath(board, word, xi-1, yi, wi+1, visited)) {
            return true;
        }
        if (yi > 0 && !visited[xi][yi-1] && board[xi][yi-1] == word[wi] && findPath(board, word, xi, yi-1,  wi+1, visited)) {
            return true;
        }
        if (xi < height - 1 && !visited[xi+1][yi] && board[xi+1][yi] == word[wi] && findPath(board, word, xi+1, yi, wi+1, visited)) {
            return true;
        }
        if (yi < width - 1 && !visited[xi][yi+1] && board[xi][yi+1] == word[wi] && findPath(board, word, xi, yi+1, wi+1, visited)) {
            return true;
        }
        visited[xi][yi] = false;
        return false;
    }
};

int main(int argc, const char *argv[])
{
  Solution sol;
  return 0;
}
