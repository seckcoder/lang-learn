The right method to implement binary search
========

The key to implement binary search is to maintain loop invariant and avoid one corner case.
I will detail the process of solving there binary search problems.


Problem 1: Simple Binary search
=======

Given a sorted(assending) array `A`, with its size to be `size`, find value `val`
in binary search.

The implementation is in bin_search1.cc

The loop invariant for the problem is: "p <= q and if A contains val, it will be found in A[p-q]".

Prove of loop invariant:

Initialize
====
p = 0, q = size - 1. As long as size >= 1, p <= q

maintain
====
mid = (p+q)/2.
So if A[mid] < val, and val will be found in A[(mid+1)->q], so p = mid+1.
If A[mid] > val, val will be found in A[p->(mid-1)], so q = mid-1.

Terminate
====
mid = (p+q)/2. 
So if A[mid] = val, val is already found.
If p > q, we know we can't find val in A.


Problem 2: search the lower and upper bound in a sorted array A.
=======

Given a sorted(assending) array `A`, how to find the lower and upper idx of a 
value: `val` in the array.

The implementation is in bin_search2.cc

There is two loops.

The loop invariant for the first is:

"p <= q and the lower index of val in A resides in p-q"

I will not detail the prove of loop invariant in my code.
But I will point out the corner case I mentions earlier.
To maintain the loop invariant, when A[mid] = val, we should set q = mid,
so that the lower index of val in A resides in p-q. After set this,
we will encounter the case when p = q. So mid = p = q. If at this time,
A[mid] also equals val, the loop will never terminate. So we need to add
a terminate condition(when p = q) to the loop.

The loop invariant for the second is:

"p <= q and the upper index of val in A resides in p-q".

To maintain the loop invariant, when A[mid] = val, we set p = mid,
so that the upper index of val in A resides in p-q. After this,
we will encounter two corner case.

1. when p = q, so mid = p = q. If A[mid] = val, the loop will never terminate.
2. when p+1 = q, so mid = p = q - 1. If A[mid] = val, the loop will never terminate.

So we need to add two terminate condition(p=q, p+1=q) to the loop.

Problem 3: find the truncated position in an array
=========

Find the truncated position of Array A, with A being the concatenation of two
sub arrays B1, B2 of B. B is a sorted(assending, no equal elements) array. We truncate B
into two parts B1, B2 at some position.

For example, if B is [1,2,3,4,5] then A is [3,4,5,1,2] if we truncate after index 1.

We can use binary search to find the truncated position.

The loop invariant is: "p+1 <= q,and truncated position in p-q".

When maintaining the loop invariant, we set p = mid, so we need to add termination
for p+1=q. Note we don't need to add termination for p = q since this will violate
the loop invariant and it breaks directly.
