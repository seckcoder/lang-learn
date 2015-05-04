
/* KEY IDEA:
 * First it's intuitive to map title to number.
 * For the reverse process, we only need to map back
 */
class Solution {
public:
    /*
     * num = num * 26 + (s[i] - 'A' + 1)
     * => s[i] = (num - 1) % 26 + 'A'.
     * 
     * Note we need to minus 1 to num since we using modulo operation. 
     * Reasoning:
     *  A-Z has 26 numbers. So 26 is period or base.
     *  Then we need to modulo 26.
     *  However, n % 26 ranges from 0 to 25 while 
     *  (s[i] - 'A' + 1) ranges from 1 to 26.
     *  So n % 26 != (s[i] - 'A' + 1).
     *  However, after we move 1 to the left, i.e., we got:
     *  num - 1 = num * 26 + (s[i] - 'A'), then
     *  (s[i] - 'A') ranges from 0 to 25. So the formula
     *  matches the modulo requirement.
     * 
     */
    int titleToNumber(string s) {
        int num = 0;
        for (int i = 0; i < s.length(); i++) {
            num = num * 26 + (s[i] - 'A' + 1);
        }
        return num;
    }
    string convertToTitle(int n) {
      string s;
      while (n) {
        char c = 'A';
        c += (n-1) % 26;
        s.append(1, c);
        n /= 26;
      }
      return s;
    }
};


