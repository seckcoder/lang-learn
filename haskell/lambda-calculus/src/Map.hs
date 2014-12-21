{-# LANGUAGE NoImplicitPrelude #-}

module Map (Map(..), empty, insert, lookup) where

import qualified Data.Map.Lazy
import qualified Data.Maybe
import Data.Ord

import Maybe

type Map = Data.Map.Lazy.Map

empty :: (Data.Map.Lazy.Map k a)
empty = Data.Map.Lazy.empty

lookup :: (Ord k) => k -> Data.Map.Lazy.Map k a -> Maybe a
lookup k map =
  case Data.Map.Lazy.lookup k map of
       Data.Maybe.Nothing -> Nothing
       Data.Maybe.Just v -> Just v

insert :: (Ord k) => k -> a -> Data.Map.Lazy.Map k a -> Data.Map.Lazy.Map k a
insert = Data.Map.Lazy.insert
