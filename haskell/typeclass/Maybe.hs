{-# LANGUAGE NoImplicitPrelude #-}

module Maybe(
  Maybe(..),
  ) where

  import GHC.Base (Eq)
  import GHC.Show
  import Functor
  import Applicative
  import Monad

  data Maybe a = Just a | Nothing deriving (Eq, Show)

  instance Functor Maybe where
    fmap _ Nothing = Nothing
    fmap f (Just x) = Just (f x)

  instance Applicative Maybe where
    pure x = Just x
    (Just f) <*> (Just x) = Just (f x)
    _ <*> _ = Nothing

  instance Monad Maybe where
    return = Just
    Nothing >>= _ = Nothing
    (Just x) >>= f = (f x)
