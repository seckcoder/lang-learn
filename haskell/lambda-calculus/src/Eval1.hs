{-# LANGUAGE NoImplicitPrelude #-}

import Prelude ((+), (.), ($), error, const)
import System.IO
import Data.Maybe
import Data.Either
import Data.List ((++))
import Data.String
import Control.Monad
import Control.Monad.Identity
import Control.Monad.Trans.Reader
import Control.Monad.Trans.State (StateT(..))
import Control.Monad.Trans.Class
import Control.Monad.Trans.Except
import Control.Monad.State.Class
import qualified Data.Map as Map (lookup, insert, empty)
import GHC.Integer
import GHC.Num
import Ast

exampleExp = (Lit 12) `Plus` (App (Lambda "x" (Var "x")) (Lit 4 `Plus` Lit 2))
exampleExp1 = (App (Lambda "x" (Var "y")) (Lit 4))
exampleExp2 = (App (Lit 5) (Lit 4))
exampleExp3 = (App (Lambda "x" (Var "x")) (Lit 1))

eval0 :: Env -> Exp -> Either String Value

eval0 env (Lit i) = return $ IntVal i
eval0 env (Var s) =
  case (Map.lookup s env) of
       Nothing -> Left ("can't find variable: " ++ s)
       Just x -> return x
eval0 env (Plus e1 e2) =
  eval0 env e1 >>= \v1 ->
    eval0 env e2 >>= \v2 ->
      case (v1, v2) of
           (IntVal i1, IntVal i2) -> return $ IntVal (i1 + i2)
           _ -> Left "type error"

eval0 env (Lambda s exp) = return $ FunVal env s exp

eval0 env (App e1 e2) =
  eval0 env e1 >>= \val1 ->
    eval0 env e2 >>= \val2 ->
      case val1 of
           (FunVal env' s body) -> eval0 (Map.insert s val2 env') body
           _ -> Left "type error"


type Eval1 a = ReaderT Env (Either String) a

panic :: (MonadTrans t) => String -> t (Either String) a
panic = lift . Left

eval1 :: Exp -> Eval1 Value
eval1 (Lit i) = return $ IntVal i
eval1 (Var s) = do
  env <- ask
  case (Map.lookup s env) of
       Nothing -> panic ("can't find variable: " ++ s)
       Just x -> return x

eval1 (Plus e1 e2) =
  eval1 e1 >>= \v1 ->
    eval1 e2 >>= \v2 ->
      case (v1, v2) of
           (IntVal i1, IntVal i2) -> return $ IntVal (i1 + i2)
           _ -> panic "type error"

eval1 (Lambda s exp) = asks (\env -> FunVal env s exp)

eval1 (App e1 e2) =
  eval1 e1 >>= \val1 ->
    eval1 e2 >>= \val2 ->
      case val1 of
           (FunVal env' s body) -> local (const (Map.insert s val2 env')) (eval1 body)
           _ -> panic "type error"

runEval1 env ev = (runReaderT ev env)

testEval1 exp = runEval1 Map.empty (eval1 exp)


-------------------------------------------------------------

type Eval2 a = ReaderT Env (Either String) a

-- panic :: (MonadTrans t) => String -> t (Either String) a
-- panic = lift . Left

eval2 :: Exp -> Eval2 Value
eval2 (Lit i) = return $ IntVal i
eval2 (Var s) = ask >>= \r -> case (Map.lookup s r) of
                                   Nothing -> panic ("can't find variables: " ++ s)
                                   Just x -> return x

eval2 (Plus e1 e2) =
  eval2 e1 >>= \v1 ->
    eval2 e2 >>= \v2 ->
      case (v1, v2) of
           (IntVal i1, IntVal i2) -> return $ IntVal (i1 + i2)
           _ -> panic "type error"

eval2 (Lambda s exp) = asks (\env -> FunVal env s exp)

eval2 (App e1 e2) =
  eval2 e1 >>= \val1 ->
    eval2 e2 >>= \val2 ->
      case val1 of
           (FunVal env' s body) -> local (const (Map.insert s val2 env')) (eval2 body)
           _ -> panic "type error"

runEval2 env ev = (runReaderT ev env)


testEval2 exp = runEval2 Map.empty (eval2 exp)


---------------------------------------------------------------------------------



panic3 = lift . lift . throwE
type Eval3 a = ReaderT Env (StateT Integer (ExceptT String Identity)) a
runEval3 env s ev = runIdentity $ runExceptT $ runStateT (runReaderT ev env) s
-- type Eval3 a = ReaderT Env (ExceptT String (StateT Integer Identity)) a
-- runEval3 env s ev = runIdentity $ runStateT (runExceptT (runReaderT ev env)) s

-- here `m` is Eval3
tick :: (Num s, MonadState s m) => m ()
tick = get >>=
  \s -> put (s + 1)

eval3 :: Exp -> Eval3 Value
-- eval3 (Lit i) = tick >>= \_ -> return $ IntVal i
eval3 (Lit i) = tick >> (return $ IntVal i)
eval3 (Var s) =
  tick >> ask >>=
    \r ->case (Map.lookup s r) of
              Nothing -> panic3 ("can't find variables: " ++ s)
              Just x -> return x

eval3 (Plus e1 e2) =
  tick >>
    eval3 e1 >>= \v1 ->
      eval3 e2 >>= \v2 ->
        case (v1,v2) of
          (IntVal i1, IntVal i2) -> return $ IntVal (i1 + i2)
          _ -> panic3 "type error"

eval3 (Lambda s exp) = tick >> asks (\r -> FunVal r s exp)

eval3 (App e1 e2) =
  tick >>
    eval3 e1 >>= \val1 ->
      eval3 e2 >>= \val2 ->
        case val1 of
             (FunVal r' s body) -> local (const (Map.insert s val2 r')) (eval3 body)
             _ -> panic3 "type error"


testEval3 exp = runEval3 Map.empty 1 (eval3 exp)

main = print 3
