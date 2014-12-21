{-# LANGUAGE NoImplicitPrelude #-}
{-# LANGUAGE MultiParamTypeClasses, FunctionalDependencies, FlexibleInstances #-}


module MT.Reader (
  ReaderT(..),
  ReaderMonad(..),
  withReaderT
  ) where

    import Prelude (($), (.))

    import Functor
    import Applicative
    import Monad
    import MT.Class

    newtype ReaderT r m a = ReaderT { runReaderT :: r -> m a }

    instance Functor m => Functor (ReaderT r m) where
      fmap f m = ReaderT $ \r -> fmap f (runReaderT m r)

    instance Applicative m => Applicative (ReaderT r m) where
      pure x = ReaderT $ \r -> pure x
      f <*> m = ReaderT $ \r ->
        (runReaderT f r) <*> (runReaderT m r)

    instance Monad m => Monad (ReaderT r m) where
      return x = ReaderT $ \r -> return x
      m >>= f = ReaderT $ \r -> (runReaderT m r) >>= \a -> runReaderT (f a) r

    instance MonadT (ReaderT r) where
      lift m = ReaderT $ \r -> m

    class Monad m => ReaderMonad r m | m -> r where
      ask :: m r
      asks :: (r -> a) -> m a
      local :: (r -> r) -> m a -> m a

    withReaderT :: (r' -> r) -> ReaderT r m a -> ReaderT r' m a
    -- withReaderT f m = ReaderT $ \r' -> runReaderT m (f r')
    withReaderT f m = ReaderT $ (runReaderT m) . f

    instance Monad m => ReaderMonad r (ReaderT r m) where
      -- ask = ReaderT $ \r -> return r
      ask = ReaderT return
      -- asks f = ReaderT $ \r -> return (f r)
      asks f = ReaderT (return . f)
      local = withReaderT
