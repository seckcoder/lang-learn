
/* Given a list of numbers, 
 * return number of elements that are in front of it and smaller than it
 * i.e., given A, return f(i) = count{j: j < i and A[j] < A[i]};
 *
 * 
 * The basic idea is that, after we remove the numbers greater than A[i], then
 * the rest numbers in front of i is less than i. We can directly return this
 * count in Binary Invert Tree
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define lowbit(x) ((x)&(-(x)))

int query(vector<int> &bit, int k) {
    int v = 0;
    // [j-lowbit(j)+1, j]
    for (int j = k; j > 0; j -= lowbit(j)) {
        v += bit[j];
    }
    return v;
}

void modify(vector<int> &bit, int i, int val) {
    // [j, j+lowbit(j)]
    for (int j = i; j < bit.size(); j += lowbit(j)) {
        bit[j] += val;
    }
}

int main() {

    vector<int> A = {5, 2, 10, 7, 1, 8, 3};
    // vector<int> A = {1,2,3};
    
    vector<pair<int,int>> pairs(A.size());
    for (int i = 0; i < A.size(); i++) {
        pairs[i].first = A[i], pairs[i].second = i;
    }
    std::sort(pairs.begin(), pairs.end(),[&](const pair<int,int> &p1, const pair<int,int> &p2) {
            return p1.first > p2.first || (p1.first == p2.first && p1.second > p2.second);
            });
    vector<int> bit(A.size()+1, 0);
    for (int i = 1; i <= pairs.size(); i++) {
        modify(bit, i, 1);
    }
    
    vector<int> ans(A.size(), 0);
    for (int i = 0; i < pairs.size(); i++) {
        modify(bit, pairs[i].second+1, -1); // remove i
        ans[pairs[i].second] = query(bit, pairs[i].second+1);
    }

    for (int i = 0; i < ans.size(); i++) {
        cout << i << " " << ans[i] << endl;
    }

    return 0;
}
