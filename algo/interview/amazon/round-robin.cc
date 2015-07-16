#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
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
    std::sort(running_pairs.begin(), running_pairs.end(), [&](
          const pair<int,int> &p1, const pair<int,int> &p2) {
        return p1.first < p2.first || (p1.first == p2.first && p1.second > p2.second);
        });

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

struct Job {
  public:
    int a, r, f; /* arrival, running, finish */
    Job() {}
    Job(int a_, int r_)
        :a(a_), r(r_), f(0) {}
};


class RoundRobin {
  public:
    // vector<int> arrival_t, running_t, finish_t;
    vector<Job> jobs;
    CList<Job*> que;
    const int q;
    typedef CList<Job*>::iterator JobIter;
    JobIter last_iter;
    int last_t;
    int n;
    RoundRobin(
            const vector<int> &arrival_t,
            const vector<int> &running_t, int unit):n(arrival_t.size()), q(unit) {
        for (int i = 0; i < n; i++) {
            jobs.push_back(Job(arrival_t[i], running_t[i]));
        }
    }
    double avg_waiting() {
      last_t = 0;
      last_iter = que.begin();
      for (int i = 0; i < n; i++) {
        if (last_t < jobs[i].a) {
          int ex_time = jobs[i].a - last_t;
          while (!que.empty() && ex_time >= 0) {
            runNext(ex_time, i);
          }
        }
        que.push_back(&jobs[i]);
      }
      // after execution, all jobs have arrived
      // calcFinishTime();
      return 0.0f;
    }
    void runNext(int &rest_time, int k) {
      do {
          last_iter++;
      } while (last_iter == que.begin());
      int runtime = std::min(q, last_iter->p->r);
      rest_time -= runtime;
      last_iter->p->r -= runtime;
      last_t += runtime;
      if (last_iter->p->r == 0) {
        last_iter->p->f = last_t;
        que.erase(last_iter);
      }
    }
};

void testCircularList() {
    CList<int> lst;
    for (int i = 1; i <= 4; i++) {
        lst.push_back()
    }
}
int main() {
    testCircularList();
    return 0
    vector<int> arrival_t {0,1,3,9};
    vector<int> running_t {2,1,7,5};
    RoundRobin rb(arrival_t, running_t, 2);
    rb.avg_waiting();
    return 0;
}
