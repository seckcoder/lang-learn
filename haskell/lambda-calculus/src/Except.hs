{-# LANGUAGE NoImplicitPrelude #-}

module Except (ExceptT(..), throwE, runExceptT) where

  import GHC.Base ((.), ($))

  import Functor
  import Monad
  import Applicative
  import Either
  import Trans

  data ExceptT e m a = ExceptT (m (Either e a))

  runExceptT :: ExceptT e m a -> m (Either e a)
  runExceptT (ExceptT m) = m

  instance Functor m => Functor (ExceptT e m) where
    fmap f = ExceptT . fmap (fmap f) . runExceptT

  instance Monad m => Applicative (ExceptT e m) where
    pure = ExceptT . pure . Right
    (ExceptT f) <*> (ExceptT v) = ExceptT $ (f >>= \mf ->
                                           v >>= \m ->
                                          return (mf <*> m))


  instance Monad m => Monad (ExceptT e m) where
    return = ExceptT . return . Right
    m >>= k = ExceptT $ runExceptT m >>= \a ->
                      case a of
                           Left e -> return (Left e)
                           Right x -> runExceptT (k x)
    fail = ExceptT . fail

  -- fmap will promote function `Right` to monad `m`
  instance MonadTrans (ExceptT e) where
    lift = ExceptT . fmap Right

  throwE :: Monad m => e -> ExceptT e m a
  throwE = ExceptT . return . Left
