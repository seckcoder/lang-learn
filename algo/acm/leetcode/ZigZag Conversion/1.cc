#include <string>
#include <iostream>

using namespace std;

/*
 * Example:
 *
 * a     g    m
 * b   f h  l n
 * c e   i k  o
 * d     j        
 * 
 * So first row is 
 *
 * a -> g -> m
 *
 * Second row is
 * 
 * (We collect two elements once for these rows since
 * idx(h) - idx(b) = idx(l) - idx(f) = period
 * b,f -> h,l -> n
 *
 * ...
 *
 * Last row is
 *
 * d -> j
 */
class Solution {
public:
    string convert(string s, int numRows) {
        string res;
        int n = s.length();
        int period;
        /* NOTE: pay attention to numRows = 1 condition. At
         * that time, period should equal to 1.
         */
        if (numRows == 1) period = 1;
        else period = 2 * numRows - 2;
        // first row
        int i1 = 0, i2 = 0;
        while (i1 < n) {
            res.append(1, s[i1]);
            i1 += period;
        }
        
        // second row to (numRows-1) th row
        for (int i = 1; i < numRows-1; i++) {
            i1 = i; 
            i2 = period - i;
            while (i1 < n && i2 < n) {
                res.append(1, s[i1]);
                res.append(1, s[i2]);
                i1 += period;
                i2 += period;
            }
            // i1 < i2. so it's possible that we still have i1 not added
            if (i1 < n) {
                res.append(1, s[i1]);
            }
        }
        
        // last row
        if (numRows >= 2) {
            i1 = numRows - 1;
            while (i1 < n) {
                res.append(1, s[i1]);
                i1 += period;
            }
        }
        return res;
    }
};

int main()
{
  Solution sol;
  cout << sol.convert("P", 2) << endl;
  return 0;
}
