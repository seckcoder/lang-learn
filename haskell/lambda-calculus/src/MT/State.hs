{-# LANGUAGE NoImplicitPrelude #-}
{-# LANGUAGE MultiParamTypeClasses, FunctionalDependencies, FlexibleInstances #-}

module MT.State (
  StateT(..),
  MonadState(..)
  ) where

    import Prelude (($), (.))
    import Functor
    import Applicative
    import Monad
    import MonadZero
    import MT.Class

    newtype StateT s m a = StateT { runStateT :: s -> m (s, a) }

    instance Functor m => Functor (StateT s m) where
      -- fmap f m = \s -> fmap (\(s', a) -> (s', f a)) (m s)
      fmap f m = StateT $ \s -> fmap (\(s', a) -> (s', f a)) (runStateT m s)

    instance Monad m => Applicative (StateT s m) where
      -- pure x = \s -> pure (s, x)
      pure x = StateT $ \s -> return (s, x)
      (<*>) = ap

    instance Monad m => Monad (StateT s m) where
      -- return x = \s -> return x
      return x = StateT $ \s -> return (s, x)
      -- m >>= f = \s -> m s >>= \ (s1, x) -> (f x s1)
      m >>= f = StateT $ \s -> runStateT m s >>= \ (s1, x) -> runStateT (f x) s1


    instance MonadZero m => MonadZero (StateT s m) where
      mzero = StateT $ \s -> mzero

    instance MonadT (StateT s) where
      lift m = StateT $ \s -> m >>= \x -> return (s, x)
      -- lift m = \s -> m >>= \x -> return (s, x)

    class Monad m => MonadState s m | m -> s where
      get :: m s
      put :: s -> m ()

    instance Monad m => MonadState s (StateT s m) where
      get = StateT $ \s -> return (s, s)
      -- get = \s -> return (s, s)
      put s = StateT $ \_ -> return (s, ())
      -- put s = \_ -> return ((), s)

    -- instance MonadState s m => MonadState s (ContT r m) where
    --   get = lift get
    --   put = lift . put
