{-# LANGUAGE MagicHash #-}


import GHC.Exts

foo :: Int# -> Int#
foo 0# = 0#
foo n = foo (n -# 1#)

main = print (I# (foo 3))
