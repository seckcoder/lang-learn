

import Data.Either
import Control.Monad.Reader

--- This demo explains why ask defines as `ReaderT return`

demo = let y :: Int
           y = 3
           x :: Either String Int
           x = runReaderT (ReaderT return) y
        in x
