#include <iostream>
#include "heap.h"
using namespace std;

/* basic usage of the heap */
void basic_usage() {
    /* maximum heap */
    Heap<int, std::greater<int>> heap;
    for (int i = 10; i >= 1; i--) heap.insert(i);
    while (!heap.empty()) {
        cout << heap.top() << " ";
        heap.pop();
    }
    for (int i = 10; i >= 1; i--) heap.insert(i);
    for (int i = 1; i <= 10; i++) heap.erase(i);
}


class Job {
    public:
        int priority;
        int id;
        Job() {}
        explicit Job(int id_, int p):id(id_), priority(p) {}
        /* provide a equal_to function */
        bool operator==(const Job &j) const {
            return id == j.id;
        }
};

/* override the default hash function for job */
namespace std {
    template <> struct hash<Job>
    {
        size_t operator()(const Job &job) const {
            return job.id;
        }
    };
};

/* implement a priority queue with heap */
void simulate_priority_queue() {
    /* Jobs with higer priority first */
    auto comp_job = [](const Job &j1, const Job &j2) {
        return j1.priority > j2.priority;
    };
    Heap<Job, decltype(comp_job)> pq(comp_job);
    vector<int> priorities {4,2,10,4,5,1,8,1,4,2,7};
    for (int i = 0; i < priorities.size(); i++) {
        pq.insert(Job(i, priorities[i]));
    } 

    while (!pq.empty()) {
        cout << pq.top().priority << " ";
        pq.pop();
    }
}

int main() {
    simulate_priority_queue();
    return 0;
}
