{-# LANGUAGE NoImplicitPrelude #-}

module Monoid ( Monoid(..), Sum(..), Product(..) ) where

  import Prelude (foldr)
  import Semigroup
  import GHC.Num
  import GHC.Show
  import Data.List

  class Semigroup a => Monoid a where
    mempty :: a
    mconcat :: [a] -> a
    mconcat = foldr (<>) mempty

  newtype Sum a = Sum { getSum :: a } deriving (Show)

  instance Num a => Semigroup (Sum a) where
    Sum x <> Sum y = Sum (x+y)

  instance Num a => Monoid (Sum a) where
    mempty = Sum 0

  newtype Product a = Product { getProduct :: a } deriving (Show)

  instance Num a => Semigroup (Product a) where
    Product x <> Product y = Product (x*y)

  instance Num a => Monoid (Product a) where
    mempty = Product 1

  instance Semigroup a => Semigroup (e -> a) where
    f <> g = \ x -> ((f x) <> (g x))
  instance Monoid a => Monoid (e -> a) where
    -- mempty = \ _ -> mempty
    -- This is just magic!
    mempty _ = mempty

  instance Semigroup [a] where
    (<>) = (++)

  instance Monoid [a] where
    mempty = []
