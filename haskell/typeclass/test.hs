{-# LANGUAGE NoImplicitPrelude #-}

import Monad
import Functor
import Maybe
import Either
import Base
import GHC.Base hiding (Functor, Maybe, Monad, fmap, return, (>>=))
import Data.Fixed
import GHC.Num
import GHC.Real
import GHC.Float
import System.IO
import Data.List
import Data.Char (ord)
import GHC.Show

divBy :: Integral t => t -> [t] -> Maybe.Maybe [t]
divBy v [] = Just []
divBy v (0:xs) = Nothing
divBy v (x:xs) =
  case divBy v xs of
       Nothing -> Nothing
       Just rxs -> Just ((v `div` x) : rxs)

demo_Maybe = divBy 3 (take 5 [0..])


demo_Maybe_Functor =
  fmap (*2) (Just 2)

demo_Maybe_Monad =
  (Just 2) >>= \ x -> Just (x * 2)

isPasswordRightLength :: [Char] -> Either.Either [Char] [Char]
isPasswordRightLength pwd =
  let len = length pwd
      in
      if len >= 6 && len <= 16
         then Right pwd
         else Left ("the length " ++ (show len) ++ " is not right")


isNumber c =
  let ascii = (ord c)
   in ascii >= (ord '0') && ascii <= (ord '9')

isPasswordHasNumber :: [Char] -> Either.Either [Char] [Char]
isPasswordHasNumber pwd =
  if any isNumber pwd
     then (Right pwd)
     else (Left "password doesn't contain number")

isPasswordValid :: [Char] -> Either [Char] [Char]
isPasswordValid pwd =
  isPasswordHasNumber pwd >>= isPasswordRightLength


demo_Either_Functor :: Either.Either Integer Integer
demo_Either_Functor =
  fmap (*2) (Right 2)

demo_Either_Monad = do
  print (isPasswordValid "0aaaaa")
  print (isPasswordValid "aaaaaa")
  print (isPasswordValid "0aaaa")



demo_tuple_Functor = do
  fmap (*2) (1,2)

demo_pair_Functor = do
  print (fmap id (Pair 2 3))
  print (((fmap (*3)) . (fmap (*5))) (Pair 1 2))
  print (fmap ((*3) . (*5)) (Pair 1 2))

main = demo_pair_Functor
