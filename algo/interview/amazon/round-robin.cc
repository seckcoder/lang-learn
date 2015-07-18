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
    vector<Job> jobs;
    CList<Job*> que; //`que` is a circular list which can be used to simulate round-robin
    const int q; // unit execution time
    typedef CList<Job*>::iterator JobIter;
    JobIter last_iter; /* the next job to execute */
    int last_t; /* the last time we execute a job */
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
      /* First we run a simulation of the jobs.
       * Time complexity of the following simulation is O(100*n)
       * */
      for (int i = 0; i < n; i++) {
        /* If we have a list of jobs and the last time we execute a job
         * is smaller than the current job's arrival time, we run all the
         * jobs in the circular-list
         */
        while (!jobs.empty() && last_t < jobs[i].a) {
          runNext();
        }
        que.push_back(&jobs[i]);
        /* If last_iter points to the fake node, we know that the next
         * job to execute is actually the newly added job. So we step back the
         * last_iter to point to the newly added job.
         */
        if (last_iter == que.end()) {
          --last_iter;
        }
      }

      /* It's possible that after the above simulation, last_iter points
       * to the middle of the list. So we execute the jobs after last_iter once
       * so that the next job to execute is the first job of the list
       */
      while (last_iter != que.end()) {
        runNext();
      }
      /* After the above simulation, we can treat the rest jobs in the
       * circular list like this:
       *    All of the jobs starts at time last_t. With this assumption,
       *    we could easily calculate the finish time in O(n^2) time.
       *
       *    P.S., if this is a real round-robin queue, i.e., each run will
       *    take time q(no less, no more), then we could calculate the finish
       *    time in O(n*lg(n)). But this question, it requests that when
       *    the rest running_time of a job < q, then the execution time should
       *    be < q.
       */
      calcFinishTime();
      double sum_t = 0.0;
      for (int i = 0; i < jobs.size(); i++) {
        const Job &job = jobs[i];
        /* waiting_time = finish_time - running_time - arrival_time */
        sum_t += job.f - job.a - running_t[i];
      }
      return ROUND(sum_t / n);
    }
    void runNext() {
      /* If last_iter points to the end of the list, we need to move
       * to the next since que.end() is a fake node
       */
      if (last_iter == que.end()) ++last_iter;
      int runtime = std::min(q, (*last_iter)->r);
      last_t += runtime;
      (*last_iter)->r -= runtime;
      if ((*last_iter)->r == 0) {
        /* remove a job when we don't need to execute it */
        (*last_iter)->f = last_t;
        /* last_iter will point to the next one */
        last_iter = que.erase(last_iter);
      } else {
        /* last_iter will point to the next one */
        ++last_iter;
      }
    }

    void calcFinishTime() {
      for (auto it1 = que.begin(); it1 != que.end(); ++it1) {
        int rt1 = (*it1)->r;
        /* period is the number of times that the job will get executed */
        int rt1_periods = PERIOD(rt1, q);
        int ft1 = 0;
        /* suppose the index of current job is i.
         * Then:
         * finish_t(i) = sum{running_t[j] if PERIOD(j) < PERIOD(i)} +
         *               sum{running_t[j] if PERIOD(j) == PERIOD(i) and j <= i} +
         *               sum{(PERIOD(j)-1) * q if PERIOD(j) == PERIOD(i) and j > i}
         */

        /* First consider jobs in front of i */
        for (auto it2 = que.begin(); it2 != it1; ++it2) {
          int rt2 = (*it2)->r;
          int rt2_periods = PERIOD(rt2, q);
          if (rt2_periods <= rt1_periods) {
            ft1 += rt2;
          } else {
            ft1 += rt1_periods * q;
          }
        }
        /* Next consider jobs after i */
        for (auto it2 = (it1+1); it2 != que.end(); ++it2) {
          int rt2 = (*it2)->r;
          int rt2_periods = PERIOD(rt2, q);
          if (rt2_periods < rt1_periods) {
            ft1 += rt2;
          } else {
            ft1 += (rt1_periods-1)*q;
          }
        }
        ft1 += rt1; /* finaly the execution time of current job */
        (*it1)->f = ft1 + last_t; /* last_t */
      }
    }
};

double run_test(const vector<int> &at, const vector<int> &rt, int q) {
  RoundRobin rb(at, rt, q);
  return rb.avg_waiting(rt);
}

int main() {
  assert(run_test({0,1,3,9}, {2,1,7,5}, 2) == 1.000000);
  assert(run_test({0,2,4,5}, {7,4,1,4}, 3) == 6.250000);
  return 0;
}
