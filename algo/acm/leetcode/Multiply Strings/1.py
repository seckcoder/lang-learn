

def c2i(c):
    return ord(c) - ord('0')

def i2c(i):
    return chr(ord('0') + i)

class Solution:
    # @param num1, a string
    # @param num2, a string
    # @return a string
    def multiply(self, num1, num2):
        # Point: First check if is zer0. This will reduce time complexity of Point 3
        if num1 == "0" or num2 == "0":
            return "0"
        num1 = list([c2i(c) for c in reversed(num1)])
        num2 = list([c2i(c) for c in reversed(num2)])
        # Point1: Multiply two numbers, the max len is the sum of the len
        num = [0] * (len(num1) + len(num2))
        for i,v1 in enumerate(num1):
            carry = 0
            for j,v2 in enumerate(num2):
                v = v1 * v2 + num[i+j] + carry
                num[i+j] = v % 10
                carry = v / 10
            # Point2: no for loops needed. After one iteration, carry < 10
            num[i+len(num2)] = carry

        # Point3: In case we have some number equation to 0.
        num_len = len(num1) + len(num2)
        while num_len > 0 and num[num_len-1] == 0:
            num_len -= 1

        return ''.join([i2c(i) for i in reversed(num[:num_len])])


print Solution().multiply("999", "999")
