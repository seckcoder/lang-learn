#include <vector>
using namespace std;
#define mod2(n) ((n) - (((n)>>1)<<1))

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        if (rowIndex == 0) {
            return vector<int>({1});
        } else {
            vector<int> dp[2];
            for (int row = 1; row <= rowIndex; row++) {
                int col_len = row+1;
                int cur_row = mod2(row);
                int last_row = mod2(row-1);
                dp[cur_row][0] = 1;
                dp[cur_row][col_len-1] = 1;
                for (int col = 1; col <= col_len-2; col++) {
                    dp[cur_row][col] = dp[last_row][col] + dp[last_row][col-1];
                }
            }
            return dp[mod2(rowIndex)];
        }
    }
};

int main(int argc, const char *argv[])
{
  
  return 0;
}
