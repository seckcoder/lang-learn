#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Every time, we consider a task numbered i, and when it comes to the last second of ith task, all the tasks shorter than it has finished. We only need to sum their cost up. For the tasks not shorter than ith task, we assume the ith task takes Ti seconds. The tasks not shorter than it and the ith task itself both work for (Ti - 1) seconds, and for their own (Ti)th of processing, only the tasks before the ith task works. Sum them up, and you'll get the answer.

Take the sample as an example:

For the 1st task, it takes 8 seconds, and the tasks shorter than it has 1 + 3 + 3 = 7 seconds, then it takes 7 seconds for it and the 5th task, so the value is 7 * 2 = 14 seconds. Then there's no task before ith task, so we only need to add 1 second for the 1st task itself. The result is 7 + 14 + 1 = 22

Maybe it's not clear enough, let's look at the 3rd task, it takes 3 seconds, and only 1 task is shorter than it(the second one which takes 1 second). And all the left tasks take the 3 - 1 = 2 seconds, it's 4 * 2 = 8 seconds. Finally, there's only one task left before it, so only it runs the 3rd time. We add it and the 3rd time processing itself. The result is 1 + 8 + 1 + 1 = 11 seconds.

When coding, you need to remember the sequence number of a task and sort them by their processing time. Then all the tasks short then them are before it. The left job is a linear time processing, and the sort takes O(nlogn) time complexity, which is fast enough to finish the job.
*/


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

vector<long long int> calcFinishTime(vector<int> &running_t) {
    int n = running_t.size();
    vector<long long int> finish_t(n, 0);
    vector<pair<int,int>> running_pairs(n);
    for (int i = 0; i < n; i++) {
        running_pairs[i].first = running_t[i];
        running_pairs[i].second = i;
    }
    std::sort(running_pairs.begin(), running_pairs.end(), [&](
          const pair<int,int> &p1, const pair<int,int> &p2) {
        return p1.first < p2.first || (p1.first == p2.first && p1.second > p2.second);
        });

    vector<int> bit(n+1, 0);
    for (int i = 1; i <= n; i++) {
        modify(bit, i, 1);
    }

    long long int less_sum = 0;
    int last_less_idx = -1;
    for (int i = 0; i < n; i++) {
        if (i > 0 && running_pairs[i].first > running_pairs[i-1].first) {
            less_sum += ((long long int)(i - last_less_idx - 1)) * running_pairs[i-1].first;
            last_less_idx = i-1;
        }
        int j = running_pairs[i].second;
        /* e: count(j: running_t[j] >= running_t[i])
         * f: count(j: running_t[j] >= running_t[i] and j <= i)
         * */
        int e = (n - last_less_idx - 1);
        int f = query(bit, j+1);

        finish_t[j] = less_sum + ((long long int)(running_t[j]-1)) * e + f;
        modify(bit, j+1, -1);
    }
    return finish_t;
}

int main() {
  int n; scanf("%d\n", &n);
  vector<int> running_t(n);
  for (int i = 1; i <= n; i++) {
    scanf("%d\n", &running_t[i-1]);
  }
  
  for (auto t:calcFinishTime(running_t)) {
    printf("%lld\n", t);
  }
  return 0;
}
