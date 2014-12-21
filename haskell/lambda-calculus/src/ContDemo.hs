{-# LANGUAGE NoImplicitPrelude #-}

import Prelude (($), (.), (>), show, id)
import GHC.Num
import System.IO
import Data.Int
import Data.String
import Base
import Cont
import Monad

square:: (Num a) => a -> a
square x = x*x

square_cont1 x = \k -> k (square x)

square_cont :: (Num a) => a -> Cont b a
square_cont x = cont $ \k -> k (square x)


square_CCC x = callCC $ \k -> k (square x)


foo = callCC $ \k -> (k "hello world") >> (return "never printed")

main = print $ runCont foo show

-- main = print $ runCont (square_CCC 4) show
-- square_cont :: ((Num a), Monad m) => a -> ContT b m a
-- square_cont x = ContT $ \k -> k (square x)
-- main = print $ runContT (square_cont 4) (\x -> (return (show x)):: Identity String)



