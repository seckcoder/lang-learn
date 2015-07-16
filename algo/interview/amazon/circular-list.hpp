#ifndef _CIRCULAR_LIST_HPP
#define _CIRCULAR_LIST_HPP


template <class T>
class Node {
    public:
        T* p;
        Node *prev, *next;
        Node(T* p_): p(new T(*p)), prev(NULL), next(NULL) {}
        Node(): p(NULL), prev(NULL), next(NULL) {}
        ~Node() {
            delete p;
            p = NULL;
        }
};


template <class T>
class Iterator:public std::iterator<std::bidirectional_iterator_tag,
    T, std::size_t> {
    public:
        Iterator() {}
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
        CList() {}
        void push_front(const value_type& val) {
        }
        void push_back(const value_type& val) {
        }
        void erase(const_iterator position) {
        }
        iterator insert(iterator position, const_reference val) {
        }
        iterator begin() {
            return iterator(sentinel.next);
        }
        const_iterator begin() const {
            return const_iterator(sentinel.next);
        }
        iterator end() {
        }
        const_iterator end() const {
        }
        iterator erase(iterator position) {
        }
        bool empty() const {
            return impl_.empty();
        }
    private:
        Node<T> sentinel;
};

#endif
