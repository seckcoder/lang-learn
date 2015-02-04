{-# LANGUAGE TemplateHaskell #-}
{-# LANGUAGE FlexibleInstances #-}

import Algo.List
import Data.List
import Test.QuickCheck
-- import Test.QuickCheck.Instances
import Test.Framework (defaultMain, defaultMainWithOpts)
import Test.Framework.Options (TestOptions, TestOptions'(..))
import Test.Framework.Runners.Options (RunnerOptions
                                      , RunnerOptions'(..)
                                      )
import Test.Framework.Providers.QuickCheck2 (testProperty)

import Algo.Sort
import Algo.Search
import Data.Monoid (mempty)
import Data.Word
import Data.Maybe
import Control.Monad.Identity
import qualified Data.Vector as Vec
import Data.Vector ((!))
import Data.Point2d
import Data.Tree

main = defaultMain tests

-- main = do
--   let empty_test_opts = mempty :: TestOptions

--   let my_test_opts = empty_test_opts
--       -- topt_timeout = Just (Just 100),
--       -- topt_maximum_generated_tests = Just 10
--   let empty_runner_opts = mempty :: RunnerOptions

--   let my_runner_opts = empty_runner_opts {
--       ropt_test_options = Just my_test_opts
--   }

--   defaultMainWithOpts tests my_runner_opts

randomBounds :: Int -> (Gen (Int, Int))
randomBounds n = do
  b1 <- (choose (0, n) :: Gen Int)
  b2 <- (choose (0, n) :: Gen Int)
  let bounds = if b1 < b2 then (b1, b2) else (b2, b1)
  return bounds

prop_minimum xs = not (null xs) ==> head (qsort xs) == minimum xs
  where types = (xs :: [Int])


data ListWithBounds a = ListWithBounds [a] (Int, Int) deriving Show

instance (Arbitrary a) => Arbitrary (ListWithBounds a) where
  arbitrary = do
    n <- choose (0, 10000)
    elems <- vector n
    random_bounds <- randomBounds (n - 1)
    return $ ListWithBounds elems random_bounds

instance (Arbitrary a) => Arbitrary (Vec.Vector a) where
  arbitrary = do
    bounds <-randomBounds 10
    elems <- vector (rangeSize bounds)
    return $ Vec.fromList elems

-- instance (Arbitrary a) => Arbitrary (Array Int a) where
--   arbitrary = do
--     b1 <- (choose (0, 1) :: Gen Int)
--     b2 <- (choose (0, 1) :: Gen Int)
--     let bounds = if b1 < b2 then (b1, b2) else (b2, b1)
--     elems <- vector (rangeSize bounds)
--     return $ listArray bounds elems


gen_binary_search_property (x,xs,bnds) search isValid =
  if x `elem` part_xs
     then isValid (fromJust search_ret) $ filter (`inRange` bnds) (elemIndices x sorted_xs)
     else isNothing search_ret
       where sorted_xs = sort xs
             part_xs = slice sorted_xs bnds
             xv = Vec.fromList sorted_xs
             search_ret = search xv

prop_search_contain x (ListWithBounds xs bnds) =
  gen_binary_search_property (x,xs,bnds) search_func isValid_func
    where search_func = \ xv -> binaryFindInArr xv x bnds
          isValid_func = Data.List.elem
          types = (x :: Int,
                  xs :: [Int])

prop_search_lower_bound x (ListWithBounds xs bnds) =
  gen_binary_search_property (x,xs,bnds) search_func isValid_func
    where search_func = \ xv -> binaryLowerBoundInArr xv x bnds
          isValid_func = \ i ids -> i == head ids


prop_search_upper_bound x (ListWithBounds xs bnds) =
  gen_binary_search_property (x,xs,bnds) search_func isValid_func
    where search_func = \ xv -> binaryUpperBoundInArr xv x bnds
          isValid_func = \ i ids -> i == last ids


data TurningPointTestList a = TurningPointTestList [a] (Int,Int) Int deriving Show

instance (Ord a, Arbitrary a) => Arbitrary (TurningPointTestList a) where
  arbitrary = let construct_random random_lst random_bounds@(p,r) = do
                    turning_point <- choose (shrinkRange random_bounds 1)
                    return $ TurningPointTestList random_lst random_bounds turning_point
                  in do
                    n <- choose (0, 10000)
                    lst <- vector n
                    let random_lst = sort (nub lst)
                    random_bounds <- randomBounds ((length random_lst) -1)
                    if rangeSize random_bounds < 3
                       then return $ TurningPointTestList [] (0,0) 0
                       else construct_random random_lst random_bounds

prop_search_turning_point (TurningPointTestList xs bnds@(p,r) tp) = length xs >= 3 ==>
  isJust search_ret && fromJust search_ret == expected_head
    where xv = Vec.fromList (interswapInRange xs bnds tp)
          expected_head = p+(r-tp)+1
          search_ret = binaryTurningPointInArr xv bnds
          types = [xs :: [Int]]

prop_search_turning_point_in_sorted (TurningPointTestList xs bnds tp) = length xs >= 3 ==>
  isNothing search_ret
    where search_ret = binaryTurningPointInArr (Vec.fromList xs) bnds

naiveSaddleBack g z = [(x,y) | x <- [0..z], y <- [0..z], g (x,y)]


prop_SaddleBack z = z >= 0 ==>
  all f res && res \\ naive_res == [] && naive_res \\ res == []
    where res = saddleBack (+) z
          f (x,y) = (x+y) == z
          naive_res = naiveSaddleBack f z
          types = [z :: Int]

data SearchKthTestList a = SearchKthTestList [a] [a] Int deriving Show

instance (Ord a, Arbitrary a) => Arbitrary (SearchKthTestList a) where
  arbitrary = do
    n <- choose (0, 10000)
    lst' <- vector n
    let lst = nub lst'
    if length lst > 0
       then
       do
        tp <- choose (0, (length lst)-1)
        let (xs',ys') = splitAt tp lst
            xs = sort xs'
            ys = sort ys'
        return $ SearchKthTestList xs ys (tp+1)
      else
        return $ SearchKthTestList [] [] 0


test_SearchKth2 (SearchKthTestList xs ys k) = searchKth2 k (Vec.fromList xs, Vec.fromList ys)
prop_SearchKth2 input@(SearchKthTestList xs ys k) = (length xs) + (length ys) >0 ==>
  test_SearchKth2 input == (merge xs ys) !! (k-1)
    where types = [xs :: [Int]]


newtype NQueenInt = NQueenInt Int deriving (Show)

nQueenSolNums = [undefined, 1, 0, 0, 2, 10, 4, 40, 92, 352, 724, 2680]
instance Arbitrary NQueenInt where
  arbitrary = do
    n <- choose (1, length nQueenSolNums - 1)
    return $ NQueenInt n

validateNQueenSolution sol = all (not . conflict) [(p1,p2) | p1 <- sol, p2 <- sol, p1 /= p2]
  where conflict (Point2d x1 y1, Point2d x2 y2) = x1 == x2 || y1 == y2 || abs(x1-x2) == abs(y1-y2)

prop_nQueenSolutionRight (NQueenInt n) = all validateNQueenSolution $ nQueen n

prop_nQueenSolutionNumRight (NQueenInt n) = length (nQueen n) == nQueenSolNums !! n

prop_nQueenMSolutionRight (NQueenInt n) = all validateNQueenSolution $ map ((map fromTuple)  . (zip [1..n])) $ nQueenM n


prop_nQueenMSolutionNumRight (NQueenInt n) = length (nQueenM n) == nQueenSolNums !! n


randomTree :: [a] -> Gen (BinTree a)
randomTree [] = return EmptyTree
randomTree (x:xs) = do
  k <- choose (0, (length xs)-1)
  let (ls,rs) = splitAt k xs
  left <- randomTree ls
  right <- randomTree rs
  return $ Branch x left right

instance Arbitrary a => Arbitrary (BinTree a) where
  arbitrary = do
    n <- choose (0, 10000)
    lst <- vector n
    randomTree lst

prop_postOrder bt = postOrder bt == postOrderT bt
  where types = [bt :: BinTree Int]

prop_preOrder bt = preOrder bt == preOrderT bt
  where types = [bt :: BinTree Int]

prop_inOrder bt = inOrder bt == inOrderT bt
  where types = [bt :: BinTree Int]

tests = [
  -- testProperty "binary search turning point" prop_search_turning_point_in_sorted
  -- testProperty "search kth" prop_SearchKth
  -- testProperty "nQueen solution is right" prop_nQueenSolutionRight,
  -- testProperty "nQueen num of solutions right" prop_nQueenSolutionNumRight,
  -- testProperty "nQueenM solution is right" prop_nQueenMSolutionRight,
  -- testProperty "nQueenM num of solutions right" prop_nQueenMSolutionNumRight,
  testProperty "postOrder traversal" prop_postOrder,
  testProperty "preOrder traversal" prop_preOrder,
  testProperty "inOrder traversal" prop_inOrder
  ]

-- return []
-- main = $(verboseCheckAll)
