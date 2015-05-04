

largestRectArea hist = go [] ([(0,minv-1)] ++ (zip [1..n] hist) ++ [((n+1),minv-1)]) 0
  where go _ [] max_area = max_area
        go [] ((m,hm):xs) max_area = go [(m,hm)] xs max_area
        go stack@((m,hm):ts) hist@((right,hr):xs) max_area
          | hm <= hr = go ((right,hr):stack) xs max_area
          | otherwise = let (left,hl) = head ts
                         in go ts hist (max_area `max` (area hm left right))
        area height p r = (r-p-1) * height
        minv = minimum hist
        n = length hist


main = print $ largestRectArea [2,1,5,6,2,3]
