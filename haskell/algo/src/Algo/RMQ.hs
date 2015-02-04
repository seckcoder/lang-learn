
module Algo.RMQ (
  ) where

    import Data.Vector as V

    -- Range minimum query

    -- <O(n), O(sqrt(n))>

    rmqPre1 vec = go (zip (V.toList vec) [0..])
      where go [] = []
            go ((x,i):rs) = i / ss
            ss = floor $ sqrt (length vec)
            dp = V.replicate ss 0


    -- <O(n), O(logn)>
    -- <O(n), O(logn)>  in segment tree
