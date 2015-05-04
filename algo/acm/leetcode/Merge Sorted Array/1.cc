

// Method 1
class Solution1 {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // copy nums1 to the end of the vector
        for (int i = m+n-1; i>=n; i--) {
            nums1[i] = nums1[i-n];
        }
        
        // merge the two vectors
        
        int vec_idx = 0;
        int i,j;
        for (i = n, j=0; i < m+n && j < n;) {
            if (nums1[i] < nums2[j]) {
                nums1[vec_idx] = nums1[i];
                i += 1;
            } else {
                nums1[vec_idx] = nums2[j];
                j += 1;
            }
            vec_idx += 1;
        }
        
        // copy rest of nums2
        
        while (j < n) {
            nums1[vec_idx] = nums2[j];
            j += 1;
            vec_idx += 1;
        }
    }
};

// Method 2: merge from back

class Solution {
  public:
    void merge(vector<int> &nums1, int m,
        vector<int> &nums2, int n) {
      int vec_idx = m+n-1;
      int i,j;
      for (i = m-1, j = n-1; i >= 0 && j >= 0; ){
        if (nums1[i] > nums2[j]) {
          nums1[vec_idx] = nums1[i];
          i -= 1;
        } else {
          nums1[vec_idx] = nums2[j];
          j -= 1;
        }
        vec_idx -= 1;
      }
      while (j >= 0) {
        nums1[vec_idx] = nums2[j];
        j -= 1;
        vec_idx -= 1;
      }
    }
};
