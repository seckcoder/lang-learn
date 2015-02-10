

#include <iostream>
#include <list>
using namespace std;


typedef list<list<int> > ElemList;
typedef list<int> IntList;


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
      if (elemCur == elemEnd) throw EndOfIteratorExcept();
      if (intCur == elemCur->end()) {
        elemCur++;
        if (elemCur == elemEnd) throw EndOfIteratorExcept();
        intCur = elemCur->begin();
        return next();
      } else {
        int value = *intCur;
        intCur++;
        return value;
      }
    }
};


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
