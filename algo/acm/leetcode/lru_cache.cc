#include <iostream>
#include <map>
#include <cassert>
#include <list>
using std::map;
using std::cout;
using std::endl;

class LRUCache{
 public:
  typedef std::list<std::pair<int, int> > lruq_type;
  typedef map<int, lruq_type::iterator> kvmap_type;
  kvmap_type kv_;
  lruq_type lruq_;
  int capacity_;
  LRUCache(int capacity) {
    capacity_ = capacity;
  }

  int get(int key) {
    kvmap_type::iterator it = kv_.find(key);
    if (it == kv_.end()) {
      return -1;
    } else {
      int val = it->second->second;
      int key = it->first;
      update_lru(it->second, key, val);
      return val;
    }
  }
  void update_lru(lruq_type::iterator &it, int key, int val) {
    lruq_.erase(it);
    lruq_.push_front(std::pair<int,int>(key, val));
    it = lruq_.begin(); // update kv map iter
  }

  void add(int key, int value) {
    lruq_.push_front(std::pair<int,int>(key,value));
    kv_.insert(std::pair<int, lruq_type::iterator>(key, lruq_.begin()));
  }
  void set(int key, int value) {
    kvmap_type::iterator it = kv_.find(key);
    if (it == kv_.end()) {
      if (kv_.size() >= capacity_) {
        //cout << "here" << endl;
        std::pair<int, int> lruq_iter = lruq_.back();
        int key_to_remove = lruq_iter.first;
        kv_.erase(key_to_remove);
        lruq_.pop_back();
        add(key, value);
      } else {
        add(key, value);
      }
    } else {
      update_lru(it->second, key, value);
    }
  }
};

int main() {
  LRUCache cache(3);
  cache.set(1,1);
  cache.set(2,2);
  cache.set(3,3);
  cache.set(4,4);
  cout << cache.get(4) << endl;
  cout << cache.get(3) << endl;
  cout << cache.get(2) << endl;
  cout << cache.get(1) << endl;
  cache.set(5,5);
  cout << cache.get(1) << endl;
  cout << cache.get(2) << endl;
  cout << cache.get(3) << endl;
  cout << cache.get(4) << endl;
  cout << cache.get(5) << endl;
  /*cache.set(1, 2);
  cache.set(3, 4);
  assert(cache.get(3) == 4);
  assert(cache.get(2) == -1);
  cache.set(5, 6);
  assert(cache.get(1) == -1);
  assert(cache.get(3) == 4);*/
  return 0;
}
