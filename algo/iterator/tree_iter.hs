


data Tree a = EmptyTree
            | Branch a (Tree a) (Tree a)


preOrder :: Tree a -> [a]
preOrder tree = go [tree] []
  where go [] vs = reverse vs
        go (EmptyTree:ts) vs = go ts vs
        go [(Branch v left right):ts] vs = go (left:right:ts) (v:vs)


postOrder :: Tree a -> [a]
postOrder tree = go [tree] []
  where go [] vs = vs
        go (EmptyTree:ts) vs = go ts vs
        go [(Branch v left right):ts] vs = go (right:left:ts) (v:vs)


inOrder :: Tree a -> [a]
inOrder tree = go [tree] [] []
  where go [] [] vs = reverse vs
        go (EmptyTree:ts) [] vs = go ts [] vs
        go (EmptyTree:ts) (v:acc) vs = go ts acc (v:vs)
        go [(Branch v left right):ts] acc vs = go (left:right) (v:acc) vs


postOrder1 tree = go [tree] [] [] []
  where go [] [] [] vs = reverse vs
        go (EmptyTree:ts) (EmptyTree:r_acc) [] vs = go ts r_acc v_acc [] vs
        go (EmptyTree:ts) (EmptyTree:r_acc) (v:v_acc) vs = go ts r_acc v_acc (v:vs)
        go (EmptyTree:ts) [(Branch v l r):r_acc] v_acc vs = go (l:ts) (r:r_acc) (v:v_acc) vs
        go [(Branch v l r):ts] r_acc v_acc vs = go (l:ts) (r:r_acc) (v:v_acc) vs




