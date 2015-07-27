



module WordLadderI (
  ladderLength
  ) where

import qualified Data.HashSet as HS

ladderLength :: [Char] -> [Char] -> HS.HashSet [Char] -> Int
ladderLength p r dict =

  map (\ c -> ['a'..'z']) p
