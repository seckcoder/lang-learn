#include <iostream>
using namespace std;


int *smallest_greater_or_equal_than(int *p, int *r, int val) {
  int cnt = r-p;
  int *mark = r;
  // [p, r)
  while (cnt > 0) {
    int *it = p;
    int step = cnt / 2;
    it += step;
    if (*it < val) {
      p = ++it;
      cnt -= step+1;
    } else {
      mark = it;
      cnt = step;
    }
  }
  return mark;
}

int *smallest_greater_than(int *p, int *r, int val) {
  int cnt = r-p;
  int *mark = r;
  while (cnt > 0) {
    int *it = p;
    int step = cnt / 2;
    it += step;
    if (*it <= val) {
      p = ++it;
      cnt -= step+1;
    } else {
      mark = it;
      cnt = step;
    }
  }
  return mark;
}

int *smallest_equal_than(int *p, int *r, int val) {
  int cnt = r-p;
  int *mark = r;
  while (cnt > 0) {
    int *it = p;
    int step = cnt/2;
    it += step;
    if (*it < val) {
      p = ++it;
      cnt -= step + 1;
    } else if (*it > val) {
      cnt = step;
    } else {
      mark = it;
      cnt = step;
    }
  }
  return mark;
}

int *greatest_equal_than(int *p, int *r, int val) {
  int cnt = r-p;
  int *mark = r;
  while (cnt > 0) {
    int *it = p;
    int step = cnt/2;
    it += step;
    if (*it < val) {
      p = ++it;
      cnt -= step + 1;
    } else if (*it > val) {
      cnt = step;
    } else {
      mark = it;
      p = ++it;
      cnt -= step + 1;
    }
  }
  return mark;
}

int *binsearch_truncated(int *p, int *r, int val) {
  if (p >= r) return r;
  int begin = *p;
  int cnt = r-p;
  int *mark = r;
  while (cnt > 0) {
    int *it = p;
    int step = cnt/2;
    it += step;
    if (*it >= begin) {
      p = ++it;
      cnt -= step + 1;
    } else {
      mark = it;
      cnt = step;
    }
  }
  return mark;
}

template <class ForwardIterator, class Compare>
ForwardIterator binSearch(Forwarditerator first, Forwarditerator last, Compare comp) {
  ForwaredIterator it, mark;
  std::iterator_traits<ForwardIterator>::difference_type count, step;
  count = distance(first, last);
  while (count > 0) {
    it = first;
    step = count/2;
    advance(it, step);
    if (comp(it) == 0) {
      first = ++it;
      count -= step+1;
    } else {
      count = step;
    }
  }
  return first;
}


int n;
int *a;

void input() {
  freopen("test.in", "r", stdin);
  scanf("%d", &n);
  a = new int[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
}

void test_smallest_greater_than() {
  int *it = smallest_greater_than(a, a+n, -1);
  cout << it - a << endl;
}

int main(int argc, const char *argv[])
{
  input();
  test_smallest_greater_than();
  //test_greatest_greater_than();
  delete [] a;
  return 0;
}
