{-# LANGUAGE NoImplicitPrelude #-}


module Base (
  Pair(..),
  flip
  ) where
    import GHC.Base hiding (Functor(..), flip)
    import GHC.Show
    import Data.Int

    import Functor

    flip f x y = f y x

    data Pair a = Pair a a deriving (Show)

    instance Functor Pair where
      fmap f (Pair x y) = Pair (f x) (f y)

    data ITree a = Leaf (Int -> a)
                 | Node [ITree a]

    instance Functor ITree where
      fmap f (Leaf g) = Leaf (f . g)
      fmap f (Node [it]) = Node [fmap f it]
