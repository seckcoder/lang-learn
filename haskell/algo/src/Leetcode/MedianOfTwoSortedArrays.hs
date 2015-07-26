
{-# LANGUAGE ScopedTypeVariables #-}


module MedianOfTwoSortedArrays (
  findMedian,
  sample
  ) where


    import Data.Vector (fromList, (!), Vector)
    import Data.Vector as Vec
    import Debug.Trace

    data Median a = Pair a a
                 | Single a
                 deriving (Show)

    -- After using scoped type variables, we could give type-signatures
    -- to subterms which reference the type in parent functions.
    findMedian :: forall a. (Ord a) => Vector a -> Vector a -> Median a
    -- findMedian :: (Ord a) => Vector a -> Vector a -> Median a
--  1 -- 2
--  3 -- 4
    findMedian vec1 vec2 = if even (len1 + len2)
                              then Pair (kth vec1 vec2 halflen)  (kth vec1 vec2 (halflen+1))
                              else Single $ kth vec1 vec2 (halflen+1)
                                where len1 = Vec.length vec1
                                      len2 = Vec.length vec2
                                      div2 = (`div` 2)
                                      halflen = div2 (len1 + len2)
                                      kth :: (Ord a) => Vector a -> Vector a -> Int -> a
                                      kth vec1 vec2 k = go 0 (len1-1) 0 (len2-1) k
                                        where go :: (Ord a) => Int -> Int -> Int -> Int -> Int -> a
                                              go p1 r1 p2 r2 k
                                                | p1 > r1 = vec2 ! (p2+k-1)
                                                | p2 > r2 = vec1 ! (p1+k-1)
                                                | v1 < v2 && hflen < k = go (m1+1) r1 p2 r2 (k-hflen1) -- discard part 1
                                                | v1 < v2 && hflen >= k = go p1 r1 p2 (m2-1) k -- discard part 4
                                                | v1 >= v2 && hflen < k = go p1 r1 (m2+1) r2 (k-hflen2) -- discard part 3
                                                | v1 >= v2 && hflen >= k =  go p1 (m1-1) p2 r2 k -- discard part 2
                                                  where (m1::Int) = div2 (p1+r1)
                                                        (m2::Int) = div2 (p2+r2)
                                                        v1 = vec1 Vec.! m1
                                                        v2 = vec2 Vec.! m2
                                                        hflen1 = m1-p1+1
                                                        hflen2 = m2-p2+1
                                                        hflen = hflen1+hflen2-1
    sample = [findMedian (fromList [1,4]) (fromList [2,3]),
              findMedian (fromList [1,2]) (fromList [3,4,5]),
              findMedian (fromList [1]) (fromList [2,3]),
              findMedian (fromList [1]) (fromList [2])
              ]
