

// O(n) method.
// Proof:
//
//         a          b-1 b
// --------|-----------|  | -------
//
//
// Suppose we just move the end from b to b-1, and start = a.
//
// So we know:
// h[a] >= b[b:] and h[a] >= h[:a].  This is easy to prove
//
// Suppose max_area[:] is the final result. area(b) = (b-a) * height[a]
// We also claim that
//
// 1) The max area we can get for height b.
// 2) exist b' > b, such that area(b') > area(b)
// 
//
// Now we prove this claim based on two cases
//
//
// 1) Suppose for all a' < a, h[a'] < h[b]. Then we know, area(b) is the max
// area we can get for height b.
//
// 2) Suppose exist a' < a, h[a'] >= h[b]. At this time,
//  
//    h[a] >= h[a'] >= h[b].
//
//    Also, as a' < a, and h[a'] >= h[b], then exist b' > b, and 
//    h[a'] <= h[b'] and that b' makes the start transfer from a' to a'+1.
//
//    So we have:
//
//    h[a'] <= h[b'] <= h[a]
//
//    => h[b] <= h[a'] <= h[b'] <= h[a]
//
//    => We also know that exist a' < a'' <= a, this a'' makes the end transfer
//    from b' to b'-1. 
//
//    => h[a] >= h[a''] >= h[b']
//
//    => The area we get when transfer end from b' to b'-1 is:
//    area(b') = (b' - a'') * h[b']
//
//    As b' > b, a'' < a and h[b'] >= h[b]
//    => area(b') > area(b).
//
// Based on the above claim, it's easy to prove that our algorithm is right.

class Solution {
public:
    int maxArea(vector<int> &height) {
        vector<int> left_highest; // stack
        int max_area = 0;
        int start = 0, end = height.size()-1;
        while (start < end) {
            if (height[start] < height[end]) {
                max_area = std::max(max_area, (end-start) * height[start]);
                start += 1;
            } else {
                max_area = std::max(max_area, (end-start) * height[end]);
                end -= 1;
            }
        }
        return max_area;
    }
};


