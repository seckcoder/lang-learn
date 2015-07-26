{-# LANGUAGE ScopedTypeVariables #-}


module AddTwoNumbers(
  addTwoNumbers
  ) where


import Data.Monoid

-- Method 1
addTwoNumbers :: Integral a => [a] -> [a] -> [a]
addTwoNumbers xs1 xs2 = go 0 xs1 xs2
  where go 0 [] xs2 = xs2
        go 0 xs1 [] = xs1
        go c [] [] = [c]
        go c [] (x2:xs2) = (c+x2):xs2
        go c (x1:xs1) [] = (c+x1):xs1
        go c (x1:xs1) (x2:xs2) = let sum = x1+x2+c
                                  in (sum `mod` 10): (go (sum `div` 10) xs1 xs2)



zipWithPadding :: a -> b -> [a] -> [b] -> [(a,b)]
zipWithPadding a b (x:xs) (y:ys) = (x,y) : zipWithPadding a b xs ys
zipWithPadding a _ []     ys     = zip (repeat a) ys
zipWithPadding _ b xs     []     = zip xs (repeat b)

addTwoNumbers1 :: (Integral a) => [a] -> [a] -> [a]
addTwoNumbers1 xs1 xs2 = let
                            (c,l) = foldl (\ (c,l) (v1,v2) ->
                                      let s = c+v1+v2
                                       in (s `div` 10, (s `mod` 10):l))
                                       (0,[]) (zipWithPadding 0 0 xs1 xs2)
                           in reverse (if c == 0 then l else c:l)


samples = [
  addTwoNumbers [1,6] [3,4,5]
  ]
