

import Control.Monad



calcRent = let sumv = 2774
               digit = [500..sumv]
            in do
              x <- digit
              y <- [(x+50)..sumv]
              let tmp = sumv-(x+2*y)-y
              guard (tmp >= 150 && tmp <= 200)
              guard (y-x <= 100)
              return (x,y,sumv-x-2*y)

toList (x,y,z) = [x,y,z]

average rent = (foldr sum (0,0,0) rent) `div` (toInteger (length rent))
  where sum (x,y,z) (a,b,c) = (x+a,y+b,z+c)
        div :: (Integer,Integer,Integer) -> Integer -> (Double, Double, Double)
        div (x,y,z) v = (fromIntegral x / fromIntegral v,
                         fromIntegral y / fromIntegral v,
                         fromIntegral z / fromIntegral v)

main = print "hello wolrd"
