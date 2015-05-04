
num_digits_map = {
    '2': "abc",
    '3': "def",
    '4': "ghi",
    '5': "jkl",
    '6': "mno",
    '7': "pqrs",
    '8': "tuv",
    '9': "wxyz"
}

class Solution:
    # @return a list of strings, [s1, s2]
    def letterCombinations(self, digits):
        if not digits: return []
        combinations = []
        self.recur(0, digits, "", combinations)
        return combinations
    
    def recur(self, i, digits, comb, combinations):
        if i >= len(digits):
            combinations.append(comb)
        else:
            if num_digits_map.has_key(digits[i]):
                for c in num_digits_map[digits[i]]:
                    self.recur(i+1, digits, comb+c, combinations)

print Solution().letterCombinations("2")
