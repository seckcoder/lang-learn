{-# LANGUAGE NoImplicitPrelude #-}

module Maybe(
  Maybe(..),
  Last(..),
  fromJust,
  maybe
  ) where

  import GHC.Base (Eq)
  import GHC.Show
  import Functor
  import Applicative
  import Monad
  import Semigroup
  import Monoid

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

-- To construct Last, we use Last (Maybe a). But the result has type: (Last a)
  newtype Last a = Last { getLast :: Maybe a } deriving (Show)

  instance Semigroup (Last a) where
    (Last x) <> (Last Nothing) = (Last x)
    _ <> (Last (Just x)) = (Last (Just x))

  fromJust :: Maybe a -> a
  fromJust (Just x) = x

  maybe :: b -> (a -> b) -> Maybe a -> b
  maybe y f (Just x) = f x
  maybe y f Nothing = y
