
/* Note: 1.0 = 1 */
class Solution {
public:
    int compareVersion(string version1, string version2) {
        int cur1 = 0, cur2 = 0;
        while (cur1 < version1.length() || cur2 < version2.length()) {
            int v1_cur_level = parseCurLevelVersion(version1, cur1);
            int v2_cur_level = parseCurLevelVersion(version2, cur2);
            if (v1_cur_level < v2_cur_level) {
                return -1;
            } else if (v1_cur_level > v2_cur_level) {
                return 1;
            }
        }
        return 0;
    }
    /* if cur >= version.length(), we simply return 0 */
    int parseCurLevelVersion(string version, int &cur) {
        int version_number = 0;
        while (cur < version.length() && version[cur] != '.') {
            version_number = version_number * 10 + int(version[cur] - '0');
            cur += 1;
        }
        cur += 1;
        return version_number;
    }
};
