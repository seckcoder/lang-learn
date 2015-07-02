

# Various methods to generate permutations

## permute by insert

perm(n) = insert n in to perm(n-1) 

## permute by swap

perm(n) = choose any one of [1..n] as the first  + perm of rest


### Implementation I

use swap(swap with the first element, then permute on the rest)

### Implementation II

use select(dfs + visited flag). This method can be easily adapted
to the case when there are duplicates in the array

## steinhaus-johnson-trotter


Theory:

```cpp
for p in perms(n-1):
  if p is an even perm:
    insert n from back to front
  else:
    insert n from front to back
```

Definition of even permtation:

Given an identity permutation, if it takes an even number
of swaps to transfer to the identity permutation, then we say it's an even permutation.

### Implementation I

Define DirNum, the number with direction(left/right)
We define an number to be a mobile number if
1. direction left, and larger than the value on the left
2. direction right, and larger than the value on the right

When we find the largest mobile number, we swap it according to the direction.

After the swap, we change the direction of all numbers that are greater than the chosen mobile number.

I have *no idea* why this can perfectly implement the
theory. 


1,2,3,4
<- 1,2,4,3
<- 1,4,2,3
<- 4,1,2,3
<- 4,1,3,2
<- 1,4,3,2
<- 1,3,4,2
<- 1,3,2,4
<- 3,1,2,4
<- 3,1,4,2
<- 3,4,1,2
<- 4,3,1,2
<- 4,3,2,1
<- 3,4,2,1
<- 3,2,4,1
<- 3,2,1,4
<- 2,3,1,4
<- 2,3,4,1
<- ...

### Implementation II

No idea...


