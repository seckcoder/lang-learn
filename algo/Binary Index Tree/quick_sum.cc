
/* Given a list of integers, a lot of queries for the sum of the first k numbers
 */


#include <iostream>
#include <vector>
using namespace std;

#define lowbit(x) ((x) & (-(x)))



// bit[i] = sum(i-lowbit(i)+1 <= j <= i, A[i])
//
void build(const vector<int> &A, vector<int> &bit) {
    for (int i = 1; i <= A.size(); i++) {
        bit[i] = A[i-1];
        for (int j = i-1; j > i-lowbit(i); j-=lowbit(j)) {
            bit[i] += bit[j];
        }
    }
}

// A[0, k). Time complexity is O(lg(n))
int sum(const vector<int> &bit, int k) {
    int ans = 0;
    for (int i = k; i > 0; i -= lowbit(i))
        ans += bit[i];
    return ans;
}

// Time complexity is O(lg(n))
void modify(vector<int> &bit, int i, int delta) {
    for (int j = i+1; j < bit.size(); j += lowbit(j))
        bit[j] += delta;
}


int main() {
    vector<int> A {4,2,1,7,3};
    vector<int> bit(A.size()+1);
    build(A,bit);
    for (int i = 1; i < bit.size(); i++) {
        cout << i << " " << sum(bit, i) << endl;
    }
    return 0;
}
