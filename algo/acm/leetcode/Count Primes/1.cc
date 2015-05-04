class Solution {
public:
    int countPrimes(int n) {
        if (n <= 1) return 0;
        bool *dp = new bool[n];
        memset(dp, true, (n)*sizeof(bool));
        int count = 0; // 1 is not prime number!
        
        /* the bottom up approach
         * Generally, if p is prime number, then multiple of p is not prime number
         */
        for (int p = 2; p < n; p+=1) {
            if (dp[p]) {
                count += 1;
                for (int m = 2; m * p < n; m++) {
                    dp[m*p] = false;
                }
            }
        }
        delete [] dp;
        return count;
    }
};
