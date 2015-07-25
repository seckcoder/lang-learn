


module TwoSum (
  twoSum
  ) where

  import Data.HashSet (member, insert)
  import qualified Data.HashSet as HashSet
  import Control.Monad.ST
  import Data.STRef
  import Control.Monad (forM_, when)

  twoSum nums target =
    case
      foldl (\ (res,hset) v ->
        let newset = (insert v hset)
         in if member (target-v) hset
               then (((target-v,v):res), newset)
               else (res, newset)) ([], HashSet.empty) nums of
        (res,_) -> res


  -- Monadic way(using ST Monad)
  twoSumM nums target = runST $ do
    hset <- newSTRef HashSet.empty
    res <- newSTRef []
    forM_ nums $ \x -> do
      hset' <- readSTRef hset
      when (member (target-x) hset') $ modifySTRef res $ ((:) (target-x,x))
      modifySTRef hset $ insert x
    readSTRef res
