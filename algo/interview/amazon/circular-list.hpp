#ifndef _CIRCULAR_LIST_HPP
#define _CIRCULAR_LIST_HPP


template <class T>
class Node {
  public:
    T* p;
    Node *prev, *next;
    Node(): p(NULL), prev(NULL), next(NULL) {}
    Node(const T v): p(new T(v)), prev(NULL), next(NULL) {}
    ~Node() {
      delete p;
      p = NULL;
    }
};


template <class T>
class Iterator:public std::iterator<std::bidirectional_iterator_tag,
  T, std::size_t> {
    public:
      using typename std::iterator<std::bidirectional_iterator_tag, T, std::size_t>::reference;
      using typename std::iterator<std::bidirectional_iterator_tag, T, std::size_t>::pointer;
      Iterator() {}
      explicit Iterator(Node<T> *hpn):pn_(hpn) {}
      Iterator(const Iterator<T> &it)
        :pn_(it.pn_) {}
      Iterator<T>& operator=(const Iterator<T> &it) {
        pn_ = it.pn_;
        return (*this);
      }
      Iterator<T>& operator++() {
        pn_ = pn_->next;
        return (*this);
      }
      Iterator<T>& operator++(int) {
        Iterator<T> tmp(*this);
        ++(*this);
        return tmp;
      }
      Iterator<T> operator+(int k) {
        Iterator<T> tmp(*this);
        for (int i = 1; i <= k; i++) ++tmp;
        return tmp;
      }
      bool operator==(const Iterator<T> &it) const {
        return pn_ == it.pn_;
      }
      bool operator!=(const Iterator<T> &it) const {
        return !((*this) == it);
      }
      reference operator*() const {
        return *pn_->p;
      }
      pointer operator->() const {
        return pn_->p;
      }
      Node<T> *pn_;
  };
template <class  T>
class CircularIterator: public std::iterator<std::bidirectional_iterator_tag,
  T, std::size_t> {
    public:
      CircularIterator() {}
  };
template <class T>
class CList {
  public:
    typedef T value_type;
    typedef T& reference_type;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef Iterator<T> iterator;
    typedef Iterator<const T> const_iterator;
    typedef std::size_t size_type;
    typedef std::size_t difference_type;
    typedef CircularIterator<T> circular_iterator;
    typedef CircularIterator<const T> const_circular_iterator;
    CList() {
      sentinel.prev = &sentinel;
      sentinel.next = &sentinel;
    }
    void push_front(const value_type& val) {
      insert(begin(), val);
    }
    void push_back(const value_type& val) {
      insert(end(), val);
    }
    iterator insert(iterator position, const value_type &val) {
      Node<T>* pn = new Node<T>(val);
      Node<T>* next = position.pn_;
      Node<T>* prev = next->prev;
      pn->next = next;
      pn->prev = prev;
      prev->next = pn;
      next->prev = pn;
      return iterator(pn);
    }
    iterator begin() {
      return iterator(sentinel.next);
    }
    const_iterator begin() const {
      return const_iterator(sentinel.next);
    }
    iterator end() {
      return iterator(&sentinel);
    }
    const_iterator end() const {
      return const_iterator(&sentinel);
    }
    iterator erase(iterator position) {
      Node<T>* prev = position.pn_->prev;
      Node<T>* next = position.pn_->next;
      prev->next = next;
      next->prev = prev;
      delete position.pn_;
      return iterator(next);
    }
    bool empty() const {
      return sentinel.next == sentinel.prev;
    }
  private:
    Node<T> sentinel;
};

#endif
