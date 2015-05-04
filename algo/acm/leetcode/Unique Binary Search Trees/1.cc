#define N 1000
int dp[N];
class Solution {
public:
    int numTrees(int n) {
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            dp[i] = 0; // number of trees that can generate with i nodes.
            for (int k = 1; k <= i; k++) {
                // k-1: number of trees in the left branch
                // i-k: number of trees in the right branch
                dp[i] += dp[k-1] * dp[i-k];
            }
        }
        return dp[n];
    }
};
