{-# LANGUAGE NoImplicitPrelude #-}
{-# LANGUAGE MultiParamTypeClasses #-}

module MT.Class (
  MonadT(..)
  ) where

    import Monad

    class MonadT t where
      lift :: (Monad m) => m a -> t m a
