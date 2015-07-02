
/**
 * Write a function that is given an array of integers. It should return true if
 * any value appears at least twice in the array, and it should return false if
 * every element is distinct.
 */
bool containsDuplicate(std::vector<int> arr) {
    // Write code 
    
    typedef std::unorderd_map<int, size_t> HashMap;
    HashMap hash_map;
    
    for (int i = 0; i < arr.size(); i++) {
        HashMap::iterator it = hash_map.find(arr[i]);
        if (it == hash_map.end()) {
            // we can't find the element in the hash map
            hash_map[arry[i]] = 1;
        } else {
            it->second += 1;
            if (it->second == 2) {
                return true;
            }
        }
    }
    return false;
}


 /**
 * Write a function that is given an array of integers and an integer k. It
 * should return true if and only if there are two distinct indices i and j into
 * the array such that arr[i] = arr[j] and the difference between i and j is at
 * most k.
 */
 // [1, 2, 3, 1, 4], k = 2
 // k = 2, arr[0] and arr[3]. 3 - 0 > 2. 
bool containsNearbyDuplicate(std::vector<int> arr, int k) {
    // Write code here
    
    typedef std::unorderd_map<int, size_t> HashMap;
    HashMap hash_map;
    
    for (int i = 0; i < arr.size(); i++) {
        if (i - k - 1 >= 0) {
            hash_map.delete(arr[i-k-1]); 
        }
        HashMap::iterator it = hash_map.find(arr[i]);
        if (it == hash_map.end()) {
            // we can't find the element in the hash map
            hash_map[arr[i]] = i;
        } else {
            if (i - it->second <= k) return true;
            it->second = i;
        }
    }
    return false; 
}


/**
 * Write a function that is given an array of integers. It should return true if
 * and only if there are two distinct indices i and j into the array such that
 * the difference between arr[i] and arr[j] is at most d and the difference
 * between i and j is at most k.
 */  
 
// n * lg(n)
 
// Implmeentation in SegmentTree
struct SegmentTree {
    SegmentTree(std::vector<int> &arr) {
        pArr = &arr;
    }
    std::vector<int> *pArr;
    
    // segment tree
    int *M;
    int mlen;
};

// build the segment tree and store it in Array M.
void buildSegmentTree(SegmentTree &seg_tree) {
    
}

// whether we have an elements in [p, r]
// it will return -1 if we can't find it.
// If we find it, the returned value should be the index
// of the array
int query(SegmentTree &seg_tree, int p, int r) {
    
}


// d = 5, k = 5
// index: 1 [0, 10], index: 10 [5, 15]
// arr[i] = 8, i = 11

// [3, 8] -> 1
// [8, 13] -> 10


// Implementation in BinarySearchTree
bool containsNearbyAlmostDuplicate(std::vector<int> arr, int k, int d) {
    // Write code 
    
    BinSearchTree tree;
    for (int i = 0; i < arr.size(); i++) {
        if (i-k-1 >= 0) {
            // delete the node with this value in the tree
            tree.del(arr[i-k-1]);
        }
        // query whether there exists a value within a range
        if (tree.query(arr[i], arr[i]+d) || tree.query(arr[i],arr[i]-d)) {
            return true;
        }
        // insert a new value.
        tree.insert(arr[i]);
    }
    return false;
}




