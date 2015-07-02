


class Solution {
public:
    string multiply(string num1, string num2) {
        int max_res_len = num1.length() + num2.length() + 1;
        string res(max_res_len, '0');
        int res_len = 0;
        string tmp(max_res_len, '0');
        int tmp_len = 0;
        int num1_len = num1.length(),
            num2_len = num2.length();
        std::reverse(num1.begin(), num1.end());
        std::reverse(num2.begin(),num2.end());
        
        for (int i = 0; i < num2_len; i++) {
            tmp_len = i;
            scale(num1, num1_len, num2[i], tmp, tmp_len, i);
            add(tmp, tmp_len, res, res_len);
            tmp[i] = '0'; // for next loop, we need tmp[0:i] = '0'
        }
        res.resize(res_len);
        std::reverse(res.begin(), res.end());
        return res;
    }
    void scale(string num, int num_len, int scale_v, string &res, int &res_len, int scale_start_idx) {
        for (int i = 0; i < num_len; i++, scale_start_idx++) {
            int tmp_v = scale * int(num[i] - '0');
            tmp_v += int(res[scale_start_idx] - '0');
            res[scale_start_idx] = char('0'+tmp_v % 10);
            res[scale_start_idx+1] += tmp_v / 10;
            //addInt(res[scale_start_idx+1], tmp_v / 10);
        }
        res_len = scale_start_idx;
        while (res[res_len] != '0') res_len += 1;
    }
    void add(string num1, int num1_len, string &num2, int num2_len) {
        for (int i = 0; i < num1_len; i++) {
            int tmp_v = int(num1[i] - '0');
            tmp_v += int(num2[i] - '0');
            num2[i] = char('0' + tmp_v % 10);
            num2[i+1] += tmp_v / 10;
        }
        num2_len = std::max(num2_len, num1_len);
    }
};
