#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;


#define malloc2D(ptr, xDim, yDim, Type) { \
    ptr = (Type **)malloc(xDim * sizeof(Type*)); \
    ptr[0] = (Type *)malloc(xDim * yDim *sizeof(Type *));\
    for (size_t i = 1; i < xDim; i++) { \
        ptr[i] = ptr[i-1] + yDim; \
    }\
}

#define calloc2D(ptr, xDim, yDim, Type) {\
  malloc2D(ptr, xDim, yDim, Type); \
  memset(ptr[0], 0, xDim*yDim*sizeof(Type));\
}

#define free2D(ptr)  {\
    free(ptr[0]); \
    free(ptr); \
}

static int delta[8] = {0,-1, 0,1, 1,0, -1,0};

#define forEachDir(x,y,next_x,next_y) \
    for (int __i__ = 0, next_x = x+delta[__i__*2], next_y = y + delta[__i__*2+1]; \
        __i__ < 4; __i__+=1, next_x = x+delta[__i__*2], next_y = y + delta[__i__*2+1]) \


    
class Solution {
public:
    int m,n;
    int numIslands(vector<vector<char>> &grid) {
        m = grid.size();
        if (m == 0) return 0;
        n = grid[0].size();
        
        bool **visited;
        calloc2D(visited, m, n, bool);
        
        int scc_count = 0;
        dfs(grid, visited, scc_count);
        
        free2D(visited);
        return scc_count;
    }
    void dfs(const vector<vector<char> > &grid, bool **visited, int &scc_count) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    dfsRec(grid, i, j, visited);
                    scc_count += 1;
                }
            }
        }
    }
    void dfsRec(const vector<vector<char> > &grid, int x, int y, bool **visited) {
        visited[x][y] = true;
        int next_x, next_y;
        forEachDir(x,y,next_x,next_y) {
            if (inRange(next_x, next_y) && grid[next_x][next_y] == '1' && !visited[next_x][next_y]) {
                dfsRec(grid, next_x,next_y, visited);
            }
        }
    }
    bool inRange(int next_x, int next_y) const {
        return next_x >= 0 && next_x < m && next_y >= 0 && next_y < n;
    }
};

int main() {
  vector<vector<char> > grids = {
    {'1', '1', '0','0', '0'},
    {'1', '1', '0', '0', '0'},
    {'0', '0', '1', '0', '0'},
    {'0', '0', '0', '1', '1'}};
  /* grids.push_back({'1', '1', '1', '1', '0'}); */
  /* grids.push_back({'1', '1', '0', '1', '0'}); */
  /* grids.push_back({'1', '1', '0', '0', '0'}); */
  /* grids.push_back({'1', '0', '0', '0', '0'}); */


  cout << Solution().numIslands(grids) << endl;
  return 0;
}
