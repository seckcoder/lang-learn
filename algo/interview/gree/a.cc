#include <iostream>
#include <unordered_set>
using namespace std;
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    int n,k;
    cin >> n >> k;
    typedef unordered_set<int> HashSet;
    HashSet num_sets;
    int num_pairs = 0;
    for (int i = 0; i < n; i++) {
        int tmp_num;
        cin >> tmp_num;
        if (num_sets.find(tmp_num - k) != num_sets.end()) {
            num_pairs += 1;
        }
        if (num_sets.find(tmp_num + k) != num_sets.end()) {
            num_pairs += 1;
        }
        num_sets.insert(tmp_num);
    }
    cout << num_pairs << endl;
    return 0;
}
