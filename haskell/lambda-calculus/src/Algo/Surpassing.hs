

module Algo.Surpassing (
  maximumSurpassingPair
  ) where

    import GHC.Num
    import Data.List

    maximumSurpassingPair :: (Ord a) => [a] -> (Int, a)
    maximumSurpassingPair = maximumBy orderBy . table
    orderBy :: (Ord t) => (Int, t) -> (Int, t) -> Ordering
    orderBy (cx,x) (cs,s) =
      if cx < cs
         then LT
         else if cx == cs
         then EQ
         else GT

    table :: (Ord a) => [a] -> [(Int, a)]
    table [] = []
    table [x] = [(0, x)]
    table xs =
      let m = length xs
          n = m `div` 2
          (as,ds) = splitAt n xs
          tas = table as
          tds = table ds
          -- m-n is the length of tds
       in joinTable (m-n) tas tds

    joinTable :: (Ord a) => Int -> [(Int, a)] -> [(Int, a)] -> [(Int, a)]
    joinTable 0 tas [] = tas
    joinTable n [] tds = tds
    joinTable n tas@((cx, x):tas') tds@((cy,y):tds')
      | x < y = (cx+n,x):joinTable n tas' tds
      | otherwise = (cy,y):joinTable (n-1) tas tds'
