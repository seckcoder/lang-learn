{-# LANGUAGE NoImplicitPrelude #-}


module Demo.ReaderT (
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


-- Demo StateT


tick :: (Num s, MonadState s m) => m ()
tick = get >>= \s -> put (s + 1)



-- Demo Env


data Term = Var Name
          | Lambda Name Term
          | App Term Term
          | Lit Int
          | Add Term Term
          deriving Show

data Value = IntV Int
           | Fun Env Name Term
           deriving Show

type Name = String
type Env = Map String Value
type EvalM = ReaderT Env Identity


interp :: Term -> EvalM Value
interp (Lit x) = return (IntV x)
interp (Add t1 t2) =
  interp t1 >>= \v1 ->
    interp t2 >>= \v2 ->
      case (v1, v2) of
        (IntV v1, IntV v2) -> return (IntV $ v1 + v2)
        _ -> error "type error"
interp (Var n) =
  ask >>= \r ->
    case (lookup n r) of
         Just x -> return x
         Nothing -> error ("unbound variable: " ++ n)

interp (Lambda n t) =
  ask >>= \r ->
    return $ Fun r n t

interp (App t1 t2) =
  interp t1 >>= \v1 ->
    interp t2 >>= \v2 ->
      case v1 of
           Fun r' n t -> local (const (insert n v2 r')) (interp t)
           _ -> error "type error"

exampleExp = (Lit 12) `Add` (App (Lambda "x" (Var "x")) (Lit 4 `Add` Lit 2))
demos = [
  runIdentity $ runReaderT (interp exampleExp) empty
  ]
