

#include <iostream>
#include <list>
using namespace std;

// teh same question. I have on twitter. Just copy this.

typedef list<list<int> > ElemList;
typedef list<int> IntList;

// First describe your idea.
//
// 1. I will use an exception to represent the end of list iteration
// 2. After we finish d`

class EndOfIteratorExcept : public exception {
  public:
    virtual const char *what() const throw() {
      return "End of iterator...";
    }
};

class Iterator {
  public:
    ElemList::const_iterator elemCur;
    ElemList::const_iterator elemEnd;
    IntList::const_iterator intCur;
    Iterator(const list<list<int> > &data_list) {
      elemCur = data_list.begin();
      elemEnd = data_list.end();
      intCur = elemCur->begin();
    }

    int next() {
      // next will return the next element in the iterator
      
      // end of iteration, throw an excepiotn
      if (elemCur == elemEnd) throw EndOfIteratorExcept();

      // in the first branch of if-else,
      if (intCur == elemCur->end()) {
        // if the end of current list
        // we move to the next list 
        elemCur++;
        if (elemCur == elemEnd) throw EndOfIteratorExcept();
        intCur = elemCur->begin();
        return next();
      } else {
        // other wise, we directly return the next element
        // of current list
        int value = *intCur;
        intCur++;
        return value;
      }
    }
};

// since in C++, we can't represent a list of integer and list.
// so I assume that the list is represented as a list of list.
// for the single integer, I will store 
// Just Say this: let me check it for a moment.

int main() {
  list<list<int> > data_list;
  list<int> a_list;
  a_list.push_back(1);
  list<int> b_list;
  b_list.push_back(2);
  data_list.push_back(a_list);
  data_list.push_back(b_list);


  Iterator iter(data_list);
  cout << iter.next() << " " << iter.next() << endl;
  return 0;
}



