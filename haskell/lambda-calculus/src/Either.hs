{-# LANGUAGE NoImplicitPrelude #-}

module Either(
  Either(..)
  ) where

  import GHC.Base (Eq)
  import GHC.Show
  import Functor
  import Applicative
  import Monad

  data Either a b = Left a | Right b deriving (Show)

  instance Functor (Either a) where
    fmap _ (Left x) = Left x
    fmap f (Right y) = Right (f y)

  instance Applicative (Either a) where
    pure = Right
    (Left e) <*> _ = Left e
    _ <*> (Left e) = Left e
    (Right f) <*> (Right a) = Right (f a)

  instance Monad (Either a) where
    return = Right
    (Left x) >>= _ = Left x
    (Right y) >>= f = (f y)
