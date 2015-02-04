

module Algo.DP.DivideConquer (
  ) where

    import qualified Data.Grid as G


    maxAreaOfOne :: G.Grid Char -> Int
    maxAreaOfOne map = G.map map (G.replicate (
      go (0,0) map (G.replicate (G.shape grid) 0)
