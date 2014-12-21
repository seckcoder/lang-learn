{-# LANGUAGE NoImplicitPrelude #-}

import Monad
import Functor
import Maybe
import Either
import NonEmpty
import Semigroup
import Monoid
import Applicative
import Base
import GHC.Base hiding (Functor, Maybe, Monad, fmap, return, (>>=))
import Data.Fixed
import GHC.Num
import GHC.Real
import GHC.Float hiding ((**))
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

demo_semigroup1 = do
  print (sconcat ((Sum (Complex 1 2)) :| [Sum (Complex 2 3)]))
  print (sconcat ((Product (Complex 1 2)) :| [Product (Complex 2 3)]))
  print (timeslp 10 (Product (Complex 1 2)))

demo_Complex = do
  print ((Complex 1 1) + (Complex 2 2))
  print ((Complex 1 1) - (Complex 2 2))
  print ((Complex 1 1) * (Complex 2 2))
  print ((Complex 1 1) + 0)
  print (- (Complex 1 1))

demo_monoid1 = do
  print ((Sum (Complex 1 2)) <> mempty)
  print ((Sum (Complex 1 2)) <> ((Sum (Complex 2 3)) <> (Sum (Complex 3 4))))
  print (((Sum (Complex 1 2)) <> (Sum (Complex 2 3))) <> (Sum (Complex 3 4)))
  print (mconcat [(Sum (Complex 1 2)), (Sum (Complex 2 3))])
  print (mconcat (map Sum [(Complex 1 2), (Complex 2 3)]))
  {-
  analysis of precedence:
    1. Function application has higher precedence than any infix operator
    2. infixr 9 .
    3. infixr 0 $
  So first apply map with Sum. Then combine mconcat with (map Sum). Finally apply
  this combined function to [...]
  -}
  print (mconcat . map Sum $ [(Complex 1 2), (Complex 2 3)])
  print ((mconcat . (map Sum)) [(Complex 1 2), (Complex 2 3)])


genList1 n = take n [1..]
genList2 n = take n [2..]
genList3 n = take n [3..]

demo_monoid2 = do
  -- here each function is a monoid. So we concat the function monoid to
--  generate another function and apply it to 3.
--  This example is quite meaningful...
  print (mconcat [genList1, genList2, genList3] 3)

demo_monoid_Last = do
  print ((Last (Just 3)) <> (Last (Just 4)) <> (Last (Nothing)))
  -- local type binding
  let x :: (Num a) => (Last a)
      x = (Last Nothing)
   in print x

cmpLen w1 w2 =
  compare (length w1) (length w2)

demo_monoid_Sort = do
  -- sort first by length, then alphabatically
  print (sortBy (cmpLen <> compare) (words "The reasoning behind this definition"))


demo_applicative = do
  print $ (pure id <*> ZipList [1])
  let x :: (Num a) => ZipList a
      x = pure 1
   in print ((pure (\ x -> 2 * x)) <*> x)

  print (ZipList [\ x -> 2*x, \ x -> 3*x] <*> pure 1)
  print (pure ($ 1) <*> ZipList [\ x -> 2*x, \ x -> 3*x])

  -- (+) <$> [1] creates partial function in `f` domain
--  then, this function is applied with [2]
  print (pure (+) <*> [1] <*> [2])
  print ((+) <$> [1] <*> [2])


main = demo_Monoidal
