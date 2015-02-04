


binSearch :: (Int -> Bool) -> (Int,Int) -> Maybe Int
binSearch f (p,r) = go (p,r) Nothing
  where go (p,r) mark | p > r = mark
                      | otherwise = if f m then go (m+1,r) (Just m) else go (p,m-1) mark
                                      where m = (p+r) `div` 2

cabalLength :: [Double] -> Int -> Double
cabalLength cables num_pieces = case binSearch validLength (1, 10000000) of
                                     Nothing -> fromIntegral 0
                                     Just v -> (fromIntegral v) / 100
    where cabal_ints = map (floor . (*100)) cables
          validLength len = (foldr (+) 0 (map (`div` len) cabal_ints)) >= num_pieces

main = print $ cabalLength [8.02,7.43,4.57,5.39] 11
