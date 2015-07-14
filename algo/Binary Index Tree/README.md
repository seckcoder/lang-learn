

# lowbit(x) = x & (-x)

1. lowbit(x) = 2^a with a being the lowest 1 bit. For example, bin(6) is "1010",
   so lowbit(6) is 2, or "0b10".

2. It's easy to verify that lowbit(x) = x & (~x + 1). 
    x : .....1000...
   ~x:  .....0111...
  ~x+1: .....1000...
  
3. We know that ~x + 1 = -x.



# When modify i val, we always change j += lowerbit(j)

1. Which indices cover index j?






