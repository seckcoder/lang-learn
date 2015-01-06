{-# LANGUAGE NoImplicitPrelude #-}


module MonadZero (
  MonadZero(..),
  guard
  ) where

    import Prelude (Bool(..))
    import Monad
    import Maybe
    import Either
    import Error

    -- mzero is failure for monad combination
    -- mzero is identity for mplus
    class (Monad m) => MonadZero m where
      mzero :: m a

    instance MonadZero [] where
      mzero = []

    instance MonadZero Maybe where
      mzero = Nothing

    instance (Error e) => MonadZero (Either e) where
      mzero = Left noMsg

    guard :: MonadZero m => Bool -> m ()
    guard True = return ()
    guard False = mzero
