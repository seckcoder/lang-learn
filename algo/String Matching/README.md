


# KMP


Matching string S with pattern P.

## Prefix function

Define P_s = P[0...s] or P.substr(0, s)

Define pi as

pi[q] = max{k : k < q and P_k suffix of P_q}



P_6:
abcdab

P_2:
ab

=> pi[6] = 2

We will see the intuitive meaning of pi later


## String Matching

    01234567...
S = abcabcdababcdabcdabde

    01234567...
P = abcdabd


Suppose currently, we have matched S[3...8] with P[0..5]. 

Let i = 9, and j = 6. Apparently, S[i] != P[j].

What should we do next? 

We should restart the matching process from S[4].

But S[4] != P[0]. So the match failed. Then we move to S[5] ...

It's like we are shifting the pattern P to start another match with S.

         |
abcabcdababcdabcdabde
   abcdabd


Shift P right for 1 step

abcabcdababcdabcdabde
    abcdabd

...

         |
abcabcdababcdabcdabde
       abcdabd
    


However, can we directly shift to the right point?

Thinking about our prefix function, if we define q as the number of characters
already matched, then q - pi[q] means the number of steps we can shift P.
After shifting P for q-pi[q] steps, it may not bring us a perfect match between
P and S, but we know that if we shift i < q-pi[q] steps, we will surely not get 
a match. We can get that from the definition of pi.


## Calculation of prefix function


Suppose pi[i] = k.

Now we wanna calculate pi[i+1].

Consider P[i] (the i+1 th character) with P[k] (the kth character),

if P[i] == P[k], then pi[i+1] = pi[i] + 1.
else, 

      |
abcdabd         --- P1
    abcdabd     --- P2
      abcdabd   --- P3


Suppose the pattern above is P1, the pattern below is P2. At this time,

we need to shift P2 to the right, which creates P3.

Apparently the number of characters we need to shift is k-pi[k] according
to the definition of pi.



