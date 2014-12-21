{-# LANGUAGE NoImplicitPrelude #-}

module Main where

import Prelude ((+), const)
import GHC.Base (($), (.))
import System.IO
import Data.List ((++))
import Data.String
import Ast
import Maybe
import Either
import Base
import Map
import Except
import Monad
import Reader
import Trans
import GHC.Num
import GHC.Prim

eval0 :: Env -> Exp -> Value

eval0 env (Lit i) = IntVal i
eval0 env (Var s) = fromJust (lookup s env)
eval0 env (Plus e1 e2) = let IntVal i1 = eval0 env e1
                             IntVal i2 = eval0 env e2
                        in IntVal (i1 + i2)
eval0 env (Lambda s exp) = FunVal env s exp

eval0 env (App e1 e2) = let val1 = eval0 env e1
                            val2 = eval0 env e2
                         in case val1 of
                                 FunVal env' s body -> eval0 (insert s val2 env') body


exampleExp = (Lit 12) `Plus` (App (Lambda "x" (Var "x")) (Lit 4 `Plus` Lit 2))

demo0 = eval0 empty exampleExp

type Eval1 a = Identity a

runEval1 :: Eval1 a -> a
runEval1 m = runIdentity m

eval1 :: Env -> Exp -> Eval1 Value
eval1 env (Lit i) = return (IntVal i)
eval1 env (Var s) = maybe (fail (s ++ " not found")) return (lookup s env)
eval1 env (Plus e1 e2) =
  eval1 env e1 >>= \(IntVal i1) ->
    eval1 env e2 >>= \(IntVal i2) ->
      return (IntVal (i1 + i2))

eval1 env (Lambda s exp) = return (FunVal env s exp)
eval1 env (App e1 e2) =
  eval1 env e1 >>= \(FunVal env' s body) ->
    eval1 env e2 >>= \val2 ->
      eval1 (insert s val2 env') body

exampleExp1 = (App (Lambda "x" (Var "y")) (Lit 4))
exampleExp2 = (App (Lit 5) (Lit 4))

demo1 = runEval1 (eval1 empty exampleExp)
demo11 = runEval1 (eval1 empty exampleExp1)
demo12 = runEval1 (eval1 empty exampleExp2)



type Eval2 a = ExceptT String Identity a
runEval2 :: Eval2 a -> Either String a
runEval2 ev = runIdentity (runExceptT ev)

eval2a :: Env -> Exp -> Eval2 Value
eval2a env (Lit i) = return (IntVal i)
eval2a env (Var s) = maybe (fail (s ++ " not found")) return (lookup s env)
eval2a env (Plus e1 e2) =
  eval2a env e1 >>= \(IntVal i1) ->
    eval2a env e2 >>= \(IntVal i2) ->
      return (IntVal (i1 + i2))
eval2a env (Lambda s exp) = return (FunVal env s exp)
eval2a env (App e1 e2) =
  eval2a env e1 >>= \(FunVal env' s body) ->
    eval2a env e2 >>= \val2 ->
      eval2a (insert s val2 env') body

eval2 :: Env -> Exp -> Eval2 Value
eval2 env (Lit i) = return (IntVal i)
eval2 env (Var s) = maybe (fail (s ++ " not found")) return (lookup s env)
eval2 env (Plus e1 e2) =
  eval2 env e1 >>= \v1 ->
    eval2 env e2 >>= \v2 ->
      case (v1, v2) of
           (IntVal i1, IntVal i2) -> return $ IntVal (i1 + i2)
           _ -> throwE "type error"

eval2 env (Lambda s exp) = return (FunVal env s exp)
eval2 env (App e1 e2) =
  eval2 env e1 >>= \v1 ->
    eval2 env e2 >>= \v2 ->
      case v1 of
           (FunVal env' s body) -> eval2 (insert s v2 env') body
           _ -> throwE "type error"

demo20 = runEval2 (eval2 empty exampleExp)
demo21 = runEval2 (eval2 empty exampleExp1)
demo22 = runEval2 (eval2 empty exampleExp2)


type Eval3 a = ReaderT Env (ExceptT String Identity) a

runEval3 :: Env -> Eval3 a -> Either String a
runEval3 env ev = runIdentity . runExceptT $ runReaderT ev env

throwException = lift . throwE

eval3 :: Exp -> Eval3 Value
eval3 (Lit i) = return (IntVal i)
eval3 (Var s) = ask >>= \env -> maybe (throwException (s ++ " not found")) return (lookup s env)
eval3 (Plus e1 e2) =
  eval3 e1 >>= \v1 ->
    eval3 e2 >>= \v2 ->
      case (v1, v2) of
           (IntVal i1, IntVal i2) -> return $ IntVal (i1 + i2)
           _ -> throwException "type error"
eval3 (App e1 e2) =
  eval3 e1 >>= \v1 ->
    eval3 e2 >>= \v2 ->
      case v1 of
           (FunVal env' s body) -> local (const (insert s v2 env')) (eval3 body)
           _ -> throwException "type error"

eval3 (Lambda s exp) = asks $ \env -> (FunVal env s exp)
runEval3With exp = runEval3 empty (eval3 exp)

test f = do
  print (f exampleExp1)


type Eval4 a = ReaderT Env (ExceptT String (StateT Integer Identity)) a

runEval4 :: Env -> Integer -> Eval4 Value -> Either String Value
runEval4 env st ev = runIdentity $ runStateT st $ runExceptT (runReaderT env ev)

eval4a :: Exp -> Eval4 Value
eval4a (Lit i) = get \s ->

main = test runEval3With
