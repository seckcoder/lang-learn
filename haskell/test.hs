


import Data.Monoid

mzip :: (Monoid a, Monoid b) => [a] -> [b] -> [(a, b)]
mzip (a:as) (b:bs) = (a, b) : mzip as bs
mzip []     (b:bs) = (mempty, b) : mzip [] bs
mzip (a:as) []     = (a, mempty) : mzip as []
mzip _      _      = []

