
{-# LANGUAGE NoImplicitPrelude, MagicHash, UnboxedTuples #-}

class Num a where
  (+) :: a -> a -> a


instance Num Int where
  I# x + I# y = I# (x + y)



t = let x = x
     in x
