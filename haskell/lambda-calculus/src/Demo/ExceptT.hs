{-# LANGUAGE NoImplicitPrelude #-}

module Demo.ExceptT (
  demos
  ) where

    import Prelude ((*), ($), const, (.))
    import Data.Int
    import Data.String
    import GHC.Num
    import GHC.Show
    import Data.List ((++))

    import Base
    import Functor
    import Applicative
    import Monad
    import MT.Reader
    import MT.Except
    import MT.MonadExcept
    import Maybe
    import Either
    import Map

    demo1 =
      let x :: Int
          x = 3
          y :: Int
          y = 2
          z :: ExceptT String Maybe Int
          z = ExceptT (Just (Right x))
       in runExceptT (fmap (*y) z)

    demo2 =
      let f :: Num a => ExceptT String Maybe (a -> a)
          f = pure (*2)
          v :: Num a => ExceptT String Maybe a
          v = pure 3
       in runExceptT (f <*> v)

    demo3 =
      let e :: Num a => ExceptT String Identity a
          e = throwE "this is a fake exception"
       in runIdentity $ runExceptT e

-- interpreter demo
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
    type EvalM = ReaderT Env (ExceptT String Identity)

    interp :: Term -> EvalM Value
    interp (Lit x) = return (IntV x)
    interp (Add t1 t2) =
      interp t1 >>= \v1 ->
        interp t2 >>= \v2 ->
          case (v1, v2) of
            (IntV v1, IntV v2) -> return (IntV $ v1 + v2)
            _ -> throwE "type error"
    interp (Var n) =
      ask >>= \r ->
        case (lookup n r) of
             Just x -> return x
             Nothing -> throwE ("unbound variable: " ++ n)

    interp (Lambda n t) =
      ask >>= \r ->
        return $ Fun r n t

    interp (App t1 t2) =
      interp t1 >>= \v1 ->
        interp t2 >>= \v2 ->
          case v1 of
               Fun r' n t -> local (const (insert n v2 r')) (interp t)
               _ -> throwE "type error"

    exampleExp = (Lit 12) `Add` (App (Lambda "x" (Var "x")) (Lit 4 `Add` Lit 2))
    exampleExp1 = (Lit 12) `Add` (App (Lambda "y" (Var "x")) (Lit 4 `Add` Lit 2))

    demo4 = (runIdentity . runExceptT) $ runReaderT (interp exampleExp) empty
    demo5 = (runIdentity . runExceptT) $ runReaderT (interp exampleExp1) empty

    demos = (
      demo1,
      demo2,
      demo3,
      demo4,
      demo5
      )
