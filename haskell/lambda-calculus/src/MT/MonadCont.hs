{-# LANGUAGE NoImplicitPrelude #-}
{-# LANGUAGE MultiParamTypeClasses, FunctionalDependencies, FlexibleInstances #-}

module MT.MonadCont (
  MonadCont(..)
  ) where

    import Prelude (($))
    import MT.Cont
    import Monad

    class (Monad m) => MonadCont r m | m -> r where
      callCC :: ((a -> ContT r m b) -> ContT r m a) -> ContT r m a

    instance (Monad m) => MonadCont r (ContT r m) where
      callCC f = ContT $ \c -> runContT (f (\ x -> ContT $ \_ -> c x)) c


