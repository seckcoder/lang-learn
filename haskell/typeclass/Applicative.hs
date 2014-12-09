{-# LANGUAGE NoImplicitPrelude #-}
module Applicative ( Applicative(..) ) where
  import Functor

  class Functor f => Applicative f where
    pure :: a -> f a
    (<*>) :: f (a -> b) -> f a -> f b
    (<$>) :: (a -> b) -> f a -> f b
    g <$> x = fmap g x
