

module Algo.List (
  splitAts,
  interswap,
  interswapInRange,
  slice,
  inRange,
  rangeSize,
  shrinkRange,
  splits
  ) where


import Control.Monad (MonadPlus(..))

tuple2ToList tpl = case tpl of
                        (p,r) -> [p,r]

splitAts :: [Int] -> [a] -> [[a]]
splitAts ids lst = go ids lst 0
  where go [i] lst n = tuple2ToList $ splitAt (i-n) lst
        go (i:is) lst n = case (splitAt (i-n) lst) of
                               (p,r) -> p:(go is r i)


interswap :: [a] -> Int -> [a]
interswap xs i = interswapInRange xs (0, length xs - 1) i

interswapInRange :: [a] -> (Int,Int) -> Int -> [a]
interswapInRange [] (p,r) i = []
interswapInRange xs (p,r) i = case splitAts [p,i,r+1] xs of
                                   [xs1, xs2, xs3, xs4] -> xs1 ++ xs3 ++ xs2 ++ xs4

isOrdered:: (Ord a) => [a] -> Bool
isOrdered [] = True
isOrdered [a] = True
isOrdered (x:y:xs) = if (x <= y) then isSucc xs else isPrev xs

isSucc [] = True
isSucc [a] = True
isSucc (x:y:xs) = if (x<=y) then isSucc xs else False

isPrev [] = True
isPrev [a] = True
isPrev (x:y:xs) = if (x>=y) then isPrev xs else False


slice :: [a] -> (Int, Int) -> [a]
slice xs (p,r) = take (r-p+1) (drop p xs)

inRange :: Int -> (Int,Int) -> Bool
inRange x (p,r) = p <= x && x <= r

rangeSize (p,r) = (r-p+1)

shrinkRange (p,r) i = (p+i,r-i)


splits :: MonadPlus m => [a] -> m (a, [a])
splits [] = mzero
splits (a:x) = return (a,x) `mplus`
  do (b,x') <- splits x
     return (b, a:x')
