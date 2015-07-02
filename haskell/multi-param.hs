 {-# LANGUAGE MultiParamTypeClasses #-}
 {-# LANGUAGE FunctionalDependencies #-}
 {-# LANGUAGE FlexibleInstances #-}

import System.IO

class Add a b c | a b -> c where
  plus :: a -> b -> c

class Mul a b c | a b -> c where
  mul :: a -> b -> c


instance Add Int Int Int where
  a `plus` b = a + b

instance Add Int Float Float where
  a `plus` b = (fromIntegral a) + b

instance Add Float Int Float where
  a `plus` b = a + (fromIntegral b)

instance Add Float Float Float where
  a `plus` b = a + b

instance Mul Int Int Int where
  a `mul` b = a * b

instance Mul Int Float Float where
  a `mul` b = (fromIntegral a) * b


data Vec a = Vec [a] deriving Show

data Mat a = Mat [[a]] deriving Show

instance Mul a b b => Mul a (Vec b) (Vec b) where
  a `mul` (Vec vb) = Vec (map (mul a) vb)

demo1 = let x :: Int
            x = 3
            y :: Float
            y = 4
         in x `plus` y

demo2 = let x :: Int
            x = 2
            y :: [Int]
            y = [4,5,6]
         in (x `mul` (Vec y))


class Collection e ce | ce -> e where
  empty :: ce
  insert :: e -> ce -> ce
  member :: e -> ce -> Bool


instance Collection Int [Int] where
  empty = []
  insert = (:)
  member = elem


-- demo = let x :: Int
--            x = 3
--         in insert x empty

demo = let x :: Int
           x = 3
           ec :: [Int]
           ec = empty
        in insert x empty
main = print demo
