{-# LANGUAGE NoImplicitPrelude #-}


module Demo.Monad (
  demos
  ) where

    import Prelude (Bool(..), (*), (==), (.), ($), Int(..), (>), (+), Eq(..), snd)
    import Data.List

    import Functor
    import Applicative
    import Monad
    import MonadZero
    import GHC.Show
    import MT.State


    -- list can be used as backtracing monad

    demo1 =
      [1,2,3] >>= \x ->
        [4,5,6] >>= \y ->
          guard (x*y == 8) >> (return (x,y))


    splits :: Eq a => [a] -> [([a], a)]
    splits xs = [(delete x xs, x) | x <- xs]


    choose :: Eq a => StateT [a] [] a
    choose = StateT (\ s -> splits s)
    sendMoney :: StateT [Int] [] [Int]
    sendMoney = let m = 1 :: Int
                    o = 0
                    digit = [0..9]
                    num s = foldl ((+) . (*10)) 0 s
                 in
                 choose >>= \s ->
                   guard (s > 7) >>
                     choose >>= \ e ->
                       choose >>= \ n ->
                         choose >>= \ d ->
                           choose >>= \ y ->
                             choose >>= \ r ->
                               guard (num [s,e,n,d] +
                                 num [m,o,r,e] == num [m,o,n,e,y]) >>
                                   return [s,e,n,d,m,o,r,e,m,o,n,e,y]


    foo :: StateT [Int] [] Int
    foo = choose >>= \s -> guard (s > 7) >> return s

    -- send + more = money
    demo2 = map snd $ runStateT sendMoney [2..9]

    demos = (
      --demo1,
      demo2
      )
