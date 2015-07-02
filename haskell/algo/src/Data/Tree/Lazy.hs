module Data.Tree.Lazy (
  BinTree(..),
  preOrder,
  preOrderT,
  inOrder,
  inOrderT,
  postOrder,
  postOrderT,
  postOrderT1
  ) where

data BinTree a = EmptyTree
               | Branch a (BinTree a) (BinTree a) deriving (Show)

preOrder :: BinTree a -> [a]
preOrder (EmptyTree) = []
preOrder (Branch a left right) = [a] ++ preOrder left ++ preOrder right

inOrder :: BinTree a -> [a]
inOrder (EmptyTree) = []
inOrder (Branch a left right) = inOrder left ++ [a] ++ inOrder right

postOrder :: BinTree a -> [a]
postOrder (EmptyTree) = []
postOrder (Branch a left right) = postOrder left ++ postOrder right ++ [a]


preOrderT :: BinTree a -> [a]
preOrderT bt = go [bt] []
  where go [] xs = reverse xs
        go (EmptyTree:ts) xs = go ts xs
        go (Branch v left right:ts) xs = go (left:right:ts) (v:xs)

inOrderT :: BinTree a -> [a]
inOrderT bt = go [bt] [] []
  where go [] [] xs = reverse xs
        go (EmptyTree:ts) [] xs = go ts [] xs
        go (EmptyTree:ts) (v:left_acc) xs = go ts left_acc (v:xs)
        go (Branch v left right:ts) left_acc xs = go (left:right:ts) (v:left_acc) xs



-- tail recursive post order traversal
postOrderT :: BinTree a -> [a]
postOrderT bt = go [bt] []
  where go [] xs = xs
        go (EmptyTree:ts) xs = go ts xs
        go (Branch v left right:ts) xs = go (right:left:ts) (v:xs)


postOrderT1 :: BinTree a -> [a]
postOrderT1 tree = go [tree] [] [] []
  where go :: [BinTree a] -> [BinTree a] -> [a] -> [a] -> [a]
        go [] [] [] vs = reverse vs
        go (EmptyTree:ts) [] [] vs = go [] [] [] vs
        go [] (EmptyTree:r_acc) [] vs = go [] [] [] vs
        go (EmptyTree:ts) (EmptyTree:r_acc) [] vs =
          go ts r_acc [] vs
        go (EmptyTree:ts) (EmptyTree:r_acc) (v:v_acc) vs =
          go ts r_acc v_acc (v:vs)
        go (EmptyTree:ts) (Branch v l r:r_acc) v_acc vs =
          go (l:ts) (r:r_acc) (v:v_acc) vs
        go (Branch v l r:ts) r_acc v_acc vs =
          go (l:ts) (r:r_acc) (v:v_acc) vs


sampleTree :: BinTree Int
sampleTree = Branch 4 (Branch 2 (Branch 1 EmptyTree EmptyTree) (Branch 3 EmptyTree EmptyTree)) (Branch 6 (Branch 5 EmptyTree EmptyTree) (Branch 7 EmptyTree EmptyTree))
