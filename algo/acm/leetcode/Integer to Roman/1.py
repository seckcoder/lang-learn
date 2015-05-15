# stupid question...


"""
Algo:
    num = a1 * 1 + a2 * 2 + a3 * 100 + a4 * 1000
    We need to represent a1,a2,a3,a4 and concatenate it as a4a3a2a1
    Generally,
        if ai == 9
            then represent it as a higher order character(10th) with one lower order
            character(1th) on the left.
            for example: 9 -> IX  90 -> XC
        else if ai == 4
            then represent it as a higher order character(5th) with one lower
            order character(1th) on the left
            for example: 4 -> IV 40 -> XL
        else if 5 <= ai < 9
            then represent it as higher order character(5th) with lower order
            characters(1th) on the right
            for example: 8 -> VIII 80 -> LXXX
        else if 0 <= ai < 4
            then represent it as lower order characters(1th)
            for example: 3 -> III 30 -> XXX
"""

base_roman_map = {
    1000: 'M',
    500: 'D',
    100: 'C',
    50: 'L',
    10: 'X',
    5: 'V',
    1: 'I'
}


class Solution:
    # @return a string
    def intToRoman(self, num):
        roman_numeral = ""

        for base in [1000, 100, 10, 1]:
            base_count = num / base
            if base_count == 9:
                roman_numeral += base_roman_map[base] + base_roman_map[base*10]
            elif base_count == 4:
                roman_numeral += base_roman_map[base] + base_roman_map[base*5]
            elif 5<= base_count < 9:
                roman_numeral += base_roman_map[base*5] + base_roman_map[base] * (base_count - 5)
            elif 0 <= base_count < 4:
                roman_numeral += base_roman_map[base] * base_count
            num %= base
        return roman_numeral

print Solution().intToRoman(9)
