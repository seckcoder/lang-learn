#include <string>
#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    bool isValidSubIP(const string &s, int start, int len) {
        if (len == 1) return true;
        if (s[start] == '0') return false;
        if (std::stoi(s.substr(start,len)) > 255) return false;
        return true;
    }
    vector<string> restoreIpAddresses(string s) {
        vector<string> ip_addr_vec;
        for (int a1 = 1; a1 <= 3; a1++) {
            for (int a2 = 1; a2 <= 3; a2++) {
                for (int a3 = 1; a3 <= 3; a3++) {
                    int a4 = s.length();
                    a4 -= a1 + a2 + a3;
                    if (a4 >= 1 && a4 <= 3) {
                        string ip_addr;
                        if (isValidSubIP(s, 0, a1)) {
                            ip_addr += s.substr(0, a1);
                        } else {
                            goto exit_if;
                        }
                        ip_addr += ".";
                        if (isValidSubIP(s, a1, a2)) {
                            ip_addr += s.substr(a1, a2);
                        } else {
                            goto exit_if;
                        }
                        ip_addr += ".";
                        if (isValidSubIP(s, a1+a2, a3)) {
                            ip_addr += s.substr(a1+a2, a3);
                        } else {
                            goto exit_if;
                        }
                        ip_addr += ".";
                        if (isValidSubIP(s, a1+a2+a3, a4)) {
                            ip_addr += s.substr(a1+a2+a3, a4);
                        } else {
                            goto exit_if;
                        }
                        ip_addr_vec.push_back(ip_addr);
exit_if:
                        ;
                    }
                }
                // next loop
            }
        }
        return ip_addr_vec;
    }
};

int main() {
  vector<string> res = Solution().restoreIpAddresses("172162541");
  for (int i = 0; i < res.size(); i++) {
    cout << res[i] << endl;
  }
  return 0;
}
