
#include <iostream>



/*
 * Definition:
 *  lower_bound: returning an iterator to the first element for which comp(*it,val) would return false.
 *  upper_bound: returning an iterator to the first element for which comp(val,*it) would return true.
 *
 *
 * Intuition:
 *  lower_bound: find the smallest iterator `it`, so that *it >= val
 *  upper_bound: find the smallest iterator `it`, so that *it > val
 *
 * Example:
 *
 *    lower bound of 2
 *      |
 *   [1,2,2,2,3,3,4,5]
 *            |
 *        upper bound of 3
 *
 * Intution of comp function:
 *  std::lower_bound and std::upper_bound assume that the elements in the range shall already be sorted according to this same criterion.
 *  By default, comp = std::less<T>();
 *  So:
 *
 *    *it >= val   <=>   !*it < val   <=> comp(*it, val) = False
 *    *it > val    <=>   val < *it    <=> comp(val, *it) = True
 *
 *
 * std::lower_bound and std::upper_bound could be used with any forwarditerator. But it could achieve
 * best performance when using with randomAccessIterator.
 *
 * `map` and `set` provide their own bound search function to give the best performance.
 */


/*
 * Find the largest iterator `it`, so that *it <= val
 */

template <class ForwardIterator, class T, class Comp>
  ForwardIterator largest_less_equal(ForwardIterator first, ForwardIterator last, const T& val, Comp comp=std::less<int>())
{
  auto upper = std::upper_bound(first, last, val, comp);
  if (upper == first) /* for all `it`, *it > val */
    return last; /* we can't find one */
  else
    return (--upper);
}

/*
 * Find the largest iterator `it`, so that *it < val
 */

template <class ForwardIterator, class T, class Comp>
  ForwardIterator largest_less(ForwardIterator first, ForwardIterator last, const T& val, Comp comp=std::less<int>())
{
  auto lower = std::lower_bound(first, last, val, comp);
  if (lower == first) /* for all `it`, *it >= val */
    return last; /* we can't find one */
  else
    return (--lower);
}
