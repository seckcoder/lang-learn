{-# LANGUAGE RankNTypes #-}


foo :: (forall a. a -> a) -> Char
foo f = f 'c'


type IdFunc = forall a. a -> a
someInt :: IdFunc -> Integer
someInt id' = id' 1

main = print "hello world"

----
-- runST :: forall s,a. ST s a -> a

-- newVar :: a -> ST s (MutVar s a)

-- readVar :: MutVar s a -> ST s a

-- writeVar :: MutVar s a -> a -> ST s ()

-- newVar True :: ST s (MutVar s Bool)
-- runST (newVar True) :: ST s Bool
-- readVar s :: ST s Bool
-- runST (readVar s) :: Bool

----

runST :: forall a. (forall s. ST s a) -> a
newVar :: a -> ST s (MutVar s a)
readVar :: MutVar s a -> ST s a
writeVar :: MutVar s a -> a -> ST s ()

newVar True :: ST s (MutVar s Bool)
runST (newVar True) ::



let v = runST (newVar True)
 in runST (readVar v)
