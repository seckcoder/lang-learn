


partition_rec [] v = ([], [])
partition_rec (x:xs) v
  | x < v = let (lt_xs, ge_xs) = partition_rec xs v
                              in ((x:lt_xs), ge_xs)
  | otherwise = let (lt_xs, ge_xs) = partition_rec xs v
                 in (lt_xs, (x:ge_xs))


partition_tail_rec [] v lt_xs ge_xs = lt_xs ++ ge_xs
partition_tail_rec (x:xs) v lt_xs ge_xs
  | x < v = partition_tail_rec xs v (x:lt_xs) ge_xs
  | otherwise = partition_tail_rec xs v lt_xs (x:ge_xs)

partition1 xs v = let (lt_xs, ge_xs) = partition_rec xs v
                   in lt_xs ++ ge_xs

partition2 xs v = partition_tail_rec xs v [] []
