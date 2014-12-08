{-# LANGUAGE NoImplicitPrelude #-}

module Monad(
  Monad(..)
  ) where

  class Monad m where
    return :: a -> m a
    (>>=) :: m a -> (a -> m b) -> m b

  infixl >>=
