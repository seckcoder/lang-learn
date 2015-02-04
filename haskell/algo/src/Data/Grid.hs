{-# LANGUAGE NoImplicitPrelude #-}
{-# LANGUAGE BangPatterns #-}

module Data.Grid (
  Grid,
  (!),
  fromList,
  map,
  replicate,
  toList,
  shape
  ) where


  import Prelude (Int(..), (.), ($), (==))
  import GHC.Show

  import qualified Data.Vector as V
  import qualified Data.List as L

  data Grid a = Grid (V.Vector (V.Vector a)) (Int,Int)

  instance (Show a) => Show (Grid a) where
    show g = show $ toList g

  (!) :: (Grid a) -> (Int,Int) -> a
  (!) (Grid g shape) (x,y) = (g V.! x) V.! y

  fromList :: [[a]] -> Grid a
  fromList lst = (Grid . (V.fromList . (L.map V.fromList)) $ lst) (shapeOfList lst)
    where shapeOfList lst = let len = L.length lst
                             in if len == 0 then (0,0) else (len, (L.length (L.head lst)))

  map :: (a -> b) -> Grid a -> Grid b
  map f (Grid g s) = Grid (V.map (V.map f) g) s

  replicate :: (Int,Int) -> a -> Grid a
  replicate (m,n) v = Grid (V.replicate m (V.replicate n v)) (m,n)


  toList :: Grid a -> [[a]]
  toList (Grid g s) = L.map V.toList . V.toList $ g

  shape :: Grid a -> (Int, Int)
  shape (Grid _ s) = s
