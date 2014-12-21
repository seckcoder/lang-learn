{-# LANGUAGE NoImplicitPrelude #-}

module Monad(
  Monad(..),
  when,
  ap
  ) where

  import GHC.Base (id, (.), error)

  import Data.Int
  import Functor
  import Applicative
  import Data.List (replicate, map, foldr, (++))
  import Data.Bool
  import Data.String
  import Data.Function (flip)

  infixl 1 >>=
  class Applicative m => Monad m where
     return :: a -> m a
     (>>=) :: m a -> (a -> m b) -> m b
     (>>) :: m a -> m b -> m b
     m >> n = m >>= \_ -> n
     fail :: String -> m a
     fail s = error s
  --   fmap = liftM
  --   pure = return
  --   <*> = `ap`

  -- class Functor m => Monad m where
  --   return :: a -> m a
  --   (>>=) :: m a -> (a -> m b) -> m b
  --   (>>) :: m a -> m b -> m b
  --   m >> n = m >>= \_ -> n

  join :: Monad m => m (m a) -> m a
  join mm = mm >>= id

  ap :: Monad m => m (a -> b) -> m a -> m b
  -- ap mf m = m >>= (\ a -> (mf >>= \f -> return (f a)))
  ap mf m = mf >>= (\f -> (m >>= \a -> return (f a)))

  -- liftM is unnecessary since we have the constraint that every monad is an applicative functor.
  -- liftM :: Monad m => (a -> b) -> m a -> m b
  -- liftM f m = m >>= (return . f)


  replicateM :: Monad m => Int -> m a -> m [a]
  replicateM n m = sequence (replicate n m)


  when :: Monad m => Bool -> m () -> m ()
  when p action = if p then action else return ()

  whenM :: Monad m => m Bool -> m () -> m ()
  whenM test action = test >>= \t -> if t then action else return ()

  mapM :: Monad m => (a -> m b) -> [a] -> m [b]
  mapM f as = sequence (map f as)

  forM :: Monad m => [a] -> (a -> m b) -> m [b]
  forM = flip mapM

  (=<<) :: Monad m => (a -> m b) -> m a -> m b
  (=<<) = flip (>>=)

  (>=>) :: Monad m => (a -> m b) -> (b -> m c) -> a -> m c
  f >=> g = \x -> (f x) >>= g

  (<=<) :: Monad m => (b -> m c) -> (a -> m b) -> a -> m c
  (<=<) = flip (>=>)


  -- class Applicative m => Monad' m where
  --   join :: m (m a) -> m a

  -- implement bind with join and fmap
  -- class Monad' m => Monad1 m where
  --   m >>= f = join (fmap f m)

  -- implement fmap and join interms of >>= and return
  -- class Monad m => Monad2 m where
  --   join' :: m (m a) -> m a
  --   join' = join

  instance Monad [] where
    return a = [a]
    vs >>= f = foldr ((++) . f) [] vs

  const :: a -> b -> a
  const x y = x

  instance Monad ((->) e) where
    return = const
    m >>= f = \ x -> f (m x) x