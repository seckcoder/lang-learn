{-# LANGUAGE NoImplicitPrelude #-}

module Either(
  Either(..)
  ) where

  import GHC.Base (Eq)
  import GHC.Show
  import Functor
  import Monad

  data Either a b = Left a | Right b deriving (Show)

  instance Functor (Either a) where
    fmap _ (Left x) = Left x
    fmap f (Right y) = Right (f y)

  instance Monad (Either a) where
    return = Right
    (Left x) >>= _ = Left x
    (Right y) >>= f = (f y)
