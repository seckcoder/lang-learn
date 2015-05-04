#include <unordered_set>
#include <string>
#include <iostream>

using namespace std;

// O(n) time complexity solution
// Intuition:
//
// For this kind of consecutive characters problem, we can always start by fixing a point.
//
// Here, we fix the starting point(left), then we look for the longest sequence we can construct.
// We find repeative chars when reaching the right most point.
// At this time, we need relocate left and right to provide best performance.
// For this problem, apparently, we don't need to move right. We just need to move
// left point by fixing right point until we reach the left place that doesn't have
// repeative chars.
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        std::unordered_set<char> char_set;
        int max_len = 0;
        
        // one loop
        int left = 0, right = 0;
        
        while (right < s.length()) {
            if (char_set.find(s[right]) != char_set.end()) {
                char_set.erase(s[left]);
                left += 1;
            } else {
                char_set.insert(s[right]);
                right += 1;
                max_len = std::max(max_len, right-left);
            }
        }
        return max_len;
    }
};


int main() {
  Solution sol;
  cout << sol.lengthOfLongestSubstring("abcabcbb") << endl;
  return 0;
}
