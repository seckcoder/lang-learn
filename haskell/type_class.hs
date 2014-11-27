
class MyShow a where
  myshow :: a ->String


data Point = Point Double Double

--- implement MyShow typeclass for Point
instance MyShow Point where
  myshow (Point x y) = "(" ++ show x ++ ", " ++ show y ++ ")"


instance Eq Point where
  (Point x1 y1) == (Point x2 y2) =
    (x1 == x2) && (y1 == y2)


--- context for an instance
instance (MyShow a) => MyShow [a] where
  myShow [] = "[]"
  myShow (x:xs) = myShow x ++ ":" + myShow xs

