{-# LANGUAGE NoImplicitPrelude #-}

module Functor( Functor(..) ) where
  import GHC.Base hiding (Functor)

  class Functor f where
    fmap :: (a -> b) -> f a -> f b

  instance Functor ((,) e) where
    fmap f (a,b) = (a, (f b))

  instance Functor ((->) e) where
    fmap = (.)
