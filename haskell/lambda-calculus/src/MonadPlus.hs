
{-# LANGUAGE NoImplicitPrelude #-}

module MonadPlus (
  MonadPlus(..)
  ) where


    import MonadZero
    import Maybe
    import Either

    class (MonadZero m) => MonadPlus m where
      mplus :: m a -> m a -> m a

    instance MonadPlus [] where
      mplus = (++)

    instance MonadPlus Maybe where
      Just x `mplus` _ = Just x
      Nothing `mplus` v = v

    instance MonadPlus (Either e) where
      Left _ `mplus` v = v
      Right x `mplus` _ = Right x
