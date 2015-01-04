{-# LANGUAGE NoImplicitPrelude #-}

module Demo.Foldable (
  demos
  ) where

    import Prelude ((+), (.))
    import Foldable

    demos = (
      foldl (+) 0 [1,2,3],
      foldr (+) 0 [1,2,3],
      fold [[1],[2],[3]],
      foldMap (\x -> [x]) [1,2,3]
      )
