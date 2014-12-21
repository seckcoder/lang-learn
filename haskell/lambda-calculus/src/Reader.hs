{-# LANGUAGE NoImplicitPrelude #-}

module Reader (ReaderT(..), mapReaderT, ask, asks, withReaderT, local ) where

  import Prelude (($), (.), const)
  import Functor
  import Applicative
  import Monad
  import Trans

  -- r is environment, m a is computation that share the environment
  newtype ReaderT r m a = ReaderT { runReaderT :: r -> m a }

  mapReaderT :: (m a -> m b) -> ReaderT r m a -> ReaderT r m b
  {-
  - I can also define mapReaderT as:
  - mapReaderT f m = ReaderT $ fmap f runReaderT m
  - Why?
  -
  - runReaderT return `r->m a`, which is actually a reader monad.
  - fmap applies f to result of the monad, which is `m a`.
  -
  - mapReaderT just apply function in `m a` to the Reader Monad Transformer.
  -}
  mapReaderT f m = ReaderT $ f . runReaderT m

  liftReaderT :: m a -> ReaderT r m a
  liftReaderT m = ReaderT (const m)

  -- ask will return a monad containing current environment
  ask :: Monad m => ReaderT r m r
  ask = ReaderT return

  -- asks will pass env to first argument and use the result returned to construct
--  Reader Monad
  -- f : retrieve a value from the environment
  -- return will construct a reader monad which directly return a(value returned from f) for whatever env input
  asks :: Monad m => (r -> a) -> ReaderT r m a
  asks f = ReaderT (return . f)

  -- r' is the input env, r is the modifed env. f changes r' to r.
-- It also accepts an computation to run in r
-- The returned result is a computation to run in r'.
  withReaderT :: (r' -> r) -> ReaderT r m a -> ReaderT r' m a
  withReaderT f m = ReaderT $ (runReaderT m) . f

  -- A more restricted version of withReaderT
  local :: (r -> r) -> ReaderT r m a -> ReaderT r m a
  local = withReaderT

  instance (Functor m) => Functor (ReaderT r m) where
    {-
    - Two alternative definition:
    - fmap f m = ReaderT $ \r -> fmap f ((runReaderT m) r)
    - This one is very straightforward. After getting the environment, we get the `m a` and apply f to it using fmap.
    -
    - fmap f m = ReaderT $ fmap (fmap f) (runReaderT m)
    - we know
    - fmap f :: m a -> m b
    - That is, fmap maps f to function in another category.
    - So first we map f to Category m.
    - Then we map `fmap f` to Category of Reader Monad which can directly apply to result of `(runReaderT m)`
    -}
    fmap f = mapReaderT (fmap f)

  instance Applicative m => Applicative (ReaderT r m) where
    pure = liftReaderT . pure
    {-
    - mf <*> m = ReaderT $ (runReaderT mf) <*> (runReaderT m)
    - The above definition is wrong.
    - Here, it doesn't consider that type `m` is Applicative.
    - Also, according to the definition, in `ReaderT r m f` <*> `ReaderT r m v`, `f` is a function, `v` is a value. We want to apply f to v and return the result in the monad. So what we do is extract `m f` and `m a` and apply it in `m` category, `f` is a function, `v` is a value. We want to apply f to v and return the result in the monad. So what we do is extract `m f` and `m a` and apply it in `m` category
    -
    -}
    mf <*> m = ReaderT $ \r -> (runReaderT mf r) <*> (runReaderT m r)

  instance Monad m => Monad (ReaderT r m) where
    return = liftReaderT . return
    m >>= f = ReaderT $ \r ->
      (runReaderT m r) >>= \v -> runReaderT (f v) r
    fail msg = lift (fail msg)

  instance MonadTrans (ReaderT r) where
    lift = liftReaderT
