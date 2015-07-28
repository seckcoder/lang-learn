module PalindromeNumber (
    isPalindrome,
    samples) where

import Control.Monad.State
import Control.Monad.ST
import Data.STRef

eq2 (a,b) = (a == b)

infixl 6 >-<

(>-<) :: Int -> Int -> State Int [(Int,Int)]
(>-<) p r
    | p == r = return [(p,p)]
    | p < r = do
        b <- get
        rs <- (p*b) >-< (r `div` b)
        return $ (p,r) : rs

digits :: Int -> [Int]
digits 0 = [0]
digits v = go v
    where go 0 = []
          go v = (v `mod` 10) : go (v `div` 10)

reverseSnd :: ([a],[b]) -> ([a],[b])
reverseSnd (a,b) = (a, reverse b)

-- If the lst is odd, then we drop the middle element
splitHalf :: [a] -> ([a], [a])
splitHalf lst = case splitAt (len `div` 2) lst of
                    (a,b) -> if even len then (a,b) else (a, tail b)
                  where len = length lst

zip2 :: ([a],[b]) -> [(a,b)]
zip2 (a,b) = zip a b
-- Check whether an integer is a palindrome
isPalindrome :: Int -> Bool
isPalindrome x 
    | x < 0 = False
    | x >=0 = and $ map eq2 $ zip2 (reverseSnd $ splitHalf $ digits x)


-- The above solution seems is not in constant space(because of the reverse function used)

-- Solution in constant space
-- General Idea: use another function to get the reverse list



numDigits :: Int -> Int
numDigits 0 = 1
numDigits v = go v
    where go 0 = 0
          go v = (go (v `div` 10)) + 1



-- numDigits function using constant space(using ST Monad)
numDigitsM :: Int -> Int
numDigitsM 0 = 1
numDigitsM v = runST $ do
        n <- newSTRef 0
        go v n
    where go 0 n = readSTRef n
          go x n = do
              modifySTRef n (+1)
              go x n

digitsRev :: Int -> [Int]
digitsRev 0 = [0]
digitsRev v = go v (10^(n-1))
    where n = numDigits v
          go 0 m = []
          go v m = (v `div` m) : go (v `mod` m) (m `div` 10)


-- Although we construct two lists, this version still uses constant memory
-- according to the lazy evaluation property of Haskell
isPalindrome2 :: Int -> Bool
isPalindrome2 x
    | x < 0 = False
    | x >= 0 = and $ map eq2 $ zip (takeHalf (digits x)) (takeHalf (digitsRev x))
        where  n = numDigitsM x
               takeHalf = take $ n `div` 2

samples = [
    isPalindrome 123,
    isPalindrome 121,
    isPalindrome2 123,
    isPalindrome2 121]
