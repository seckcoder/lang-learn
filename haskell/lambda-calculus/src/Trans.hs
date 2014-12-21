{-# LANGUAGE NoImplicitPrelude #-}

module Trans( MonadTrans(..) ) where

  import Monad

  -- lift a monad to the constructed monad
  class MonadTrans t where
    lift :: (Monad m) => m a -> t m a
