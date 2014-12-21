{-# LANGUAGE NoImplicitPrelude #-}
module Applicative ( Applicative(..), Monoidal(..), ZipList(..), sequence ) where

  import GHC.Base hiding (Functor(..))
  import Functor
  import Data.List
  import GHC.Show

  import Monoid

  class Functor f => Applicative f where
    pure :: a -> f a
    (<*>) :: f (a -> b) -> f a -> f b
    (<$>) :: (a -> b) -> f a -> f b
    g <$> x = fmap g x

  -- Monoidal
  -- TODO : I still didn't figure out what's monoidal.

  class Functor f => Monoidal f where
    unit :: f ()
    (**) :: f a -> f b -> f (a, b)

{-
- Law:
-   1. pure id <*> v = v
-   2. pure f <*> pure v = pure (f v)
-   3. u <*> pure y = pure ($ y) <*> u
-   4. u <*> (v <*> w) = pure (.) <*> u <*> v <*> w
-}

  data ZipList a = ZipList [a] deriving (Show)

  instance Functor ZipList where
    fmap f (ZipList x) = ZipList (fmap f x)

  instance Applicative ZipList where
    pure x = ZipList [x]
    (ZipList gs) <*> (ZipList xs) = ZipList (zipWith ($) gs xs)


  instance Applicative [] where
    pure x = [x]
    gs <*> xs = [ g $ s | g <- gs, s <- xs ]

  instance Monoid e => Applicative ((,) e) where
    pure b = (mempty, b)
    (a0,f) <*> (a1,b) = ((a0 <> a1), (f b))

  instance Applicative ((->) e) where
    pure = const
    f <*> g = \x -> f x (g x)

  liftA2 :: Applicative f => (a1 -> a -> b) -> f a1 -> f a -> f b
  liftA2 f a b = f <$> a <*> b

  sequence :: Applicative f => [f a] -> f [a]
  sequence fas = foldr (liftA2 (:)) (pure []) fas
