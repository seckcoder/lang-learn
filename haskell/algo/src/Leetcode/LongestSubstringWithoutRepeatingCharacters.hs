






module LongestSubstringWithoutRepeatingCharacters (
  lswrc
  ) where

    import Data.HashSet (insert, member, HashSet)
    import qualified Data.HashSet as HashSet
    import Data.List (findIndex, head, tail, maximumBy)
    import Control.Monad.State

    splitBefore :: (a -> Bool) -> [a] -> ([a], [a])
    splitBefore f lst = case findIndex f lst of
                           Just idx -> splitAt idx lst
                           Nothing -> ([], []) -- this will surely not happen.
    chooseLonger :: [a] -> [a] -> [a]
    chooseLonger s1 s2 = if length s1 > length s2 then s1 else s2

    lswrc :: [Char] -> [Char]
    lswrc s = go s HashSet.empty [] []
      where go [] hset acc res = res
            go (c:s) hset acc res =
              if member c hset
                 then let (a,b) = (splitBefore (== c) acc)
                          newset = (foldl (\ hset c' -> HashSet.delete c' hset) hset a)
                       in go s newset ((tail b) ++ [c]) (chooseLonger acc res) -- fst doesn't include c, snd is [c, ..c)
                 else go s (insert c hset) (acc ++ [c]) res


    -- sample = [lswrc "abcabcbb", lswrc "bbbbb"]

    -- using State monad
    lswrcM :: [Char] -> [Char]
    lswrcM [] = []
    lswrcM s = maximumBy (\ a b -> compare (length a) (length b)) $ evalState (go s) (HashSet.empty, [])
      where go :: [Char] -> State (HashSet Char, [Char]) [[Char]]
            go [] = return []
            go (c:s) = do
              (hset, acc) <- get
              if member c hset
                 then let (a,b) = splitBefore (== c) acc
                       in do
                         put (foldl (\ hset c' -> HashSet.delete c' hset) hset a, (tail b) ++ [c])
                         rst <- go s
                         return $ acc : rst
                 else do
                   put (HashSet.insert c hset, acc ++ [c])
                   go s
