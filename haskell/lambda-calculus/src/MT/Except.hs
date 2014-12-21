{-# LANGUAGE NoImplicitPrelude #-}
{-# LANGUAGE MultiParamTypeClasses, FunctionalDependencies, FlexibleInstances #-}

module MT.Except (
  ExceptT(..)
  ) where

    import Prelude (($), (.))
    import Functor
    import Applicative
    import Monad
    import MT.Class
    import Either

    -- why not Either e (m a)?
    -- We don't want to lose Computatio because of exception
    newtype ExceptT e m a = ExceptT { runExceptT :: m (Either e a) }

    instance Functor m => Functor (ExceptT e m) where
      fmap f m = ExceptT $ (fmap (fmap f) (runExceptT m))

    instance Monad m => Applicative (ExceptT e m) where
      -- pure x = pure (Right x)
      pure = ExceptT . pure . Right
      (<*>) = ap

    instance Monad m => Monad (ExceptT e m) where
      return = ExceptT . return . Right
      m >>= f = ExceptT $ (runExceptT m) >>= \m' ->
        case m' of
             Left x -> return $ Left x
             Right x -> runExceptT (f x)

    instance MonadT (ExceptT e) where
      lift m = ExceptT (m >>= return . Right)
