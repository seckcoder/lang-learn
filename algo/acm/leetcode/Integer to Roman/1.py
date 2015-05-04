# stupid question...

base_roman_map = {
    1000: 'M',
    500: 'D',
    100: 'C',
    50: 'L',
    10: 'X',
    5: 'V',
    1: 'I'
}

base_nums = [1000, 500, 100, 50, 10, 5, 1]

class Solution:
    # @return a string
    def intToRoman(self, num):
        roman_numeral = ""
        base_idx = 0
        while num > 0:
            base_idx = self.findBase(num, base_idx)
            base_count = num / base_nums[base_idx]
            # four cases.
            if base_count == 9:
                roman_numeral += base_roman_map[base_nums[base_idx]] + base_roman_map[base_nums[base_idx-2]]
            elif base_count >= 5:
                roman_numeral += base_roman_map[base_nums[base_idx-1]] + base_roman_map[base_nums[base_idx]] * (base_count - 5)
            elif base_count == 4:
                roman_numeral += base_roman_map[base_nums[base_idx]] + base_roman_map[base_nums[base_idx-1]]
            else:
                roman_numeral += base_roman_map[base_nums[base_idx]] * base_count
            num -= base_count * base_nums[base_idx]
        return roman_numeral
    
    # find new base_idx starting from base_idx
    def findBase(self, num, base_idx):
        # assert num >= 1, so base_idx < len(base_nums)
        # Note we always use 1xxx as the base
        while base_nums[base_idx] > num:
            base_idx += 2
        return base_idx
        
