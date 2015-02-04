

import qualified Data.Vector.Unboxed.Mutable as M

sample1 = do
  v <- M.new 10
  M.rite v 0 (4 :: Int)
  x <- M.read v 0
  print x

sample2 = do
  v <- M.replicate 10 (3 :: Int)
  x <- M.read v 0
  print x

main = sample2
