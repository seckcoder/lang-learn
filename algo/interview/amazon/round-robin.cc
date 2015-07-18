#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include "circular-list.hpp"
using namespace std;



#define PERIOD(t,q) (int(std::ceil(double(t)/double(q))))
#define precision 1000000
#define ROUND(d) ((std::floor(d*precision))/precision)

struct Job {
  public:
    int a, r, f; /* arrival, running, finish
                  * Note here the finish time is actually the last time
                  * the job starts to execute.
                  */
    Job() {}
    Job(int a_, int r_)
        :a(a_), r(r_), f(0) {}
};

ostream& operator<<(ostream &os, const Job &job) {
  os << job.a << " " << job.r << " " << job.f;
  return os;
}


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
    double avg_waiting(const vector<int> &running_t) {
      last_t = 0;
      last_iter = que.begin();
      for (int i = 0; i < n; i++) {
        while (!jobs.empty() && last_t < jobs[i].a) {
          runNext();
        }
        que.push_back(&jobs[i]);
        if (last_iter == que.end()) {
          --last_iter;
        }
      }

      while (last_iter != que.end()) {
        // cout << "ha " << *(*last_iter) << endl;
        runNext();
      }
      calcFinishTime();
      double sum_t = 0.0;
      for (int i = 0; i < jobs.size(); i++) {
        const Job &job = jobs[i];
        // cout << job.a << " " << job.f << endl;
        sum_t += job.f - job.a - running_t[i];
      }
      // cout << ROUND(sum_t / n) << endl;
      return ROUND(sum_t / n);
    }
    void runNext() {
      if (last_iter == que.end()) ++last_iter;
      int runtime = std::min(q, (*last_iter)->r);
      last_t += runtime;
      (*last_iter)->r -= runtime;
      // cout << "running:  " << *(*last_iter) << endl;
      if ((*last_iter)->r == 0) {
        (*last_iter)->f = last_t;
        last_iter = que.erase(last_iter);
      } else {
        ++last_iter;
      }
    }

    void calcFinishTime() {
      for (auto it1 = que.begin(); it1 != que.end(); ++it1) {
        int rt1 = (*it1)->r;
        int rt1_periods = PERIOD(rt1, q);
        int ft1 = 0;
        /* for it2 < it1 */
        for (auto it2 = que.begin(); it2 != it1; ++it2) {
          int rt2 = (*it2)->r;
          int rt2_periods = PERIOD(rt2, q);
          if (rt2_periods <= rt1_periods) {
            ft1 += rt2;
          } else {
            ft1 += rt1_periods * q;
          }
        }
        /* for it2 > it1 */
        for (auto it2 = (it1+1); it2 != que.end(); ++it2) {
          int rt2 = (*it2)->r;
          int rt2_periods = PERIOD(rt2, q);
          if (rt2_periods < rt1_periods) {
            ft1 += rt2;
          } else {
            ft1 += (rt1_periods-1)*q;
          }
        }
        ft1 += rt1;
        (*it1)->f = ft1 + last_t;
      }
    }
};

void testCircularList() {
    CList<int> lst;
    for (int i = 1; i <= 4; i++) {
        lst.push_back(i);
    }
    for (auto v: lst) {
      cout << v << endl;
    }
}


double run_test(const vector<int> &at, const vector<int> &rt, int q) {
  RoundRobin rb(at, rt, q);
  return rb.avg_waiting(rt);
}

int main() {
  assert(run_test({0,1,3,9}, {2,1,7,5}, 2) == 1.000000);
  assert(run_test({0,2,4,5}, {7,4,1,4}, 3) == 6.250000);
  return 0;
}
