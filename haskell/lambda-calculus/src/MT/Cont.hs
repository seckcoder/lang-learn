{-# LANGUAGE NoImplicitPrelude #-}


module MT.Cont (
  ContT(..)
  ) where


    import Prelude (($), (.))
    import Base
    import Functor
    import Applicative
    import Monad
    import MT.Class


    newtype ContT r m a = ContT { runContT :: (a -> m r) -> m r }

    type Cont r = ContT r Identity

    cont :: ((a -> r) -> r) -> Cont r a
    cont f = ContT $ \k -> Identity (f (runIdentity . k ))
    -- cont f = ContT $ \ k -> Identity $ f (\ a -> runIdentity (k a))
    runCont :: Cont r a -> (a -> r) -> r
    runCont m f = runIdentity $ runContT m (\a -> Identity (f a))

    instance Functor m => Functor (ContT r m) where
      fmap f m = ContT $ \ k -> runContT m (k . f)

    instance Functor m => Applicative (ContT r m) where
      pure x = ContT ($ x)
      -- pure x = ContT $ \ k -> k x
      f <*> v = ContT $ \ k -> runContT f $ \ g -> runContT v (k . g)

    instance Monad m => Monad (ContT r m) where
      return x = ContT ($ x)
      m >>= f = ContT $ \ k -> runContT m $ \ x -> runContT (f x) k

    instance MonadT (ContT r) where
      lift m = ContT $ \ k -> m >>= \a -> k a
