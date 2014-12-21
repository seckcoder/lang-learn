

import qualified Data.Map as Map (insert, lookup, empty)
import Control.Monad.Trans.Except
import Control.Monad.Trans.Reader
import Control.Monad.Trans.State (StateT(..))
import Control.Monad.Identity
import Control.Monad.State.Class
import Data.Maybe

import Ast

type Eval3 a = ReaderT Env (ExceptT String Identity) a

runEval3 :: Env -> Eval3 a -> Either String a
runEval3 env ev = runIdentity (runExceptT (runReaderT ev env))

eval3 :: Exp -> Eval3 Value
eval3 (Lit i ) = return $ IntVal i
eval3 (Var n) = do env <-  ask
                   case Map.lookup n env of
                        Nothing -> fail ("unbound variable: " ++ n)
                        Just val -> return val
eval3 (Plus e1 e2 ) = do e1' <- eval3 e1
                         e2' <- eval3 e2
                         case (e1', e2') of
                              (IntVal i1,IntVal i2 ) -> return $ IntVal (i1 + i2 )
                              _ -> fail "type error in addition"

eval3 (Lambda n e) = do env <- ask
                        return $ FunVal env n e

eval3 (App e1 e2 ) = do val1 <- eval3 e1
                        val2 <- eval3 e2
                        case val1 of
                             FunVal env0 n body -> local (const (Map.insert n val2 env0)) (eval3 body)
                             _ -> fail "type error in application"

exampleExp = (Lit 12) `Plus` (App (Lambda "x" (Var "x")) (Lit 4 `Plus` Lit 2))

-- type Eval4 a = ReaderT Env (ExceptT String (StateT Integer Identity)) a
type Eval4 a = ExceptT String (ReaderT Env (StateT Integer Identity)) a

-- runEval4 :: Env -> Integer -> Eval4 a -> (Either String a, Integer)
-- runEval4 env st ev = runIdentity $ runStateT (runReaderT (runExceptT ev) ev) st

tick :: (Num s, MonadState s m) => m ()
tick = do st <- get
          put (st+1)

eval4 :: Exp -> Eval4 Value
eval4 (Lit i) = do
  tick
  return $ IntVal i

eval4 (Var n) = do tick
                   env <- ask
                   case Map.lookup n env of
                        Nothing -> throwE ("unbound variable " ++ n)
                        Just val -> return val

-- eval4 (Plus e1 e2) = do tick
--                         e1' <- eval4 e1
--                         e2' <- eval4 e2
--                         case (e1', e2') of
--                              (IntVal i1, IntVal i2) -> return $ IntVal (i1+i2)
--                              _ -> throwE "type error"

-- eval4 (Lambda n e) = do tick
--                         env <- ask
--                         return $ FunVal env n e

-- eval4 (App e1 e2) = do tick
--                        val1 <- eval4 e1
--                        val2 <- eval4 e2
--                        case val1 of
--                             FunVal env' n body ->
--                               local (const (Map.insert n val2 env')) (eval4 body)
--                             _ -> throwE "type error"

main = print 4
-- main = print (runEval4 Map.empty 0 (eval4 exampleExp))
