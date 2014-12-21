{-# LANGUAGE NoImplicitPrelude #-}

module Cont( ContT(..), Cont, callCC, cont, runCont ) where

  import Prelude (($), (.))
  import Base
  import Functor
  import Applicative
  import Monad
  import Trans

  -- newtype Cont r a = Cont { runCont :: (a -> r) -> r}

  -- `a` is intermediate return value in continuation monad. It will be passed
--  to continuation.
--  Note that for Monad, we always "focus" on `a`.
  newtype ContT r m a = ContT { runContT :: (a -> m r) -> m r }

  type Cont r = ContT r Identity

  cont :: ((a -> r) -> r) -> Cont r a
  cont f = ContT $ \ c -> Identity (f (runIdentity . c))

  runCont :: Cont r a -> (a -> r) -> r
  runCont m k = runIdentity $ runContT m (Identity . k)

  instance Functor (ContT r m) where
    fmap f m = ContT $ \c -> runContT m (c . f)

  instance Applicative (ContT r m) where
    -- $ x is the simplest suspended computation. The computation does nothing
-- but return the value `x`.
    pure x = ContT ($ x)
    -- First extract the function and value in the Applicative Context, then
--  return the final value through continuation:c
    f <*> v = ContT $ \c -> runContT f $ \g -> runContT v $ (c . g)

  instance Monad m => Monad (ContT r m) where
    return x = ContT ($ x)
-- For a continuation monad, the final return value `r` is the return value of
-- continuation :`a -> r`. So `c` is always called in the last.
    m >>= f = ContT $ \c -> runContT m $ \x -> runContT (f x) c

  callCC :: ((a -> ContT r m a1) -> ContT r m a) -> ContT r m a
  callCC f = ContT $ \ c -> runContT (f (\ x -> ContT $ \ _ -> c x)) c
