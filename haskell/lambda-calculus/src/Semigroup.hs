{-# LANGUAGE NoImplicitPrelude #-}

module Semigroup ( Semigroup(..) ) where

  import Prelude (even, quot, (-))
  import GHC.Base
  import GHC.Num
  import NonEmpty

  infixr 6 <>
  class Semigroup a where
    (<>) :: a -> a -> a
    (<>) = mappend
    sconcat :: NonEmpty a -> a
    sconcat (a :| as) = go a as where
      go b [] = b
      go b (c:cs) = go (b <> c) cs
    mappend :: a -> a -> a
    mappend = (<>)

    timeslp :: Int -> a -> a
    timeslp n x0 = pow x0 ((+1) n)
      where
        pow base e
          | even e = pow (base <> base) (e `quot` 2)
          | e == 1 = base
          | otherwise = pow_combine (base <> base) ((e - 1) `quot` 2) base
        pow_combine base e const
          | even e = pow_combine (base <> base) (e `quot` 2) const
          | e == 1 = (base <> const)
          | otherwise = pow_combine (base <> base) ((e - 1) `quot` 2) (base <> const)

    {-# MINIMAL (<>) | mappend #-}
