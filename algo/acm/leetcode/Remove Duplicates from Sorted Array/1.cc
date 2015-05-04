class Solution {
public:
    int removeDuplicates(int A[], int n) {
        if (n == 0) return 0;
        int cur = 1, len = 1;
        while (cur < n) {
            if (A[cur] == A[len-1]) {
                cur += 1;
            } else {
                std::swap(A[cur], A[len]);
                len += 1;
                cur += 1;
            }
        }
        return len;
    }
};
