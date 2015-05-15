

/*
 * Note: 
 *
 * 
 * Suppose the highest 1 bit of m is smaller than the highest 1 bit of n
 * i.e, n = 1.... , m = 0.1.. , 
 * Then we know m < 10000 <= n. Also, 10000 & m = 0 => range and between m and n
 * is 0.
 *
 * Therefore, we have position of highest 1 bit of m equal to the position of
 * highest 1 bit of n.
 * 
 * Therefore, we have 
 * n = 1.1...
 * m = 1.0.1.
 * 
 * Also, in the same idea, we know that 
 * m < 1.1000 <= n. Therefore, we have range and between m and n equals 1.0000
 *
 * Therefore, what we want is the common leading 1 of m and n.
 */

class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int cnt = 0;
        while (m != n && m != 0) {
            m >>= 1;
            n >>=1;
            cnt += 1;
        }
        return (m << cnt);
    }
};
