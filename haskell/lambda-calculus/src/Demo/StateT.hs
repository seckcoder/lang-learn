{-# LANGUAGE NoImplicitPrelude #-}


module Demo.StateT (
  demos
  ) where

import Prelude ((+), ($), const, error)
import GHC.Integer
import GHC.Num
import Data.Int
import Data.List ((++))
import Data.String
import System.IO
import GHC.Show


import Base
import Maybe
import Monad
import MT.State
import MT.Reader
import Map

-- tail recursive fact without explicit accumulate number
fact :: Integer -> StateT Integer Identity Integer
fact 0 = return 1
fact n = get >>= \acc -> put (acc*n) >> (fact $ n - 1)

demos = [
  runIdentity (runStateT (fact 5) 1)
  ]
