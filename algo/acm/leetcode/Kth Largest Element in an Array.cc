
#include <queue>
#include <cstdlib>
#include <iostream>
#include <cstdio>
using namespace std;


/** Quick-Select.
 *
 * The most challenging part about this question is how to avoid
 * infinite recursion.
 *
 * The first method is intuitive but the it's very difficult to
 * maintain the corner cases.
 *
 */


class Solution1 {
    public:
        int partition(vector<int>& nums, int b, int e) {
            int pivot = nums[b];
            // loop invariant:
            //      nums[b,j) >= pivot,
            //      nums[j,i) < pivot
            int i = b, j = b;
            for (; i < e; i++) {
                if (nums[i] >= pivot) {
                    std::swap(nums[i], nums[j]);
                    j += 1;
                }
            }
            return j;
        }
        int findKthLargest(vector<int>& nums, int k) {
            return findKthLargest(nums, 0, nums.size(), k);
        }

        /**
         * assert k <= e - b and k >= 1
         * We update the range of nums and k dynamically.
         * 
         */
        int findKthLargest(vector<int> &nums,
            int b, int e, int k) {
            if (e - b == 1) {
                return nums[b];
            }

            // [b, m) >= pivot, [m, e) < pivot
            int m = partition(nums, b, e);
            // Note m - b > 0. But it's possible that e - m == 0

            if (e - m == 0) {
                // For all i in [b,e), we have nums[i] >= nums[b].
                if (e - b == k) {
                    // We have k numbers, and nums[b] is the smallest.
                    // Therefore, nums[b] is the kth largest
                    return nums[b];
                } else {
                    // We have more than k numbers, and numbs[b] is the smallest,
                    // Therefore, we directly get rid of it
                    return findKthLargest(nums, b+1, e, k);
                }
            } else if (m - b >= k) {
                // The left part contains what we want
                return findKthLargest(nums, b, m, k);
            } else {
                // The right part contains what we want.
                // As m-b > 0, we avoid infinite recursion here.
                // Also, m - b < k, so k - (m-b) > 0. Also,
                // Since k <= e - b, therefore,
                // k - (m-b) <= e - m
                return findKthLargest(nums, m, e, k - (m-b));
            }
        }
};


/* The second method is easier to maintain.
 *
 * In this method, we don't update k. Instead, we just move
 * the elements in nums and make sure that finally, we got the kth largest
 * element in index k of nums
 *
 *
 * Time complexity:
 *  T(n) = T(n/2) + O(n)
 *  => T(n) = 1 + 2 + 2^2 + ... + 2^k with 2^k = n
 *     T(n) = 2*2^k - 1 = O(n)
 *  
 */
 
class Solution {
    public:
        int findKthLargest(vector<int> &nums, int k) {
            return findKthLargest(nums, 0, nums.size()-1, k-1);
        }


        int partition(vector<int> &nums, int p, int r) {
            int pivot = nums[p];
            std::swap(nums[p], nums[r]);
            // loop invariant:
            //      nums[p,j) > pivot
            //      nums[j, i) <= pivot
            int j = p;
            for (int i = p; i < r; i++) {
                if (nums[i] > pivot) {
                    std::swap(nums[i], nums[j]);
                    j += 1;
                }
            }
            std::swap(nums[j], nums[r]);
            return j;
        }
        
        /* In this function, [p,r] is the range of nums.
         * We assume k >= 0. r-p >= k.
         * k is kept th
         * */
        int findKthLargest(vector<int> &nums, int p, int r, int k) {
            if (p == r) return nums[p];
            int m = partition(nums, p, r);
            if (m == k) {
                return nums[m];
            } else if (k < m) {
                return findKthLargest(nums, p, m-1, k);
            } else {
                return findKthLargest(nums, m+1, r, k);
            }
        }
};


int main() {
    vector<int> nums = {2,2,2,2,2,2};
    cout << Solution().findKthLargest(nums, 2) << endl;
    return 0;
}
