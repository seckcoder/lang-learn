
import Data.Maybe


foo :: Num a => Maybe a -> a
foo Nothing = 3
foo (Just v) = v


main = foo 3
