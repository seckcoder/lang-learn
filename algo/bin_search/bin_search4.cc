#include <iterator>     // std::iterator_traits

using namespace std;
// The code is from C++ std lib.

// Apparently, although this function works when Forwarditerator is not a
// random-access iterator, it's much slower.
// For random-access iterator: time complexity is O(lgn)
// For non-random access iter: time complexity is O(2n+lgn). distance is O(n),
//     advance sum up to O(n), the loop is O(lgn).
//
// If val not exist in [first,last), then return value is last
// If val exist in [first, last), return the lowest index so that it's >= val
template <class ForwardIterator, class T>
  ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last, const T& val)
{
  ForwardIterator it;
  std::iterator_traits<ForwardIterator>::difference_type count, step;
  count = distance(first,last);
  // loop invariant: answer in [first, last), if answer doens't exist,
  // answer = last.
  while (count>0)
  {
    // After every loop, count will always be strictly smaller!
    it = first; step=count/2; advance (it,step);
    if (*it<val) {                 // or: if (comp(*it,val)), for version (2)
      // right
      // *it is a false value, so we can advance first to next of it.
      first=++it;
      count-=step+1;
    } else {
      // left has step number of elements, floor(count/2) < count
      count=step;
    }
  }
  // if val < smallest of [first, last), then final value = first
  // if val > greatest of [first, last), then final value = last.
  return first;
}


// Return the lowest index such that it's greater than val.
template <class ForwardIterator, class T>
  ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& val)
{
  ForwardIterator it;
  std::iterator_traits<ForwardIterator>::difference_type count, step;
  count = std::distance(first,last);
  while (count>0)
  {
    it = first; step=count/2; std::advance (it,step);
    if (!(val<*it)) {                 // or: if (!comp(val,*it)), for version (2)
      // *it is a false value( *it >= val ). Why write it as !(val<*it)?
      // Because >= op may hasn't been defined.
      first=++it; count-=step+1; 
    }
    else count=step;
  }
  return first;
}
