

data Tree a = EmptyTree
            | Branch a Tree Tree


generateTrees n = do
  lst <- enumerate n
  return $ generateTreesFromList lst

generateTreesFromList [] = [EmptyTree]
generateTreesFromList (x:xs) = do
  (left, right) <- combineList xs
  left_branch <- generateTreesFromList left
  right_branch <- generateTreesFromList right
  return $ Branch x left_branch right_branch

enumerate n = do
  x <- choice [1..n]
  xs <- choice $ enumerate ([1..n] // x)
  return $ (x:xs)

combineList [] = ([], [])
combineList xs = let len = length xs
                  in do
                    left_len <- choice [0..len]
                    return $ split xs left_len
