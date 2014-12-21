

data Point = Point { xCoord :: Double, yCoord :: Double }


getX :: Point -> Double
getX pt = xCoord pt


data Fuck a b = Fuck { runFuck :: (a, b) } deriving Show


test1 = Fuck (2,3)


newtype Fuck1 a b = Fuck1 { runFuck1 :: a -> b}

test2 = Fuck1 (*2)

-- Fuck2 accepts a function which takes a function return an argument
newtype Fuck2 a b = Fuck2 { runFuck2 :: (a -> b) -> b}

test3 = Fuck2 ($ 2)
