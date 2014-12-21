{-# LANGUAGE NoImplicitPrelude #-}
{-# LANGUAGE MultiParamTypeClasses, FunctionalDependencies, FlexibleInstances, UndecidableInstances #-}


module MT.MonadExcept (
  MonadExcept(..)
  ) where

    import Prelude ((.))
    import MT.Class
    import MT.Reader
    import MT.Except
    import Either
    import Monad

    class (Monad m) => MonadExcept e m | m -> e where
      throwE :: e -> m a

    instance (Monad m) => MonadExcept e (ExceptT e m) where
      -- throwE e = ExceptT (return (Left e))
      throwE = ExceptT . return . Left

    instance MonadExcept e m => MonadExcept e (ReaderT r m) where
      throwE = lift . throwE
