
-- An example from The Craft of Functional Programming, Simon Thompson (http://www.cs.kent.ac.uk/people/staff/sjt/), Addison-Wesley 1999: "Given an arbitrary tree, transform it to a tree of integers in which the original elements are replaced by natural numbers, starting from 0. The same element has to be replaced by the same number at every occurrence, and when we meet an as-yet-unvisited element we have to find a 'new' number to match it with:"



module LabelingTree (
  label
  ) where

import Control.Monad.State
import Data.List

data Tree a = Branch a (Tree a) (Tree a)
            | EmptyTree deriving (Show)


label :: (Eq a) => Tree a -> Tree Int
label tr = evalState (labelTree tr) []
  where labelNode :: (Eq a) => a -> State [a] Int
        labelNode v = do
          table <- get
          case elemIndex v table of
               Just idx -> return idx
               Nothing -> do
                 put (table ++ [v])
                 return (length table)
        labelTree :: (Eq a) => Tree a -> State [a] (Tree Int)
        labelTree EmptyTree = return EmptyTree
        labelTree (Branch v left right) = do
          idx <- labelNode v
          left' <- labelTree left
          right' <- labelTree right
          return $ Branch idx left' right'

sample = label (Branch "a" (Branch "b" EmptyTree EmptyTree) (Branch "c" (Branch "a" EmptyTree EmptyTree) (Branch "b" EmptyTree EmptyTree)))
