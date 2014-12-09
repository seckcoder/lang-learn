{-# LANGUAGE NoImplicitPrelude #-}


module Base (
  Pair(..),
  flip,
  Complex(..)
  ) where
    import Prelude ((+))
    import GHC.Base hiding (Functor(..), flip)
    import GHC.Show
    import Data.Int
    import GHC.Num
    import GHC.Integer

    import Functor
    import Semigroup
    import Monoid

    flip f x y = f y x

    data Pair a = Pair a a deriving (Show)

    instance Functor Pair where
      fmap f (Pair x y) = Pair (f x) (f y)

    data ITree a = Leaf (Int -> a)
                 | Node [ITree a]

    instance Functor ITree where
      fmap f (Leaf g) = Leaf (f . g)
      fmap f (Node [it]) = Node [fmap f it]

    data Complex = Complex Int Int

    instance Show Complex where
      show (Complex a b) = (show a) ++ "+" ++ (show b) ++ "i"

    plusComplex (Complex a0 b0) (Complex a1 b1) = (Complex (a0 + a1) (b0 + b1))
    minusComplex (Complex a0 b0) (Complex a1 b1) = (Complex (a0 - a1) (b0 - b1))
    timesComplex (Complex a0 b0) (Complex a1 b1) = (Complex (a0 * a1) (b0 * b1))
    negateComplex (Complex a0 b0) = (Complex (-a0) (-b0))

    instance Num Complex where
      (+) = plusComplex
      (-) = minusComplex
      (*) = timesComplex
      negate = negateComplex
      fromInteger i = Complex (fromInteger i) 0
      signum a = error "Can't call signum of complex number"
      abs (Complex a b) = (Complex (abs a) (abs b))

{-
    instance Monoid (Sum Complex) where

       mempty = Sum (Complex 0 0)


    instance Semigroup Complex where
       (Complex a0 b0) <> (Complex a1 b1) = Complex (a0 + a1) (b0 + b1)

    instance Monoid Complex where
       mempty = Complex 0 0

-}
