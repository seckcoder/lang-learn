
class Solution {
 public:
  int longestConsecutive(vector<int> &num) {
    unordered_set<int> tbl;
    for (int i = 0; i < num.size(); i++) {
      tbl.insert(num[i]);
    }
    int max_len = 0;
    for (int i = 0; i < num.size(); i++) {
      unordered_set<int>::iterator it = tbl.find(num[i]);
      if (it != tbl.end()) {
        tbl.erase(it);
        int v = num[i];
        int down = v-1, down_len = 0;
        while ((it=tbl.find(down)) != tbl.end()) {
          tbl.erase(it);
          down_len += 1;
          down -= 1;
        }
        int up = v+1, up_len = 0;
        while ((it=tbl.find(up)) != tbl.end()) {
          tbl.erase(it);
          up_len += 1;
          up += 1;
        }
        max_len =std::max(up_len + down_len + 1, max_len);
      }
    }
    return max_len;
  }
};
