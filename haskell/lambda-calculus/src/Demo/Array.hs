
module Demo.Array (
  demos
  ) where



    import Data.Array

    -- accumArray

    -- Accumulate all values in the list with same index into the same entry in the created array

    demo1 = accumArray (+) 0 (1,3) [(1,2), (2, 3), (1, 5)]

    -- accumArray is mainly used for frequency related problems

    freqInRangeAuto lst = freqInRange (minimum lst, maximum lst) lst
    -- Generate a histogram of numbers in lst
    freqInRange rng lst = accumArray (+) 0 rng (zip lst (repeat 1))

    demos = (
      demo1,
      (freqInRange (1, 10) [4, 2, 4, 7, 1, 1, 9])
      )

