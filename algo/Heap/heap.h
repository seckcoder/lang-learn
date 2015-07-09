#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <unordered_map>
using std::vector;
using std::unordered_map;

/* A heap implementation support direct erase operation */
template <class T, class Comp = std::less<T>>
class Heap {
    public:
#define PAR(i) ((i)>>1)
#define LEFT(i) ((i)<<1)
// using brackets to group (i)<<1 since << has lower precedence to +
#define RIGHT(i) (((i)<<1)+1)
        vector<T> vec;
        /* using a hashmap to keep track of the index so
         * that we could erase elements in heap in O(lg(n))
         */
        unordered_map<T, size_t> idxmap;
        Comp comp;
        Heap():vec(1){}
        explicit Heap(Comp comp_):comp(comp_),vec(1) {}
        void insert(const T &v) {
            if (idxmap.count(v)) return;
            vec.push_back(v);
            idxmap[v] = vec.size()-1;
            bottom_up(vec.size()-1);
        }
        /* maintain heap bottom-up */
        void bottom_up(size_t cur) {
            for (size_t p = PAR(cur);
                    p >= 1 && !comp(vec[p], vec[cur]);
                    p = PAR(cur)) {
                swap(p, cur);
                cur = p;
            }
        }
        /* maintain heap top-down */
        void top_down(size_t cur) {
            size_t n = vec.size()-1;
            for (; ; ) {
                size_t l = LEFT(cur);
                size_t r = RIGHT(cur);
                size_t max = cur;
                if (l <= n && !comp(vec[max], vec[l])) max = l;
                if (r <= n && !comp(vec[max], vec[r])) max = r;
                if (max == cur) break;
                else if (max == l) swap(cur, l), cur = l;
                else if (max == r) swap(cur, r), cur = r;
            }
        }
        void swap(size_t a, size_t b) {
            /* be careful with the swap procedure */
            if (a != b) {
                std::swap(vec[a], vec[b]);
                idxmap[vec[a]] = a;
                idxmap[vec[b]] = b;
            }
        }
        void erase(const T &v) {
            if (!idxmap.count(v)) return;
            size_t idx = idxmap[v];
            swap(idx, vec.size()-1);
            idxmap.erase(v);
            vec.pop_back();
            top_down(idx);
            bottom_up(idx);
        }
        void pop() {
            swap(1, vec.size()-1);
            idxmap.erase(vec.back());
            vec.pop_back();
            top_down(1);
        }
        const T& top() const {
            return vec[1];
        }
        bool empty() const {
            return vec.size() == 1;
        }
};

#endif
