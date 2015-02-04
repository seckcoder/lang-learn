module Algo.Sort (
  qsort,
  merge
  ) where

qsort :: Ord a => [a] -> [a]
qsort [] = []
qsort (x:xs) = qsort lhs ++ [x] ++ qsort rhs
  where lhs = filter (< x) xs
        rhs = filter (>= x) xs




-- merge two sorted list
merge :: Ord a => [a] -> [a] -> [a]
merge [] ys = ys
merge xs [] = xs
merge xs@(x:xs') ys@(y:ys')
  | x < y = x:(merge xs' ys)
  | otherwise = y:(merge xs ys')



-- topological sort
topSort = undefined
