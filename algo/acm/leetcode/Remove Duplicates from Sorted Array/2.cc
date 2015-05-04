class Solution {
public:
    int removeDuplicates(int A[], int n) {
        if (n == 0) return 0;
        int len = 1, cur = 1;
        // introduce a variable to record
        // the number of duplicates
        int duplicate_num = 1;
        while (cur < n) {
            if (A[cur] == A[len-1]) {
                duplicate_num += 1;
                if (duplicate_num > 2) {
                    // ignore cur
                } else {
                    // swap in
                    std::swap(A[cur], A[len]);
                    len += 1;
                }
            } else {
                std::swap(A[cur], A[len]);
                len += 1;
                duplicate_num = 1;
            }
            cur += 1;
        }
        return len;
    }
};
