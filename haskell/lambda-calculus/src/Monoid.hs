{-# LANGUAGE NoImplicitPrelude #-}

module Monoid (
  Semigroup(..),
  Monoid(..),
  Sum(..),
  Product(..),
  Endo(..),
  Dual(..)
  ) where

  import Prelude (foldr, id, (.))
  import Semigroup
  import GHC.Num
  import GHC.Show
  import GHC.Generics
  import Data.List
  import Data.Ord

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


  instance Semigroup Ordering where
    LT <> _ = LT
    GT <> _ = GT
    EQ <> y = y

  instance Monoid Ordering where
    mempty = EQ

  newtype Endo a = Endo { appEndo :: a -> a }

  instance Semigroup (Endo a) where
    Endo f <> Endo g = Endo (f . g)

  instance Monoid (Endo a) where
    mempty = Endo id

  newtype Dual a = Dual { getDual :: a }

  instance Semigroup a => Semigroup (Dual a) where
    Dual x `mappend` Dual y = Dual (y `mappend` x)

  instance Monoid a => Monoid (Dual a) where
    mempty = Dual mempty
