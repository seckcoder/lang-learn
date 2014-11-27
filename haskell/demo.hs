import GHC.Base
import Data.Char

safeDiv :: Integral a => a -> a -> a
safeDiv x y =
  let q = div x y
  in if y == 0 then 0 else q


isLarge :: (Ord a, Num a) => a -> String
isLarge x
  | x > 10 = "yep"
  | otherwise = "nope"

factorialRec :: (Ord a, Num a) => a -> a -> a
factorialRec acc n
  | n > 1 = factorialRec (acc * n) (n - 1)
  | otherwise = acc

factorial :: Integer -> Integer
factorial = factorialRec 1

addMaybes mx my
  | Just x <- mx, Just y <- my = Just (x + y)
  | otherwise = Nothing

filter1 :: (a -> Bool) -> [a] -> [a]
filter1 pred [] = []
filter1 pred (x:xs)
  | pred x = x : filter1 pred xs
  | otherwise = filter1 pred xs

-- (filter isLower) is not function composition, but currying
counterLowerCase :: [Char] -> Int
counterLowerCase = length . filter (\c -> isLower c || isDigit c)


stringPuncatuation :: [Char] -> [Char]
stringPuncatuation = filter (`notElem` "!#$%&")


seq_demo = let q = 1 `div` 0
               --- seq q is curried. $ apply "seq q" with return value of putStrLn, which is IO Monad.
            in seq q $ putStrLn "hello world\n"

seq_demo1 = let q = "3"
                -- $! is like imperative function apply. It first evaluate q and then apply f with value of q.
             in putStrLn $! q

--- factorial without accumulating thunks
factorial2 n0 = loop 1 n0
  where loop acc n | n > 1 = (loop $! acc * n) (n-1)
                   | otherwise = acc


main =
  putStrLn "What is your name?" >>
    getLine >>= \name ->
      putStrLn ("Nice to meet you, " ++ name ++ "!")
