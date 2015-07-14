#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define lowbit(x) ((x) & (-(x)))
// A[0, k). Time complexity is O(lg(n))
int query(const vector<int> &bit, int k) {
    int ans = 0;
    for (int i = k; i > 0; i -= lowbit(i))
        ans += bit[i];
    return ans;
}

// Time complexity is O(lg(n))
void modify(vector<int> &bit, int i, int delta) {
    for (int j = i; j < bit.size(); j += lowbit(j))
        bit[j] += delta;
}

vector<int> calcFinishTime(vector<int> &running_t) {
    int n = running_t.size();
    vector<int> finish_t(n, 0);
    vector<pair<int,int>> running_pairs(n);
    for (int i = 0; i < n; i++) {
        running_pairs[i].first = running_t[i];
        running_pairs[i].second = i;
    }
    std::sort(running_pairs.begin(), running_pairs.end());

    vector<int> bit(n+1, 0);
    for (int i = 1; i <= n; i++) {
        modify(bit, i, 1);
    }

    int less_sum = 0;
    int last_less_idx = -1;
    for (int i = 0; i < n; i++) {
        if (i > 0 && running_pairs[i].first > running_pairs[i-1].first) {
            less_sum += (i - last_less_idx - 1) * running_pairs[i-1].first;
            last_less_idx = i-1;
        }
        int j = running_pairs[i].second;
        /* e: count(j: running_t[j] >= running_t[i])
         * f: count(j: running_t[j] >= running_t[i] and j <= i)
         * */
        int e = (n - last_less_idx - 1);
        int f = query(bit, j+1);
        finish_t[j] = less_sum + (running_t[j]-1) * e + f;
        modify(bit, j+1, -1);
    }
    return finish_t;
}

int main() {
    vector<int> running_t = {8,1,3,3,8};
    vector<int> finish_t = calcFinishTime(running_t);
    // 22,2,11,12,23
    for (auto x: finish_t) cout << x << " ";
    cout << endl;
    return 0;
}
