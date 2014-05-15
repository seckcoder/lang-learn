// http://oj.leetcode.com/problems/regular-expression-matching/

// const means content in s/p can't be modified.
int c_solution(const char *s, const char *p) {
}

class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        int ans = c_solution(s, p);
        if (ans == 1) {
            return true;
        } else {
            return false;
        }
    }
};
