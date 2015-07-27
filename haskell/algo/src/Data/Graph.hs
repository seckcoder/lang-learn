
{-# LANGUAGE TypeFamilies, FlexibleContexts #-}

module Data.Graph (
  Graph
  ) where

import Control.Monad


class (Monad g, Eq (Vertex g), Eq (Edge g)) => Graph g where
  type Verte g :: *
  type Edge g :: *
  foo :: a -> g a
