

module AddTwoNumbers(
 addTwoNumbers
) where



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





-- Method 2
addTwoNumbers1 :: Integral a => [a] -> [a] -> [a]
addTwoNumbers1 xs1 xs2 = if length xs1 < length xs2
                            then go xs1 xs2
                            else go xs2 xs1
                         where go xs1 xs2 = let (fst,snd) = splitAt (length xs1) xs2
                                             in foldl (\ 
((zipWith (+) xs1 fst) ++ xs2)

samples = [
    addTwoNumbers [1,6] [3,4,5]
]
