import Control.Monad.Trans.Cont

square:: (Num a) => a -> a
square x = x*x

square_cps :: (Num a) => a -> (a -> b) -> b
square_cps x k = k (square x)

twice :: (a -> a) -> a -> a
twice f x = f . f $ x


twice_cps :: (a -> (a -> b) -> b) -> a -> (a -> b) -> b
twice_cps f_cps x =
  \k ->
    f_cps x $ \y ->
      f_cps y $ \z ->
        k z


square_cont :: (Num a) => a -> a -> Cont r a
square_cont x = return (square x)


main = print (twice_cps square_cps 3 id)
