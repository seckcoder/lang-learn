{-# LANGUAGE Rank2Types #-}
{-# LANGUAGE ImpredicativeTypes #-}

import Control.Monad
import Control.Applicative
import Control.Exception

newtype DB c a = DB {
  fromDB :: IO a
}


instance Functor (DB c) where
  fmap = liftM

instance Applicative (DB c) where
  pure = return
  (<*>) = ap

instance Monad (DB c) where
  return x = DB $ return x
  m >>= f = DB $ do
    x <- fromDB m
    y <- fromDB $ f x
    return y

data Connection = Connection
data Pool = Pool

newtype SafeConn c = Safe Connection

getConn :: Pool -> IO Connection
getConn = undefined
returnConn :: Pool -> Connection -> IO ()
returnConn = undefined

withConn :: Pool -> (Connection -> IO a) -> IO a
withConn pool act =
  bracket (getConn pool) (returnConn pool) act

query :: Connection -> String -> IO [String]
query = undefined

-- When a connection is returned to the pool, we can't use it anymore.
-- However, withConn can be misused to expose a connection outside of it.
evil :: Pool -> IO Connection
evil pool = withConn pool return
-- This is evil.
-- However, withSafeConn can't expose a (usable) connection to the outside
--

safeQuery :: SafeConn c -> String -> DB c [String]
safeQuery (Safe conn) str = DB (query conn str)

-- Following will report error `c would escape its scope`.
-- That's because the scope of c extends only to the rightmost parenthesis of (forall c. SafeConn c -> DB c a). So after `return` is called, `c` no longer exist in the typing environment. You can't match it against anything.
-- notEvil pool = withSafeConn pool return


withSafeConn :: Pool -> (forall c. SafeConn c -> DB c a) -> IO a
withSafeConn pool act =
  withConn pool $ \conn ->
    fromDB (act (Safe conn))


term1 :: [forall a. a]
term1 = undefined

term2 :: [forall a. a]
term2 = []

term3 :: [forall a. a]
term3 = [undefined]

term4 :: [forall a. a]
term4 = [undefined, undefined]

term5 :: [forall a. (Enum a) => a]
term5 = undefined

term6 :: [forall a. (Enum a) => a]
term6 = []

term7 :: [forall a. (Enum a) => a]
term7 = [undefined]


