

import Control.Monad

getSamples = do
  t <- [1..]
  y <- [1..]
  x <- [y+1..(y+t)]
  guard (x*x - y*y > x*t)
  return [(0,x), (t, y)]

main = print $ take 10 getSamples
