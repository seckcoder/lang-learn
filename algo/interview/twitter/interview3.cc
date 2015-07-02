
// add in O(1)
// remove in O(1)
// getRandom in O(1)

template <class T>
class DataStructure {
  public:
    vector<T> elems;
    unordered_map<std::pair<T, int> > hash_map;
    void add(T elem) {
      if (hash_map.find(elem) == hash_map.end()) {
        elems.append(elem);
        int idx = elems.size()-1;
        hash_map[elem] = idx;
      }
    }
    void remove(T elem) {
      if (hash_map.find(elem) != hash_map.end()) {
        int idx = hash_map[elem];
        T last_elem = elems.back();
        int last_elem_idx = hash_map[last_elem];
        if (idx == last_elem_idx) {
          // the same element
          elems.pop_back();
          hash_map.remove(elem);
        } else {
          // swap the elem with the last elem
          std::swap(elems[idx], elems[last_elem_idx]);
          // change last elem index in hash map
          hash_map[last_elem] = idx;
          // resize
          elems.resize(elems.size()-1);
          hash_map.remove(elem);
        }
      }
    }
    T getRandom() const {
      int random_idx = random(0, elems.size()-1);
      return elems[random_idx];
    }
};
