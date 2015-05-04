
class CmpIndex {
public:
    vector<int> *pnum;
    CmpIndex(vector<int> &numbers) {
        pnum = &numbers;
    }
    bool operator()(int idx1, int idx2) {
        return (*pnum)[idx1] < (*pnum)[idx2];
    }
};


// O(nlog(n))
class Solution1 {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
      vector<int> ans;
      int n = numbers.size();
      std::vector<int> indices(n);
      
      for (int i = 0; i < n; i++) {
          indices[i] = i;
      }
      CmpIndex cmp_op(numbers);
      std::sort(indices.begin(), indices.end(), cmp_op);
      
      for (int i = 0; i < n-1; i++) {
        int num_i = numbers[indices[i]];
        int j = binSearch(indices, numbers, i+1, n-1, target - num_i);
        if (j >= 0) {
          ans.push_back(std::min(indices[i]+1, j+1));
          ans.push_back(std::max(indices[i]+1, j+1));
          return ans;
        }
      }
    }
    int binSearch(const vector<int> &indices, const vector<int> &numbers, int p, int r, int v) {
      while (p <= r) {
        int m = (p+r)>>1;
        int num_m = numbers[indices[m]];
        if (num_m == v) {
          return indices[m];
        } else if (num_m < v) {
          p = m+1;
        } else {
          r = m-1;
        }
      }
      return -1;
    }
};

// Solution using hashmap
// O(1)
class Solution {
  public:
    vector<int> twoSum(vector<int> &numbers, int target) {
      typedef std::unordered_map<int, int> HashMap;
      HashMap num_idx_map;
      for (int i = 0; i < numbers.size(); i++) {
        int num_i = numbers[i];
        int num_j = target - num_i;
        if (num_idx_map.find(num_j) != num_idx_map.end()) {
          int j = num_idx_map[num_j];
          return {j+1, i+1};
        } else {
          num_idx_map[num_i] = i;
        }
      }
    }
};
