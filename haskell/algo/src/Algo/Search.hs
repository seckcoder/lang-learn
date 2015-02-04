module Algo.Search(
  binaryFind,
  binaryFindInArr,
  binaryLowerBound,
  binaryLowerBoundInArr,
  binaryUpperBound,
  binaryUpperBoundInArr,
  binaryTurningPoint,
  binaryTurningPointInArr,
  binarySearch,
  binarySearchSmallestGreater,
  binarySearchSmallestGreaterInArr,
  saddleBack,
  searchKth2,
  nQueen,
  nQueenM
  ) where


    import Data.Vector hiding ((++), all)
    import Data.Maybe
    import Debug.Trace
    import Data.Foldable hiding (all)

    import Data.Point2d
    import Control.Monad
    import Algo.List


    binaryFindInArr:: (Integral a) => (Vector a) -> a -> (Int,Int) -> Maybe Int
    binaryFindInArr vec v (a,b) = binaryFind (\ m -> compare (vec!m) v) (a,b)

    -- binaryFind :: (Int -> Ordering) -> (Int, Int) -> Maybe Int
    -- binaryFind f (a,b)
    --   | a > b = Nothing
    --   | otherwise = let m = (a+b) `div` 2
    --                  in case f m of
    --                          EQ -> Just m
    --                          LT -> binaryFind f (m+1,b)
    --                          GT -> binaryFind f (a, m-1)

    binaryFind f = binarySearch (\ m mark -> case f m of
                 EQ -> Return (Just m)
                 LT -> GoRight mark
                 GT -> GoLeft mark)

    binaryLowerBoundInArr :: (Integral a) => (Vector a) -> a -> (Int, Int) -> Maybe Int
    binaryLowerBoundInArr vec v (a,b) = binaryLowerBound (\ m -> compare (vec!m) v) (a,b)

    -- binaryLowerBound :: (Int -> Ordering) -> (Int, Int) -> Maybe Int
    -- binaryLowerBound f (a,b) = go (a,b) Nothing
    --   where go (p,r) mark | p > r = mark
    --                       | otherwise = let m = (p+r) `div` 2
    --                                      in case f m of
    --                                              EQ -> go (p,m-1) (Just m)
    --                                              LT -> go (m+1,r) mark
    --                                              GT -> go (p, m-1) mark
    binaryLowerBound f = binarySearch (\ m mark -> case f m of
                       EQ -> GoLeft (Just m)
                       LT -> GoRight mark
                       GT -> GoLeft mark)

    binaryUpperBoundInArr :: (Integral a) => (Vector a) -> a -> (Int, Int) -> Maybe Int
    binaryUpperBoundInArr vec v (a,b) = binaryUpperBound (\ m -> compare (vec!m) v) (a,b)

    -- binaryUpperBound :: (Int -> Ordering) -> (Int, Int) -> Maybe Int
    -- binaryUpperBound f (a,b) = go (a,b) Nothing
    --   where go (p,r) mark | p > r = mark
    --                       | otherwise = let m = (p+r) `div` 2
    --                                      in case f m of
    --                                              EQ -> go (m+1, r) (Just m)
    --                                              LT -> go (m+1, r) mark
    --                                              GT -> go (p, m-1) mark

    binaryUpperBound f = binarySearch (\ m mark -> case f m of
                       EQ -> GoRight (Just m)
                       LT -> GoRight mark
                       GT -> GoLeft mark)

    binaryTurningPointInArr :: (Integral a) => (Vector a) -> (Int, Int) -> Maybe Int
    binaryTurningPointInArr vec (a,b) = binaryTurningPoint (\ m -> compare (vec!m) (vec!a)) (a,b)

    binaryTurningPoint f = binarySearch (\ m mark -> case f m of
                                        EQ -> Return mark
                                        LT -> GoLeft (Just m)
                                        GT -> GoRight mark)

    -- binaryTurningPoint :: (Int -> Ordering) -> (Int, Int) -> Maybe Int
    -- binaryTurningPoint f (a,b) = go (a,b) Nothing
    --   where go (p,r) mark | p > r = mark
    --                       | otherwise = let m = (p+r) `div` 2
    --                                      in case f m of
    --                                              EQ -> mark
    --                                              LT -> go (p, m-1) (Just m)
    --                                              GT -> go (m+1, r) mark

    data CompareResult a = Return a
                         | GoRight a
                         | GoLeft a



    binarySearchSmallestGreaterInArr vec v (a,b) = binarySearchSmallestGreater (\ m -> compare (vec!m) v) (a,b)
    binarySearchSmallestGreater f = binarySearch (\ m mark -> case f m of
                                                 EQ -> GoRight mark
                                                 LT -> GoRight mark
                                                 GT -> GoLeft (Just m))


    -- General form of binary search
    binarySearch :: (Int -> Maybe Int -> CompareResult (Maybe Int)) -> (Int,Int) -> Maybe Int
    binarySearch cmp (a,b) = go (a,b) Nothing
      where go (p,r) mark | p > r = mark
                          | otherwise = let m = (p+r) `div` 2
                                         in case cmp m mark of
                                                 (Return mark) -> mark
                                                 (GoRight mark) -> go (m+1,r) mark
                                                 (GoLeft mark) -> go (p, m-1) mark

    saddleBack :: (Int -> Int -> Int) -> Int -> [(Int, Int)]
    saddleBack f z = go (0, m) f z
      where
        m = fromJust $ binarySearch (cmp_func (\ y -> compare (f 0 y) z)) (0, z)
        n = fromJust $ binarySearch (cmp_func (\ x -> compare (f x 0) z)) (0,z)
        cmp_func g m mark = case (g m) of
                                 EQ -> GoRight (Just m)
                                 LT -> GoRight (Just m)
                                 GT -> GoLeft mark
        go (u,v) f z
          | u > n || v < 0 = []
          | z' < z = go (u+1,z) f z
          | z' == z = (u,v) : go (u+1, v-1) f z
          | z' > z = go (u, v-1) f z
            where z' = f u v




    traceValue :: (Show a) => String -> a -> a
    traceValue s a = trace (s Prelude.++ show a) a

    searchKth2 :: (Ord a) => Int -> (Vector a, Vector a) -> a
    searchKth2 k (xa,ya) = go k (0, (Data.Vector.length xa) - 1) (0, (Data.Vector.length ya) - 1)
      where go k (px,rx) (py,ry) | px > rx = ya!(py+k-1)
                                 | py > ry = xa!(px+k-1)
                                 | otherwise = case (xa!mx < ya!my, half_len >= k) of
                                                    (True, True) -> go k (px,rx) (py,my-1)
                                                    (True, False) -> go (k-(mx-px+1)) (mx+1,rx) (py,ry)
                                                    (False, True) -> go k (px,mx-1) (py,ry)
                                                    (False, False) -> go (k-(my-py+1)) (px,rx) (my+1,ry)
                                    where mx = (px+rx) `div` 2
                                          my = (py+ry) `div` 2
                                          half_len =  mx-px + my-py + 1




    nQueen :: Int -> [[Point2d Int]]
    nQueen n = go 1 []
      where go x sol | x > n = [sol]
                     | otherwise = fold [go (x+1) (Point2d x y:sol)  | y <- [1..n], valid sol x y ]
            valid sol x y = all (not . align (Point2d x y)) sol


    -- Monadic style backtracking
    nQueenM :: Int -> [[Int]]
    nQueenM n = place n [1..n] [] []
      where place :: (MonadPlus m) => Int -> [Int] -> [Int] -> [Int] -> m [Int]
            place 0 rs d1 d2 = return []
            place x rs d1 d2 = do
              (y, rs') <- splits rs
              let q1 = x-y
                  q2 = x+y
              guard (q1 `Prelude.notElem` d1)
              guard (q2 `Prelude.notElem` d2)
              ys <- place (x-1) rs' (q1:d1) (q2:d2)
              return (y:ys)
