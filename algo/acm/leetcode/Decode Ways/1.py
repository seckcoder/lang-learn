class Solution:
    # @param s, a string
    # @return an integer
    
    def numDecodingsOfOne(self,c):
        if self.canDecodingOfOne(c):return 1
        return 0
    def numDecodingsOfTwo(self,s):
        ans = 0
        if self.canDecodingOfOne(s[0]) and self.canDecodingOfOne(s[1]): ans += 1
        if self.canDecodingOfTwo(s): ans += 1
        return ans
    
    def canDecodingOfOne(self, c):
        return '1' <= c <= '9'
    def canDecodingOfTwo(self,s):
        v = int(s)
        return s[0] != '0' and (1<=v<=26)
    def numDecodings(self, s):
        if not s: return 0
        if len(s) == 1: return self.numDecodingsOfOne(s[0])
        num_decodings = [0] * len(s)
        num_decodings[-1] = self.numDecodingsOfOne(s[-1])
        num_decodings[-2] = self.numDecodingsOfTwo(s[-2:])
        for idx in xrange(len(s)-3,-1,-1):
            if self.canDecodingOfOne(s[idx]):
                num_decodings[idx] += num_decodings[idx+1]
            if self.canDecodingOfTwo(s[idx:idx+2]):
                num_decodings[idx] += num_decodings[idx+2]
        return num_decodings[0]


print Solution().numDecodings("12120")
