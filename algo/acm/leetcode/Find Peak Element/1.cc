class Solution {
public:
    int findPeakElement(const vector<int> &num) {
        if (num.size() == 0) return -1;
        
        int p = -1, r = num.size();
        
        while (p <= r) {
            int m = (p+r)/2;
            if (m == 0) {
                if (r == 1) {
                    return m;
                } else {
                    // r == 2
                    if (num[0] < num[1]) return 1;
                    else return 0;
                }
            } else if (m == num.size()-1) {
                // then p = n-2
                return m;
            } else {
                // 0 < m < n-1
                if (num[m-1] < num[m] && num[m] > num[m+1]) return m;
                else
                if (num[m-1] <  num[m] && num[m] < num[m+1]) {
                    p = m;
                } else
                if (num[m-1] > num[m] && num[m] > num[m+1]) {
                    r = m;
                } else
                if (num[m-1] > num[m] && num[m] < num[m+1]) {
                    p = m;
                }
            }
        }
        return -1;
    }
};
