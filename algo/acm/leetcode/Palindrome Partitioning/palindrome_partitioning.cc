#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> palindromes;
        vector<string> cur_palindrome;
        partitionRec(s, 0, palindromes, cur_palindrome);
        return palindromes;
    }
    void partitionRec(string str, int start, vector<vector<string>> &palindromes, vector<string> &cur_palindrome) {
        if (start >= str.length())  {
            palindromes.push_back(cur_palindrome);
            return ;
        }
        for (int i = start; i < str.length(); i++) {
            if (isPalindrome(str, start,i)) {
                cur_palindrome.push_back(str.substr(start,i-start+1));
                partitionRec(str, i+1, palindromes, cur_palindrome);
                cur_palindrome.pop_back();
            }
        }
    }
    bool isPalindrome(string str, int i, int j) {
      while (i < j && str[i] == str[j]) {
        i += 1;
        j -= 1;
      }
      return i >= j;
    }
};
