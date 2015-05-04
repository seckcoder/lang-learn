
/* dp[n] : max money we can get by robbing [0-n] houses
 *
 * dp[n] = std::max(dp[n-1], // not rob n
 *                  dp[n-2] + nums[n] // rob n. If we rob n, then we can only consider dp[n-2]
 *                  )
 *
 * 
 */
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        if (nums.size() == 2) return std::max(nums[0], nums[1]);
        /* here a is dp[n-2], b is dp[n-1]; */
        int a = nums[0],
            b = std::max(nums[0], nums[1]);
        
        for (int i = 2; i < nums.size(); i++) {
            int cur_max = std::max(b, a + nums[i]);
            a = b;
            b = cur_max;
        }
        return b;
    }
};
